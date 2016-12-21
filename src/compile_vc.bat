@echo off

echo Please asure that you are in Visual Studio Command Prompt
pause

@echo on

rc resource.rc
cl.exe /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /EHsc /MT *.cpp resource.res /link /out:RapidPingOptimizer.exe "kernel32.lib" "user32.lib" "gdi32.lib" "advapi32.lib" "Comctl32.lib"

@echo off
pause
