/**
    @file v_abstract_calibrator.h

    @brief Definition of the base class for calibration.

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

#ifndef __V_ABSTRACT_CALIBRATOR_H
#define __V_ABSTRACT_CALIBRATOR_H

#include <opencv2/core/core.hpp>

/**
  @class VAbstractCalibrator

  Base class for calibrating cameras. It uses chessboard as calibration object.

  @author Dmitry Suvorov
 */
class VAbstractCalibrator
{
protected:
    ///Number of grabed chessboard's views.
    size_t m_framesGrabed;
    ///Positions of chessboard's corners in the camera's coordinate system.
    std::vector<std::vector<cv::Point3f> > m_realPoints;
    ///Resolution of the calibrating camera(s).
    cv::Size m_cameraResolution;
    ///
    double m_initialFocusValue;

    ///Nubmer of squares on eachchessboard's side.
    static const cv::Size patternSize;

    ///@param[in] points Detected chessboard's corners.
    template<typename Point2D>
    static void orderDetectedPoints(std::vector<Point2D>& points);
public:
    inline VAbstractCalibrator() :
            m_framesGrabed(0),
            m_initialFocusValue(-1.0)
    {
    }
    virtual ~VAbstractCalibrator();

    ///Stop calibration.
    inline void stop()
    {
        m_framesGrabed=0;
    }
    ///@return Number of chessboard's views required for calibration.
    inline int getRequiredFramesCount() const
    {
        return m_realPoints.size();
    }
    ///@return Number of grabed chessboard's views.
    inline int getGrabedFramesCount() const
    {
        return m_framesGrabed;
    }
    ///Set camera's resolution.
    ///@param[in] resolution Resolution of the calibrating camera(s).
    inline void setResolution(const cv::Size& resolution)
    {
        m_cameraResolution=resolution;
    }
    ///Start calibration.
    ///@param[in] initialFocus Initial focus value in pixels.
    inline void start(double initialFocus = -1.0)
    {
        m_initialFocusValue = initialFocus;
    }

    ///Set number of chessboard's views required for calibration.
    ///param[in] count Number of chessboard's views required for calibration.
    ///param[in] squareLength Length in mm of one chessboard's square.
    virtual void setRequiredFramesCount(size_t count,int squareLength);

    ///Calculate parameters.
    ///@return True on success.
    virtual bool calibrate()=0;
};

template<typename Point2D>
void VAbstractCalibrator::orderDetectedPoints(std::vector<Point2D>& points)
{
    Point2D temp;
    int lastIndex=patternSize.width-1;
    int maxJ,j,i=0;
    if(points[0].x>points[points.size()-1].x) {
        if(points[0].y>points[points.size()-1].y) {
            for(;i<lastIndex;++i) {
                maxJ=lastIndex-i;
                for(j=i;j<maxJ;++j) {
                    std::swap(points[i*patternSize.width+j],points[(lastIndex-i)*patternSize.width+lastIndex-j]);
                    std::swap(points[j*patternSize.width+lastIndex-i],points[(lastIndex-j)*patternSize.width+i]);
                }
            }
        }
        else {
            for(;i<lastIndex;++i) {
                maxJ=lastIndex-i;
                for(j=i;j<maxJ;++j) {
                    temp=points[i*patternSize.width+j];
                    points[i*patternSize.width+j]=points[(lastIndex-j)*patternSize.width+i];
                    points[(lastIndex-j)*patternSize.width+i]=points[(lastIndex-i)*patternSize.width+lastIndex-j];
                    points[(lastIndex-i)*patternSize.width+lastIndex-j]=points[j*patternSize.width+lastIndex-i];
                    points[j*patternSize.width+lastIndex-i]=temp;
                }
            }
        }
    }
    else if(points[0].y>points[points.size()-1].y) {
            for(;i<lastIndex;++i) {
                maxJ=lastIndex-i;
                for(j=i;j<maxJ;++j) {
                    temp=points[i*patternSize.width+j];
                    points[i*patternSize.width+j]=points[j*patternSize.width+lastIndex-i];
                    points[j*patternSize.width+lastIndex-i]=points[(lastIndex-i)*patternSize.width+lastIndex-j];
                    points[(lastIndex-i)*patternSize.width+lastIndex-j]=points[(lastIndex-j)*patternSize.width+i];
                    points[(lastIndex-j)*patternSize.width+i]=temp;
                }
            }
        }
}

#endif // __V_ABSTRACT_CALIBRATOR_H
