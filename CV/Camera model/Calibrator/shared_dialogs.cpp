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

#include "shared_dialogs.h"

VChooseModeDialog::VChooseModeDialog(QWidget *parent) :
        QDialog(parent),
        m_selectedMode(MONO_CALIBRATION)
{
    setupUi(this);
    setFixedSize(size());

    connect(m_monoRadio, SIGNAL(clicked()), this, SLOT(changeMode()));
    connect(m_stereoRadio, SIGNAL(clicked()), this, SLOT(changeMode()));
}

void VChooseModeDialog::changeMode()
{
    m_selectedMode = m_monoRadio->isChecked() ? MONO_CALIBRATION : STEREO_CALIBRATION;
}

VInitialValueDialog::VInitialValueDialog(QWidget *parent) :
        QDialog(parent),
        m_initialFocus(0),
        m_requiredFramesCount(0),
        m_squareLength(0)
{
    setupUi(this);
    setFixedSize(size());

    QRegExp regExp("[1-9][0-9]{0,5}");
    m_valueEdit->setValidator(new QRegExpValidator(regExp,this));
    m_lengthEdit->setValidator(new QRegExpValidator(regExp,this));
    regExp.setPattern("[1-9][0-9]");
    m_frameEdit->setValidator(new QRegExpValidator(regExp,this));

    connect(m_valueEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
    connect(m_frameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
    connect(m_lengthEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeOkButtonState()));
}

void VInitialValueDialog::changeOkButtonState()
{
    if(m_valueEdit->hasAcceptableInput() && m_frameEdit->hasAcceptableInput() && m_lengthEdit->hasAcceptableInput()) {
        m_okButton->setEnabled(true);
        m_initialFocus = m_valueEdit->text().toDouble();
        m_requiredFramesCount = m_frameEdit->text().toInt();
        m_squareLength = m_lengthEdit->text().toInt();
    }
    else
        m_okButton->setEnabled(false);
}
