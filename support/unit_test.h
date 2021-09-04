#pragma once
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace UnitTestSupport
{
    class CUnitTest : public testing::Test
    {
    protected:

        // test support functions
        static std::wstring getExecutablePath();
        static std::wstring getTextFileData(const std::wstring& fileName);
        static std::vector<std::wstring> getTextFileList(const std::wstring& fileName);
        static void logText(const std::string& text);
        static void logText(const std::wstring& text);

        static std::wstring getTestPath(const std::wstring& base);
        static bool setupFolder(const std::wstring& path);
        static bool cleanupFolder(const std::wstring& path);

    };
}
