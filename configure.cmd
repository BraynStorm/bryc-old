@echo off
setlocal
set "MODE=%1"
if "%MODE%" == "" ( set "MODE=Debug"; goto build )

if not exist "build\%MODE%" (mkdir "build\%MODE%")

:build
pushd "build\%MODE%"
cmake ..\.. -DCMAKE_BUILD_TYPE=%MODE% -GNinja
popd