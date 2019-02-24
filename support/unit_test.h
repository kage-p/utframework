#pragma once
#include <string>
#include "gmock/gmock.h"

namespace UnitTestSupport
{
	class CUnitTest
	{

	public:
		// implement by test classes
		virtual void runAllTests() = 0;

	protected:

		static std::wstring getExecutablePath();
		static std::wstring getFileData(std::wstring file);
		static void logText(std::string text);
		static void logText(std::wstring text);

		static std::wstring getTestPath(std::wstring base);
		static void setupFolder(std::wstring path);
		static void cleanupFolder(std::wstring path);

		static void ASSERT_ISTRUE(bool expr, std::string msg = "");
		static void ASSERT_EQUALS(int expected, int actual, std::string msg = "");

	};
}
