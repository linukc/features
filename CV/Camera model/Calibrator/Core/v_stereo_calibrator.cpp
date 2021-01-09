/*
 *  Copyright (c) 2011 Dmitry Suvorov <D.Suvorov90@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "v_stereo_calibrator.h"

#include <boost/thread/thread.hpp>

#include <opencv2/imgproc/imgproc.hpp>

VStereoCalibrator::VStereoCalibrator()
{
    for(unsigned i = 0;i < CAMERAS_COUNT; ++i) {
        m_cameraMatrix[i] = cv::Mat(3, 3, CV_64FC1),
        m_distCoeffs[i] = cv::Mat(5,1,CV_64FC1);
    }
}
VStereoCalibrator::~VStereoCalibrator()
{
}

void VStereoCalibrator::setRequiredFramesCount( size_t count, int squareLength )
{
    VAbstractCalibrator::setRequiredFramesCount( count, squareLength );
    for(size_t j,i = 0;i < CAMERAS_COUNT; ++i) {
        m_imagePoints[i].resize(count);
        for(j = 0; j < count; ++j)
             m_imagePoints[i][j].resize(patternSize.width * patternSize.height);
    }
}
bool VStereoCalibrator::calibrate()
{
    if( m_framesGrabed == m_realPoints.size() ) {
        unsigned i = 0;
        for(;i < CAMERAS_COUNT; ++i) {
            m_distCoeffs[i] = cv::Scalar(0);
            m_cameraMatrix[i] = cv::Scalar(0);
        }

        int flags = cv::CALIB_ZERO_TANGENT_DIST;
        if(m_initialFocusValue > 0.0) {
            for(i = 0; i < CAMERAS_COUNT; ++i) {
                m_cameraMatrix[i].at<double>(0, 0) = m_initialFocusValue;
                m_cameraMatrix[i].at<double>(0, 2) = m_cameraResolution.width >> 1;
                m_cameraMatrix[i].at<double>(1, 1) = m_initialFocusValue;
                m_cameraMatrix[i].at<double>(1, 2) = m_cameraResolution.height >> 1;
                m_cameraMatrix[i].at<double>(2, 2) = 1.0;
            }
            flags |= cv::CALIB_USE_INTRINSIC_GUESS;
        }
        cv::stereoCalibrate( m_realPoints, m_imagePoints[LEFT_CAMERA], m_imagePoints[RIGHT_CAMERA],
                             m_cameraMatrix[LEFT_CAMERA], m_distCoeffs[LEFT_CAMERA],
                             m_cameraMatrix[RIGHT_CAMERA], m_distCoeffs[RIGHT_CAMERA],
                             m_cameraResolution, m_R, m_T, m_E, m_F,
                             cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30.0, 1e-6), flags );
        return true;
    }
    return false;
}
int VStereoCalibrator::tryFrames( cv::Mat& leftFrame, cv::Mat& rightFrame )
{
    bool res[CAMERAS_COUNT];
    boost::thread thread(tryFrame, rightFrame, m_imagePoints[m_framesGrabed][RIGHT_CAMERA],
                         m_grayImage[RIGHT_CAMERA], res[RIGHT_CAMERA] );
    tryFrame(leftFrame, m_imagePoints[m_framesGrabed][LEFT_CAMERA], m_grayImage[LEFT_CAMERA], res[LEFT_CAMERA]);
    thread.join();
    if( res[LEFT_CAMERA] && res[RIGHT_CAMERA] )
        ++ m_framesGrabed;
    return m_realPoints.size() - m_framesGrabed;
}

void VStereoCalibrator::tryFrame(cv::Mat& frame, std::vector<cv::Point2f>& detectedPoints,
                                 cv::Mat& grayImage, bool &res)
{
    res = cv::findChessboardCorners( frame, patternSize, detectedPoints );
    if( res ) {
        orderDetectedPoints( detectedPoints );
        cv::cvtColor( frame, grayImage, CV_BGR2GRAY );
        cv::cornerSubPix( grayImage, detectedPoints, cv::Size(11, 11), cv::Size(-1, -1),
                          cv::TermCriteria( cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1 ) );
        cv::drawChessboardCorners( frame,patternSize, detectedPoints, true );
    }
}
