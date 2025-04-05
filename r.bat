@echo off
setlocal ENABLEDELAYEDEXPANSION

echo Debug: Running PowerShell automation...
powershell -ExecutionPolicy Bypass -File "%~dp0automation4.ps1"

echo Debug: Script execution completed.
pause
