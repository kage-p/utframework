#pragma once
#include <string>
#include <gtest/gtest.h>

namespace UnitTestSupport
{
	class CUnitTest : public testing::Test
	{

	protected:

        // test support functions
		static std::wstring getExecutablePath();
		static std::wstring getFileData(std::wstring file);
		static void logText(std::string text);
		static void logText(std::wstring text);

		static std::wstring getTestPath(std::wstring base);
		static void setupFolder(std::wstring path);
		static void cleanupFolder(std::wstring path);

	};
}
