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

#ifndef __VVIDEOWIDGET_H
#define __VVIDEOWIDGET_H

#include <QWidget>
#include <QPainter>

#include <opencv2/core/core.hpp>

class VVideoWidget : public QWidget
{
    Q_OBJECT
private:
    enum BGR
    {
        BLUE,
        GREEN,
        RED
    };

    QImage m_image;
protected:
    virtual void paintEvent(QPaintEvent *event);
public:
    explicit VVideoWidget(QWidget *parent=0,Qt::WindowFlags f=0);

    void showImage(const cv::Mat& image);
};

#endif // __V_VIDEO_WIDGET_H
