@echo off
setlocal

set "MODE=%1"
if "%MODE%" == "" ( set "MODE=Debug"; goto build )

:build
cmake --build "build\%MODE%"