/**
    @file v_stereo_calibrator.h

    @brief Definition of class for calibrating stereo system.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __V_STEREO_CALIBRATOR_H
#define __V_STEREO_CALIBRATOR_H

#include <opencv2/calib3d/calib3d.hpp>

#include "v_abstract_calibrator.h"

/**
    @class VStereoCalibrator

    Class for calibrating stereo system using chessboard.

    @author Dmitry Suvorov
 */
class VStereoCalibrator : public VAbstractCalibrator
{
public:
    ///Camera's position in the stereo system.
    enum CameraSide
    {
        LEFT_CAMERA,
        RIGHT_CAMERA
    };

    ///Count of cameras in the stereo system.
    enum { CAMERAS_COUNT = 2 };
private:
    std::vector<std::vector<cv::Point2f> > m_imagePoints[CAMERAS_COUNT];

    cv::Mat m_cameraMatrix[CAMERAS_COUNT];
    cv::Mat m_distCoeffs[CAMERAS_COUNT];
    cv::Mat m_R;
    cv::Mat m_T;
    cv:: Mat m_E;
    cv::Mat  m_F;

    cv::Mat m_grayImage[CAMERAS_COUNT];

    static void tryFrame(cv::Mat& frame, std::vector<cv::Point2f>& detectedPoints,
                        cv::Mat& grayImage, bool &res);
public:
    VStereoCalibrator();
    virtual ~VStereoCalibrator();

    ///Get intrinsics parameters of one camera.
    inline void getCamerasIntrinsics(int side, cv::Mat& M, cv::Mat& D) const
    {
        assert(side < CAMERAS_COUNT);
        M = m_cameraMatrix[side];
        D = m_distCoeffs[side];
    }
    ///Get essential matrix.
    inline void getEssentialMatrix(cv::Mat& E) const
    {
        E = m_E;
    }
    ///Get fundamental matrix.
    inline void getFundamentalMatrix(cv::Mat& F) const
    {
        F = m_F;
    }
    ///Get the rotation matrix and translation vector between the cameras.
    inline void getCamerasOrientation(cv::Mat& R, cv::Mat& T) const
    {
        R = m_R;
        T = m_T;
    }

    ///Try to detect chessboard's corners.
    ///@param[in] frame Image with chessboard.
    ///@return Number of frames to grab before starting calibration.
    int tryFrames(cv::Mat& leftFrame, cv::Mat& rightFrame );

    virtual void setRequiredFramesCount(size_t count,int squareLength);
    virtual bool calibrate();
};

#endif // __V_STEREO_CALIBRATOR_H
