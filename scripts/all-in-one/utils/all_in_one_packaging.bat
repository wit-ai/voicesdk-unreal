:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off
IF "%1"=="" GOTO arg_not_exists
set unrealVersion=%1

if exist output\ rmdir /s /q output
mkdir output

if exist workspace\ rmdir /s /q workspace
mkdir workspace

cd workspace

echo ">> 1. Download wit-unreal"
git clone -c core.longpaths=true https://github.com/wit-ai/wit-unreal

echo ">> 2. Download voicesdk-unreal"
git clone -c core.longpaths=true https://github.com/wit-ai/voicesdk-unreal

echo ">> 3. add WITH_VOICESDK macro for 'create preset' feature, this can be removed if 2 repos merged."
node ../../utils/update_WITH_VOICESDK_flag.js
node ../../utils/update_WITH_VOICESDK_MARKETPLACE_flag.js

echo ">> 4. Copy code and content from wit to voicesdk"
powershell -Command "cp ./wit-unreal/Source/* ./voicesdk-unreal/Source/ -recurse -force"

powershell -Command "Copy-Item ../../utils/VoiceSDK.uplugin -Destination ./voicesdk-unreal/"
powershell -Command "Copy-Item ../../utils/Config -Destination ./voicesdk-unreal/ -recurse"

echo ">> 5. Build"
if "%unrealVersion%"=="4.27" (SET vSVersion="-VS2019") else (SET vSVersion="")

set currDir=%CD%

cd "C:\Program Files\Epic Games\UE_%unrealVersion%\Engine\Build\BatchFiles"

call "RunUAT.bat" BuildPlugin -Rocket -Plugin="%currDir%\voicesdk-unreal\VoiceSDK.uplugin" -TargetPlatforms=Win64 -Package="%currDir%\..\output\voicesdk-unreal" %vSVersion%

if %ERRORLEVEL% neq 0 goto:eof

cd %currDir%
cd ..
..\\utils\\zip_all_in_one.bat

goto:eof

:arg_not_exists
echo Please run this command with Unreal version. For example: 4.27, 5.1 or 5.0
