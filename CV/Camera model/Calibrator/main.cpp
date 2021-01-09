/**
    @mainpage This is a program for calibration one or two cameras.

    @author Dmitry Suvorov

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

#include <QtGui/QApplication>

#include "mono_calibration_dialogs.h"
#include "stereo_calibration_dialogs.h"
#include "shared_dialogs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VChooseModeDialog dlg;
    if(dlg.exec()==QDialog::Accepted) {
        if(dlg.getCalibrationMode()==VChooseModeDialog::STEREO_CALIBRATION) {
            VStereoCalibrationDialog dlg;
            dlg.exec();
        }
        else {
            VMonoCalibrationDialog dlg;
            dlg.exec();
        }
    }
    return 0;
}
