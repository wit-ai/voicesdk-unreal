:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off
IF "%1"=="" GOTO arg_not_exists
set unrealVersion=%1

IF "%2"=="" (SET witBranch="main") else (SET witBranch=%2)
IF "%3"=="" (SET vsdkBranch=%witBranch%) else (SET vsdkBranch=%3)

if exist output\ rmdir /s /q output
mkdir output

if exist workspace\ rmdir /s /q workspace
mkdir workspace

cd workspace

echo ">> 1. Download wit-unreal"
git clone -c core.longpaths=true https://github.com/wit-ai/wit-unreal

cd wit-unreal
git checkout -b build origin/%witBranch%
cd ..

echo ">> 2. Download voicesdk-unreal"
git clone -c core.longpaths=true https://github.com/wit-ai/voicesdk-unreal

cd voicesdk-unreal
git checkout -b build origin/%vsdkBranch%
cd ..

echo ">> 3. add WITH_VOICESDK macro for 'create preset' feature, this can be removed if 2 repos merged."
node ../../utils/update_WITH_VOICESDK_flag.js
node ../../utils/update_WITH_VOICESDK_MARKETPLACE_flag.js

echo ">> 4. Copy code and content from wit to voicesdk"
powershell -Command "Copy-Item ./wit-unreal/Source/* ./voicesdk-unreal/Source/ -recurse -force"

powershell -Command "Copy-Item ../../utils/VoiceSDK.uplugin -Destination ./voicesdk-unreal/"
powershell -Command "Copy-Item ../../utils/Config -Destination ./voicesdk-unreal/ -recurse"

echo ">> 5. Build"
if "%unrealVersion%"=="4.27" (SET vSVersion="-VS2019") else (SET vSVersion="")

set currDir=%CD%

cd "C:\Program Files\Epic Games\UE_%unrealVersion%\Engine\Build\BatchFiles"

call "RunUAT.bat" BuildPlugin -Rocket -clean -Plugin="%currDir%\voicesdk-unreal\VoiceSDK.uplugin" -TargetPlatforms=Win64 -package="%currDir%\..\output\voicesdk-unreal" %vSVersion%

if %ERRORLEVEL% neq 0 goto:eof

cd %currDir%
cd ..
..\\utils\\zip_all_in_one.bat

goto:eof

:arg_not_exists
echo Please run this command with Unreal version. For example: 4.27, 5.1 or 5.0
