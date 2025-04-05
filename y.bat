@echo off
setlocal ENABLEDELAYEDEXPANSION



echo Debug: Running PowerShell automation...
powershell -ExecutionPolicy Bypass -File "%~dp0automation2.ps1"

echo Debug: Script execution completed.
pause
