
#include "unit_test.h"

#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

// Android note: unsupported for Android r21 or lower
// See https://android.googlesource.com/platform/ndk/+/master/docs/Roadmap.md
#if __cplusplus > 201402L // cpp17
#include <filesystem>
using namespace std::filesystem;
#else
#include <experimental/filesystem>
using namespace std::experimental::filesystem;
#endif

using namespace UnitTestSupport;


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns path of the current executable
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getExecutablePath()
{
#ifdef _WIN32
    std::wstring localPath;
    localPath.resize(MAX_PATH + 1);
    GetModuleFileNameW(
        nullptr,
        &localPath[0],
        MAX_PATH
    );
    auto n = localPath.find_last_of('\\');
    if (n != std::wstring::npos) localPath.resize(n);
    return localPath;
#else
    return current_path().wstring();
#endif
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns contents of a text file
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getTextFileData(const std::wstring& fileName)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8cnv;
    std::ifstream file(utf8cnv.to_bytes(fileName));

    if (!file.is_open() )
        return std::wstring();
    
    std::stringstream buffer;
    buffer << file.rdbuf();

    return utf8cnv.from_bytes(buffer.str());
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns contents of a text file in a vector with each item representing a line
//-----------------------------------------------------------------------------
std::vector<std::wstring> CUnitTest::getTextFileList(const std::wstring& fileName)
{
    std::vector<std::wstring> results;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8cnv;
    std::ifstream file(utf8cnv.to_bytes(fileName));
    
    if (!file.is_open())
        return results;

    std::string line;
    while (std::getline(file, line))
    {
        results.push_back(utf8cnv.from_bytes(line));
    }
    return results;
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Logs a text string to the debug console
//-----------------------------------------------------------------------------
void CUnitTest::logText(const std::string& text)
{
    std::cout << text;
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Logs a text string (unicode) to the debug console
//-----------------------------------------------------------------------------
void CUnitTest::logText(const std::wstring& text)
{
    std::wcout << text;
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns a validated directory which can be used for temporary files
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getTestPath(const std::wstring& base)
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
void CUnitTest::setupFolder(const std::wstring& path)
{
    // clear export folder and recreate
    cleanupFolder(path);

    try
    {
        create_directories(path);
    }
    catch (std::exception &ex)
    {
        // cannot remove
        std::wcout << L"CUnitTest::setupFolder(): Failed to create directory " << path << ". Error: " << ex.what() << std::endl;
    }
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Deletes directory contents and the directory itself
//-----------------------------------------------------------------------------
void CUnitTest::cleanupFolder(const std::wstring& path)
{
    if (!exists(path))
        return;

    try
    {
        remove_all(path);
    }
    catch (std::exception &ex)
    {
        // cannot remove
        std::wcout << L"CUnitTest::cleanupFolder(): Failed to remove directory " << path << ". Error: " << ex.what() << std::endl;
    }
}

