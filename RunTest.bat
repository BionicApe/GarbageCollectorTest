@echo off
rem Change to the directory where your project is located
cd /d "%~dp0"

rem Use WMIC to get the current date and time in the format YYYYMMDDHHMMSS
for /f "skip=1 tokens=1-7 delims=." %%A in ('wmic os get localdatetime') do (
    set datetime=%%A
    goto :break
)
:break

rem Get the full path of the project file (GarbageCollectorTest.uproject)
set projectpath=%cd%\GarbageCollectorTest.uproject

rem Set the log file name in the current directory with the correct format
set logfilepath=GarbageCollectionTest_%datetime%.log

rem Debug output to confirm the paths
echo Full project path: %projectpath%

rem Prompt the user to check the log file
echo.
echo Please check the log file: %cd%\Saved\%logfilepath%
echo.

rem Run the Unreal Automation Test with the full project path and log file name

"%UNREAL_BIN%\UnrealEditor-Cmd.exe" "%projectpath%" -ExecCmds="Automation RunTests GarbageCollectorTest.Runtime.GarbageCollectionTest" -unattended -nullrhi -Log=%logfilepath%
