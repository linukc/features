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

#include "v_mono_calibrator.h"

VMonoCalibrator::~VMonoCalibrator()
{
}

int VMonoCalibrator::tryFrame(cv::Mat& frame)
{
    if(m_framesGrabed < m_realPoints.size() &&
       cv::findChessboardCorners( frame, patternSize, m_detectedPoints[m_framesGrabed] ) ) {
      orderDetectedPoints(m_detectedPoints[m_framesGrabed]);
      cv::cvtColor(frame, m_grayImage, CV_BGR2GRAY);
      cv::cornerSubPix( m_grayImage, m_detectedPoints[m_framesGrabed], cv::Size(11,11), cv::Size(-1, -1),
                        cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1 ) );
      cv::drawChessboardCorners(frame, patternSize, m_detectedPoints[m_framesGrabed], true);
      ++ m_framesGrabed;
    }
    return m_realPoints.size() - m_framesGrabed;
}
void VMonoCalibrator::getHomography(cv::Mat& H) const
{
    cv::Mat R;
    cv::Rodrigues(m_R, R);
    cv::Mat W(3, 4, CV_64FC1);
    int j;
    for(int i = 0; i < 3 ; ++i)
      for(j = 0; j < 3; ++j)
        W.at<double>(i, j)=R.at<double>(i, j);
    for(j = 0; j < 3; ++j)
      W.at<double>(j, 3)=m_T.at<double>(0, j);
    H = m_cameraMatrix * W;
}
void VMonoCalibrator::setRequiredFramesCount(size_t count, int squareLength)
{
    VAbstractCalibrator::setRequiredFramesCount(count, squareLength);
    m_detectedPoints.resize(count);
    for(size_t i = 0; i < count; ++i)
        m_detectedPoints[i].resize(patternSize.width * patternSize.height);
}
bool VMonoCalibrator::calibrate()
{
    if(m_framesGrabed == m_realPoints.size()) {
        std::vector<cv::Mat> rvecs(m_realPoints.size());
        std::vector<cv::Mat> tvecs(m_realPoints.size());

        m_distortionCoefficients = cv::Scalar(0);
        m_cameraMatrix=cv::Scalar(0);

        int flags = cv::CALIB_FIX_K3;
        if(m_initialFocusValue > 0.0) {
            m_cameraMatrix.at<double>(0, 0) = m_initialFocusValue;
            m_cameraMatrix.at<double>(0, 2) = m_cameraResolution.width >> 1;
            m_cameraMatrix.at<double>(1, 1) = m_initialFocusValue;
            m_cameraMatrix.at<double>(1, 2) = m_cameraResolution.height >> 1;
            m_cameraMatrix.at<double>(2, 2) = 1.0;
            flags |= cv::CALIB_USE_INTRINSIC_GUESS;
        }
        cv::calibrateCamera(m_realPoints, m_detectedPoints,
                            m_cameraResolution, m_cameraMatrix, m_distortionCoefficients,
                            rvecs, tvecs, flags);
        m_R = rvecs[0];
        m_T = tvecs[0];
        return true;
    }
    return false;
}
