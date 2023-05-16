:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

IF "%1"=="" (SET witBranch="main") else (SET witBranch=%1)
IF "%2"=="" (SET vsdkBranch=%witBranch%) else (SET vsdkBranch=%2)

if exist output\ rmdir /s /q output
mkdir output

if exist workspace\ rmdir /s /q workspace
mkdir workspace

cd workspace

git clone -c core.longpaths=true https://github.com/wit-ai/voicesdk-unreal
git clone -c core.longpaths=true https://github.com/wit-ai/wit-unreal

cd voicesdk-unreal
git checkout -b build origin/%vsdkBranch%
rmdir /s /q .git
rmdir /s /q scripts

cd ..\wit-unreal
git checkout -b build origin/%witBranch%
rmdir /s /q .git
rmdir /s /q scripts

set currPath=%CD%
cd ../../../utils
for /f %%i in ('node read_Plugin_version.js') do set sdkVersion=%%i
cd %currPath%

cd ..
set outputName=voicesdk-all-in-one-UE4-v%sdkVersion%.zip
powershell Compress-Archive -Path wit-unreal, voicesdk-unreal -DestinationPath ../output/%outputName%

cd ..
echo "The UE4 VoiceSDK all-in-one plugin is ready in output/%outputName%"
