
CONFIG += c++11 staticlib

TARGET = UnitTestFramework
TEMPLATE = lib

CONFIG(debug, debug|release): DEFINES += _DEBUG

INCLUDEPATH += \
            gmock/include \
            gmock \
            gtest/include \
            gtest

HEADERS += \
    support/unit_test.h

SOURCES += \
    support/unit_test.cpp \
    gmock/src/gmock-all.cc \
    gtest/src/gtest-all.cc


# Windows-specific definitions
windows {

    QMAKE_CXXFLAGS += /J
    DEFINES += _WIN32

    # Library dependencies (Windows-specific)
    LIBS += -luser32 \
          -lgdi32 \
          -ladvapi32 \
          -lws2_32 \
          -lshlwapi \
          -lwinspool \
          -lcomdlg32 \
          -lcomctl32 \
          -lshell32 \
          -lole32 \
          -loleaut32 \
          -lwinmm

    # MSVC: Always use static runtime library
    QMAKE_CFLAGS_MT =-MT
    QMAKE_CFLAGS_MT_DBG =-MTd
    QMAKE_CFLAGS_MT_DLL =-MD
    QMAKE_CFLAGS_MT_DLLDBG =-MDd

    QMAKE_CFLAGS_RELEASE -= $$QMAKE_CFLAGS_MT_DLL
    QMAKE_CFLAGS_RELEASE += $$QMAKE_CFLAGS_MT
    QMAKE_CXXFLAGS_RELEASE -= $$QMAKE_CFLAGS_MT_DLL
    QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_MT

    QMAKE_CFLAGS_DEBUG -= $$QMAKE_CFLAGS_MT_DLLDBG
    QMAKE_CFLAGS_DEBUG += $$QMAKE_CFLAGS_MT_DBG
    QMAKE_CXXFLAGS_DEBUG -= $$QMAKE_CFLAGS_MT_DLLDBG
    QMAKE_CXXFLAGS_DEBUG += $$QMAKE_CFLAGS_MT_DBG
}
