TARGET = Calibrator
QT += gui
TEMPLATE = app
BASE_DIRECTORY = ../

# Configurations
DEFINES += BASE_DIR="\\\""$$BASE_DIRECTORY/"\\\""
VPATH += $$BASE_DIRECTORY
DESTDIR = $$BASE_DIRECTORY/build
OBJECTS_DIR = $$BASE_DIRECTORY/build/.obj
MOC_DIR = $$BASE_DIRECTORY/build/.moc
RCC_DIR = $$BASE_DIRECTORY/build/.rcc
UI_DIR = $$BASE_DIRECTORY/build/.ui

# Targets
SOURCES += main.cpp
HEADERS += vvideowidget.h
SOURCES += vvideowidget.cpp
HEADERS += shared_dialogs.h
SOURCES += shared_dialogs.cpp
HEADERS += mono_calibration_dialogs.h
SOURCES += mono_calibration_dialogs.cpp
HEADERS += stereo_calibration_dialogs.h
SOURCES += stereo_calibration_dialogs.cpp
HEADERS += Core/v_abstract_calibrator.h
SOURCES += Core/v_abstract_calibrator.cpp
HEADERS += Core/v_mono_calibrator.h
SOURCES += Core/v_mono_calibrator.cpp
HEADERS += Core/v_stereo_calibrator.h
SOURCES += Core/v_stereo_calibrator.cpp

# UI
FORMS += Ui/v_choose_mode_dialog.ui
FORMS += Ui/v_initial_value_dialog.ui

FORMS += Ui/v_stereo_calibration_dialog.ui
FORMS += Ui/v_choose_cameras_dialog.ui

FORMS += Ui/v_mono_calibration_dialog.ui
FORMS += Ui/v_choose_camera_dialog.ui

# Linkage to OpenCV
LIBS += -lopencv_highgui
LIBS += -lopencv_calib3d

# Linkage to boost.
LIBS += -lboost_thread
