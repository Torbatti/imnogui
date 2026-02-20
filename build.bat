
@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"
:restart

if not exist build mkdir build
if not exist local mkdir local
zig cc ./app-imnogui/src/app.c -o build/imnogui.exe -Ivendor-glad/v2.0.8 -luser32 -lgdi32 -lopengl32
