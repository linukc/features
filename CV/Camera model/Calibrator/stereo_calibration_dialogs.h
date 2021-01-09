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

#ifndef __STEREO_CALIBRATION_DIALOGS_H
#define __STEREO_CALIBRATION_DIALOGS_H

#include <opencv2/highgui/highgui.hpp>

#include "Core/v_stereo_calibrator.h"

#include "ui_v_stereo_calibration_dialog.h"
#include "ui_v_choose_cameras_dialog.h"

class VChooseCamerasDialog : public QDialog, private Ui::VChooseCamerasDialog
{
    Q_OBJECT
private:
    int m_selectedIndex[VStereoCalibrator::CAMERAS_COUNT];
private slots:
    void changeOkButtonState();
public:
    VChooseCamerasDialog(QWidget *parent = 0);

    int getSelectedIndex(int side) const
    {
        Q_ASSERT(side < VStereoCalibrator::CAMERAS_COUNT);
        return m_selectedIndex[side];
    }
};

class VStereoCalibrationDialog : public QDialog, private Ui::VStereoCalibrationDialog
{
    Q_OBJECT
private:
    cv::VideoCapture m_cameras[VStereoCalibrator::CAMERAS_COUNT];
    cv::Mat m_currentFrames[VStereoCalibrator::CAMERAS_COUNT];
    VStereoCalibrator m_stereoCalibrator;

    QTimer *m_timer;
    int m_interval;
private slots:
    void changeCameras();
    void start();
    void stop();
    void useCurrentFrames();
    void showNewFrames();
    void changeFPS();
    void changeTextFPS();
public:
    VStereoCalibrationDialog(QWidget *parent = 0);
};

#endif // STEREO_CALIBRATION_DIALOGS_H
