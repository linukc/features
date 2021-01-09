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

#include "mono_calibration_dialogs.h"

#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include "shared_dialogs.h"

VChooseCameraDialog::VChooseCameraDialog(QWidget *parent) :
        QDialog(parent),
        m_selectedIndex(0)
{
    setupUi(this);
    setFixedSize(size());

    QRegExp regExp("[0-9]{1,2}");
    m_indexEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(m_indexEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
}

void VChooseCameraDialog::changeOkButtonState()
{
    if(m_indexEdit->hasAcceptableInput()) {
        m_selectedIndex=m_indexEdit->text().toInt();
        m_okButton->setEnabled(true);
    }
    else
        m_okButton->setEnabled(false);
}

VMonoCalibrationDialog::VMonoCalibrationDialog(QWidget *parent) :
        QDialog(parent),
        m_interval(200)
{
    setupUi(this);

    QSettings settings("Wicron","Calibrator");
    if(settings.contains("cameraIndex"))
        m_camera.open(settings.value("cameraIndex").toInt());
    else
        m_camera.open(CV_CAP_ANY);

    m_fpsEdit->setText(QString("%1").arg(1000 / m_interval));
    QRegExp regExp("[1-9][0-9]{0,2}");
    m_fpsEdit->setValidator(new QRegExpValidator(regExp, this));

    m_timer = new QTimer(this);
    if(m_camera.isOpened()) {
        m_videoWidget->setFixedSize((int)m_camera.get(CV_CAP_PROP_FRAME_WIDTH),
                                    (int)m_camera.get(CV_CAP_PROP_FRAME_HEIGHT));
        m_timer->start(m_interval);
        m_startButton->setEnabled(true);
    }

    connect(m_startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(m_useButton, SIGNAL(clicked()), this, SLOT(useCurrentFrame()));
    connect(m_changeButton, SIGNAL(clicked()), this, SLOT(changeCamera()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(showNewFrame()));
    connect(m_fpsButton, SIGNAL(clicked()), this, SLOT(changeFPS()));
    connect(m_fpsEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeTextFPS()));
}

void VMonoCalibrationDialog::changeCamera()
{
    VChooseCameraDialog dlg(this);
    int res;
    do {
        res = dlg.exec();
        if(res == QDialog::Accepted) {
            stop();
            m_camera.open(dlg.getSelectedIndex());
            if(m_camera.isOpened()) {
                m_timer->start(m_interval);
                stop();
                QSettings settings("Wicron","Calibrator");
                settings.setValue("cameraIndex", dlg.getSelectedIndex());
                m_videoWidget->setFixedSize((int)m_camera.get(CV_CAP_PROP_FRAME_WIDTH),
                                            (int)m_camera.get(CV_CAP_PROP_FRAME_HEIGHT));
            }
            else {
                m_timer->stop();
                showNewFrame();
                m_startButton->setEnabled(false);
                m_stopButton->setEnabled(false);
                m_useButton->setEnabled(false);
                QMessageBox::critical(this,"Error!", "Wrong camera's index!");
            }
        }
    }
    while(res == QDialog::Accepted && !m_camera.isOpened());
}
void VMonoCalibrationDialog::start()
{
    VInitialValueDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        m_monoCalibrator.setRequiredFramesCount(dlg.getRequiredFramesCount(),dlg.getSquareLength());
        m_monoCalibrator.setResolution(cv::Size((int)m_camera.get(CV_CAP_PROP_FRAME_WIDTH),
                                                (int)m_camera.get(CV_CAP_PROP_FRAME_HEIGHT)));
        m_monoCalibrator.start(dlg.getInitialValue());
        m_startButton->setEnabled(false);
        m_stopButton->setEnabled(true);
        m_useButton->setEnabled(true);
    }
}
void VMonoCalibrationDialog::stop()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    m_useButton->setEnabled(false);
    m_monoCalibrator.stop();
}
void VMonoCalibrationDialog::useCurrentFrame()
{
    if(m_monoCalibrator.tryFrame(m_currentFrame))
        m_videoWidget->showImage(m_currentFrame);
    else {
        if(m_monoCalibrator.calibrate()) {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save Results"),
                                                            QString::null, "yml (*.yml)");
            if(fileName != QString::null) {
                cv::Mat M, D, R, T, H;
                m_monoCalibrator.getIntrinsics(M,D);
                m_monoCalibrator.getExtrinsics(R,T);
                m_monoCalibrator.getHomography(H);
                cv::FileStorage fs(fileName.toStdString(), cv::FileStorage::WRITE);
                fs << "Camera matrix" << M << "Distortion coefficients" << D;
                fs << "Rotation vector" << R << "Translation vector" << T;
                fs << "Homography" << H;
            }
        }
        else
            QMessageBox::critical(this,"Error!","Error has occured during the calibration!");
        stop();
    }
}
void VMonoCalibrationDialog::showNewFrame()
{
    m_camera >> m_currentFrame;
    m_videoWidget->showImage(m_currentFrame);
}
void VMonoCalibrationDialog::changeFPS()
{
    m_timer->setInterval(m_interval);
}
void VMonoCalibrationDialog::changeTextFPS()
{
    if(m_fpsEdit->hasAcceptableInput()) {
        m_fpsButton->setEnabled(true);
        m_interval=1000/m_fpsEdit->text().toInt();
    }
    else
        m_fpsButton->setEnabled(false);
}

