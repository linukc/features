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

#include "vvideowidget.h"

VVideoWidget::VVideoWidget(QWidget *parent,Qt::WindowFlags f) :
        QWidget(parent,f),
        m_image(640,480,QImage::Format_RGB888)
{
    resize(m_image.size());
    
    QPainter painter(&m_image);
    painter.fillRect(m_image.rect(),Qt::black);
}

void VVideoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawImage(0,0,m_image);
}
void VVideoWidget::showImage(const cv::Mat& image)
{
    if(image.data) {
        if(m_image.width()!=image.cols || m_image.height()!=image.rows)
            m_image=QImage(image.cols,image.rows,QImage::Format_RGB888);
        const uchar *ptr;
        for(int j,i=0;i<image.rows;++i) {
            ptr=image.data+i*image.step;
            for(j=0;j<image.cols;++j) {
                m_image.setPixel(j,i,qRgb(ptr[RED],ptr[GREEN],ptr[BLUE]));
                ptr+=3;
            }
        }
    }
    else {
        QPainter painter(&m_image);
        painter.fillRect(m_image.rect(),Qt::black);
    }
    update();
}
