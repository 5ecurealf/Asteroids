@echo off

GOTO BEGIN

:ERROR
echo SETUP ERROR
PAUSE
exit /B 1

:BEGIN
REM Build SDL
thirdparty\cmake\win\bin\cmake %* -S thirdparty\sdl -B thirdparty\sdl\build\win -DCMAKE_INSTALL_PREFIX=thirdparty\sdl\install\win
IF ERRORLEVEL 1 GOTO ERROR
thirdparty\cmake\win\bin\cmake --build thirdparty\sdl\build\win --config Debug --target install
IF ERRORLEVEL 1 GOTO ERROR
thirdparty\cmake\win\bin\cmake --build thirdparty\sdl\build\win --config RelWithDebInfo --target install
IF ERRORLEVEL 1 GOTO ERROR

REM Build project
thirdparty\cmake\win\bin\cmake %* -S asteroids -B build\win -DCMAKE_PREFIX_PATH="%cd%\thirdparty\sdl\install\win"
IF ERRORLEVEL 1 GOTO ERROR
thirdparty\cmake\win\bin\cmake --build build\win --config Debug
IF ERRORLEVEL 1 GOTO ERROR
thirdparty\cmake\win\bin\cmake --build build\win --config RelWithDebInfo
IF ERRORLEVEL 1 GOTO ERROR

echo SETUP SUCCESSFUL!
PAUSE