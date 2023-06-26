set BUILD_PLATFORM=win32-64
set BUILD_DIR=build-%BUILD_PLATFORM%
set BUILD_TYPE=Release
set BUILD_SHARED_LIBS=OFF
set BUILD_STATIC_LIBS=ON
REM set INSTALL_DIR=install-%BUILD_PLATFORM%

cd %BUILD_DIR%

ctest --verbose --build-config %BUILD_TYPE% --no-compress-output -T Test || verify > NUL