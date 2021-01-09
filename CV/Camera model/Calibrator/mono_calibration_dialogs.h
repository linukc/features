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

#ifndef __MONO_CALIBRATION_DIALOGS_H
#define __MONO_CALIBRATION_DIALOGS_H

#include <opencv2/highgui/highgui.hpp>

#include "Core/v_mono_calibrator.h"

#include "ui_v_mono_calibration_dialog.h"
#include "ui_v_choose_camera_dialog.h"

class VChooseCameraDialog : public QDialog, private Ui::VChooseCameraDialog
{
    Q_OBJECT
private:
    int m_selectedIndex;
private slots:
    void changeOkButtonState();
public:
    VChooseCameraDialog(QWidget *parent = 0);

    int getSelectedIndex() const
    {
        return m_selectedIndex;
    }
};

class VMonoCalibrationDialog : public QDialog, private Ui::VMonoCalibrationDialog
{
    Q_OBJECT
private:
    cv::VideoCapture m_camera;
    cv::Mat m_currentFrame;
    VMonoCalibrator m_monoCalibrator;

    QTimer *m_timer;
    int m_interval;
private slots:
    void changeCamera();
    void start();
    void stop();
    void useCurrentFrame();
    void showNewFrame();
    void changeFPS();
    void changeTextFPS();
public:
    VMonoCalibrationDialog(QWidget *parent = 0);
};

#endif // __MONO_CALIBRATION_DIALOGS_H
