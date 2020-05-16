
#include "unit_test.h"

#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#include <filesystem>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

using namespace UnitTestSupport;
using namespace std::experimental; // for vs2015

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
    int n = localPath.find_last_of('\\');
    if (n != std::wstring::npos) localPath.resize(n);
    return localPath;
#else
    return filesystem::current_path();
#endif
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns contents of a text file
//-----------------------------------------------------------------------------
std::wstring CUnitTest::getTextFileData(const std::wstring& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open() )
        return false;
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(buffer.str());
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Returns contents of a text file in a vector with each item representing a line
//-----------------------------------------------------------------------------
std::vector<std::wstring> CUnitTest::getTextFileList(const std::wstring& fileName)
{
    std::vector<std::wstring> results;
    std::ifstream file(fileName);
    
    if (!file.is_open())
        return results;

    std::string line;
    while (std::getline(file, line))
    {
        typedef std::codecvt_utf8<wchar_t> convert_type;
        std::wstring_convert<convert_type, wchar_t> converter;
        results.push_back(converter.from_bytes(line));
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
#ifdef _WIN32
    OutputDebugStringA(text.c_str());
#else
    std::cout << text;
#endif
}


//-----------------------------------------------------------------------------
// [TestSupport]
//
// Logs a text string (unicode) to the debug console
//-----------------------------------------------------------------------------
void CUnitTest::logText(const std::wstring& text)
{
#ifdef _WIN32
    OutputDebugStringW(text.c_str());
#else
    std::wcout << text;
#endif
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
        filesystem::create_directories(path);
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
    if (!filesystem::exists(path))
        return;

    try
    {
        filesystem::remove_all(path);
    }
    catch (std::exception &ex)
    {
        // cannot remove
        std::wcout << L"CUnitTest::cleanupFolder(): Failed to remove directory " << path << ". Error: " << ex.what() << std::endl;
    }
}

