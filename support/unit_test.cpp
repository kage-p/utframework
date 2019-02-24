
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "unit_test.h"

#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#include <filesystem>

using namespace UnitTestSupport;
using namespace std::experimental; // for vs2015

//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns path of the current executable
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getExecutablePath()
{
    std::wstring localPath;
    localPath.resize(MAX_PATH + 1);
    GetModuleFileNameW(
        nullptr,
        &localPath[0],
        MAX_PATH
    );
    int n = localPath.find_last_of('\\');
    if (n > 0) localPath.resize(n);
    return localPath;
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns contents of a text file
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getFileData(const std::wstring file)
{
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(buffer.str());
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
//
//-----------------------------------------------------------------------------
void CUnitTest::ASSERT_ISTRUE(bool expr, std::string msg)
{
   std::string output;
   if (!expr) {
      output = "ASSERT_ISTRUE ERROR: Was false. " + msg + "\n";
      // throw new std::exception(msg.c_str());
   }
   logText(output);   
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
//
//-----------------------------------------------------------------------------
void CUnitTest::ASSERT_EQUALS(int expected, int actual, std::string msg)
{
    std::string output;
    if (actual != expected) {
        output = "ASSERT_EQUALS: ERROR: Actual: " + std::to_string(actual) + ", expected: " + std::to_string(expected) + ". " + msg + "\n";
        // throw new std::exception(msg.c_str());
    }
    logText(output);
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Logs a text string to the debug console
//-----------------------------------------------------------------------------
void CUnitTest::logText(std::string text)
{
    // write to debug output
    OutputDebugStringA(text.c_str());
}

//-----------------------------------------------------------------------------
// [TestSupport]
//
// Logs a text string (unicode) to the debug console
//-----------------------------------------------------------------------------
void CUnitTest::logText(std::wstring text)
{
    // write to debug output
    OutputDebugStringW(text.c_str());
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns a validated directory which can be used for temporary files
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getTestPath(std::wstring base)
{
    std::wstring localPath = getExecutablePath() + L"\\" + base;
    setupFolder(localPath);
    return localPath;
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Cleans and recreates a directory
//-----------------------------------------------------------------------------
void CUnitTest::setupFolder(std::wstring path)
{
    // clear export folder and recreate
    cleanupFolder(path);
    filesystem::create_directory(path);
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Deletes directory contents and the directory itself
//-----------------------------------------------------------------------------
void CUnitTest::cleanupFolder(std::wstring path)
{
    if (filesystem::exists(path))
        filesystem::remove_all(path);
}

