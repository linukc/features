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

#ifndef SHARED_DIALOGS_H
#define SHARED_DIALOGS_H

#include <QDialog>

#include "ui_v_choose_mode_dialog.h"
#include "ui_v_initial_value_dialog.h"

class VChooseModeDialog : public QDialog, private Ui::VChooseModeDialog
{
    Q_OBJECT
public:
    enum CalibrationMode
    {
        MONO_CALIBRATION,
        STEREO_CALIBRATION
    };
private:
    CalibrationMode m_selectedMode;
private slots:
    void changeMode();
public:
    VChooseModeDialog(QWidget *parent = 0);

    CalibrationMode getCalibrationMode() const
    {
        return m_selectedMode;
    }
};

class VInitialValueDialog : public QDialog, private Ui::VInitialValueDialog
{
    Q_OBJECT
private:
    qreal m_initialFocus;
    int m_requiredFramesCount;
    int m_squareLength;
private slots:
    void changeOkButtonState();
public:
    VInitialValueDialog(QWidget *parent = 0);

    qreal getInitialValue() const
    {
        return m_initialFocus;
    }
    int getRequiredFramesCount() const
    {
        return m_requiredFramesCount;
    }
    int getSquareLength() const
    {
        return m_squareLength;
    }
};

#endif // SHARED_DIALOGS_H
