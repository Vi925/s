@echo off
setlocal ENABLEDELAYEDEXPANSION



echo Copying text to clipboard...
echo lhflfhaldfhkdjafhkajhfdkd | clip

echo Waiting an additional 2 seconds...
ping -n 3 127.0.0.1 > nul

echo Debug: Running PowerShell automation...
powershell -ExecutionPolicy Bypass -File "%~dp0automation3.ps1"

echo Debug: Script execution completed.
pause
