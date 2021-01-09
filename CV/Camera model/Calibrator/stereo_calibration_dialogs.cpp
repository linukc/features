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

#include "stereo_calibration_dialogs.h"

#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>

#include "shared_dialogs.h"

VChooseCamerasDialog::VChooseCamerasDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setFixedSize(size());

    memset(m_selectedIndex, 0, sizeof(int) * VStereoCalibrator::CAMERAS_COUNT);

    QRegExp regExp("[0-9]{1,2}");
    m_leftIndexEdit->setValidator(new QRegExpValidator(regExp, this));
    m_rightIndexEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(m_leftIndexEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
    connect(m_rightIndexEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
}

void VChooseCamerasDialog::changeOkButtonState()
{
    if(m_leftIndexEdit->hasAcceptableInput() && m_rightIndexEdit->hasAcceptableInput()) {
        m_selectedIndex[VStereoCalibrator::LEFT_CAMERA]=m_leftIndexEdit->text().toInt();
        m_selectedIndex[VStereoCalibrator::RIGHT_CAMERA]=m_rightIndexEdit->text().toInt();
        m_okButton->setEnabled(true);
    }
    else
        m_okButton->setEnabled(false);
}

VStereoCalibrationDialog::VStereoCalibrationDialog(QWidget *parent) :
        QDialog(parent),
        m_interval(200)
{
    setupUi(this);

    m_fpsEdit->setText(QString("%1").arg(1000 / m_interval));
    QRegExp regExp("[1-9][0-9]{0,2}");
    m_fpsEdit->setValidator(new QRegExpValidator(regExp, this));

    m_timer = new QTimer(this);

    connect(m_startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(m_useButton, SIGNAL(clicked()), this, SLOT(useCurrentFrames()));
    connect(m_changeButton, SIGNAL(clicked()), this, SLOT(changeCameras()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(showNewFrames()));
    connect(m_fpsButton, SIGNAL(clicked()), this, SLOT(changeFPS()));
    connect(m_fpsEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeTextFPS()));
}

void VStereoCalibrationDialog::changeCameras()
{
    VChooseCamerasDialog dlg(this);
    int i, res, width, height;
    do {
        res = dlg.exec();
        if(res == QDialog::Accepted) {
            stop();
            for(i = 0; i < VStereoCalibrator::CAMERAS_COUNT; ++i)
                m_cameras[i].open(dlg.getSelectedIndex(i));
            if(m_cameras[VStereoCalibrator::LEFT_CAMERA].isOpened() &&
               m_cameras[VStereoCalibrator::RIGHT_CAMERA].isOpened()) {
                width = (int)m_cameras[VStereoCalibrator::LEFT_CAMERA].get(CV_CAP_PROP_FRAME_WIDTH);
                height = (int)m_cameras[VStereoCalibrator::LEFT_CAMERA].get(CV_CAP_PROP_FRAME_HEIGHT);
                if(width == (int)m_cameras[VStereoCalibrator::RIGHT_CAMERA].get(CV_CAP_PROP_FRAME_WIDTH) &&
                   height == (int)m_cameras[VStereoCalibrator::RIGHT_CAMERA].get(CV_CAP_PROP_FRAME_HEIGHT)) {
                    m_leftCameraWidget->setFixedSize(width, height);
                    m_rightCameraWidget->setFixedSize(width, height);
                    m_timer->start(m_interval);
                    stop();
                }
                else {
                    res = QDialog::Rejected;
                    QMessageBox::critical(this,"Error!", "Cameras must have the same resolution!");
                }
            }
            else {
                m_timer->stop();
                showNewFrames();
                m_startButton->setEnabled(false);
                m_stopButton->setEnabled(false);
                m_useButton->setEnabled(false);
                QMessageBox::critical(this,"Error!", "Wrong camera's index!");
            }
        }
    }
    while(res == QDialog::Accepted && !(m_cameras[VStereoCalibrator::LEFT_CAMERA].isOpened() &&
                                        m_cameras[VStereoCalibrator::RIGHT_CAMERA].isOpened()));
}
void VStereoCalibrationDialog::start()
{
    VInitialValueDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        m_stereoCalibrator.setRequiredFramesCount(dlg.getRequiredFramesCount(),dlg.getSquareLength());
        m_stereoCalibrator.setResolution(cv::Size((int)m_cameras[VStereoCalibrator::LEFT_CAMERA].get(CV_CAP_PROP_FRAME_WIDTH),
                                                  (int)m_cameras[VStereoCalibrator::LEFT_CAMERA].get(CV_CAP_PROP_FRAME_HEIGHT)));
        m_stereoCalibrator.start(dlg.getInitialValue());
        m_startButton->setEnabled(false);
        m_stopButton->setEnabled(true);
        m_useButton->setEnabled(true);
    }
}
void VStereoCalibrationDialog::stop()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    m_useButton->setEnabled(false);
    m_stereoCalibrator.stop();
}
void VStereoCalibrationDialog::useCurrentFrames()
{
    if(m_stereoCalibrator.tryFrames(m_currentFrames[VStereoCalibrator::LEFT_CAMERA],
                                    m_currentFrames[VStereoCalibrator::RIGHT_CAMERA])) {
        m_leftCameraWidget->showImage(m_currentFrames[VStereoCalibrator::LEFT_CAMERA]);
        m_rightCameraWidget->showImage(m_currentFrames[VStereoCalibrator::RIGHT_CAMERA]);
    }
    else {
        if(m_stereoCalibrator.calibrate()) {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save Results"),
                                                            QString::null, "yml (*.yml)");
            if(fileName != QString::null) {
                cv::Mat M[VStereoCalibrator::CAMERAS_COUNT], D[VStereoCalibrator::CAMERAS_COUNT], R, T, F, E;
                for(unsigned i = 0;i < VStereoCalibrator::CAMERAS_COUNT; ++i)
                    m_stereoCalibrator.getCamerasIntrinsics(i, M[i], D[i]);
                m_stereoCalibrator.getCamerasOrientation(R, T);
                m_stereoCalibrator.getEssentialMatrix(E);
                m_stereoCalibrator.getFundamentalMatrix(F);
                cv::FileStorage fs(fileName.toStdString(), cv::FileStorage::WRITE);
                fs << "Left camera matrix" <<M[VStereoCalibrator::LEFT_CAMERA] <<
                      "Left distortion coefficients" << D[VStereoCalibrator::LEFT_CAMERA];
                fs << "Right camera matrix" <<M[VStereoCalibrator::RIGHT_CAMERA] <<
                      "Right distortion coefficients" << D[VStereoCalibrator::RIGHT_CAMERA];
                fs << "Rotation matrix" << R << "Translation vector" << T;
                fs << "Essential matrix" << E << "Fundamental matrix" << F;
            }
        }
        else
            QMessageBox::critical(this,"Error!","Error has occured during the calibration!");
        stop();
    }
}
void VStereoCalibrationDialog::showNewFrames()
{
    for(unsigned i = 0; i < VStereoCalibrator::CAMERAS_COUNT; ++i)
        m_cameras[i] >> m_currentFrames[i];
    m_leftCameraWidget->showImage(m_currentFrames[VStereoCalibrator::LEFT_CAMERA]);
    m_rightCameraWidget->showImage(m_currentFrames[VStereoCalibrator::RIGHT_CAMERA]);
}
void VStereoCalibrationDialog::changeFPS()
{
    m_timer->setInterval(m_interval);
}
void VStereoCalibrationDialog::changeTextFPS()
{
    if(m_fpsEdit->hasAcceptableInput()) {
        m_fpsButton->setEnabled(true);
        m_interval=1000/m_fpsEdit->text().toInt();
    }
    else
        m_fpsButton->setEnabled(false);
}
