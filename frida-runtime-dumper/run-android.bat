@echo off
set /p PKG="Enter Android package name (e.g. com.company.game): "
frida -U -f %PKG% -l frida-dump-android.js --no-pause
pause
