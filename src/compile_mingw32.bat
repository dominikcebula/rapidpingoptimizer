@echo off

echo Please asure that MINGW32 path is set propertly, Microsoft Windows SDK also needs to be installed in C:\Program Files\Microsoft SDKs\Windows\v7.0A
pause

@echo on

windres -o resource.o resource.rc
g++ -O2 -enable-auto-import -mwindows -o RapidPingOptimizer.exe *.cpp resource.o -D_WIN32_IE=0x0300 "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Comctl32.lib"

@echo off
pause
