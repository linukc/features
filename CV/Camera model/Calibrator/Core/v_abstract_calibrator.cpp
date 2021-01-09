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

#include "v_abstract_calibrator.h"

const cv::Size VAbstractCalibrator::patternSize(7,7);

VAbstractCalibrator::~VAbstractCalibrator()
{
}

void VAbstractCalibrator::setRequiredFramesCount(size_t count,int squareLength)
{
    m_realPoints.resize(count);
    static const int pointsCount=patternSize.width*patternSize.height;
    float temp=squareLength*(patternSize.width>>1);
    int j;
    for(size_t i=0;i<count;++i) {
        m_realPoints[i].resize(pointsCount);
        for(j=0;j<pointsCount;++j) {
            m_realPoints[i][j].x=squareLength*(j%patternSize.width);
            m_realPoints[i][j].x-=temp;
            m_realPoints[i][j].y=squareLength*(j/patternSize.height);
            m_realPoints[i][j].y-=temp;
            m_realPoints[i][j].z=0.0f;
        }
    }
}
