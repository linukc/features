/**
    @file v_mono_calibrator.h

    @brief Definition of the class for calibration one camera.

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

#ifndef __V_MONO_CALIBRATOR_H
#define __V_MONO_CALIBRATOR_H

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "v_abstract_calibrator.h"

/**
    @class VMonoCalibrator

    Class for calibrating one camera using chessboard.

    @author Dmitry Suvorov
 */
class VMonoCalibrator : public VAbstractCalibrator
{
    std::vector<std::vector<cv::Point2f> > m_detectedPoints;

    cv::Mat m_cameraMatrix;
    cv::Mat m_distortionCoefficients;

    cv::Mat m_R;
    cv::Mat m_T;

    cv::Mat m_grayImage;
public:
    inline VMonoCalibrator() :
            m_cameraMatrix(3, 3, CV_64FC1),
            m_distortionCoefficients(5,1,CV_64FC1)
    {
    }
    virtual ~VMonoCalibrator();

    ///Try to detect chessboard's corners.
    ///@param[in] frame Image with chessboard.
    ///@return Number of frames to grab before starting calibration.
    int tryFrame(cv::Mat& frame);
    ///Get Homography(transformation matrix from camera's coordinates to image coordinates).
    ///@param[out] H Matrix 4x3.
    void getHomography(cv::Mat& H) const;

    ///Get intisics camera's parameters.
    ///@param[out] M Camera's matrix.
    ///@param[out] D Distortion coefficients.
    inline void getIntrinsics(cv::Mat& M, cv::Mat& D) const
    {
        M = m_cameraMatrix;
        D = m_distortionCoefficients;
    }
    ///Get extrinsics camera's parameters.
    ///@param[out] R Rotation vector.
    ///@param[out] T Translation vector.
    inline void getExtrinsics(cv::Mat& R, cv::Mat& T) const
    {
        R = m_R;
        T = m_T;
    }

    virtual void setRequiredFramesCount(size_t count, int squareLength);
    virtual bool calibrate();
};

#endif // __V_MONO_CALIBRATOR_H
