@echo off
chcp 65001

cd /d %~dp0

echo progress=50
echo off
echo "生成Win64项目"
echo "Generate for Visual Studio 2022"
cd /d %~dp0
cmake.exe -G "Visual Studio 17 2022" -A x64 ../ -DRP3D_COMPILE_TESTBED=ON
echo "生成完毕"
if "%~1" == "--skipPause" goto End
pause
:End
exit %errorlevel%