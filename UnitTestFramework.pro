
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

SOURCES +=\
    support/unit_test.cpp \
    gmock/src/gmock-all.cc \
    gtest/src/gtest-all.cc
