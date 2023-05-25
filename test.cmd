@echo off
setlocal

call build.cmd
if %errorlevel% NEQ 0 ( exit /B %errorlevel% )

run\Debug\brycc
