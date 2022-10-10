:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off

rmdir /s /q output
mkdir output
rmdir /s /q workspace
mkdir workspace

cd workspace

echo ">> 1. Download wit-unreal"
git clone https://github.com/wit-ai/wit-unreal
echo ">> 2. Download voicesdk-unreal"
git clone https://github.com/wit-ai/voicesdk-unreal

echo ">> 3. add WITH_VOICESDK macro for 'create preset' feature, this can be removed if 2 repos merged."
node ../update_WITH_VOICESDK_flag.js

echo ">> 4. Copy code and content from wit to voicesdk"
powershell -Command "cp ./wit-unreal/Source/* ./voicesdk-unreal/Source/ -recurse -force"
powershell -Command "Copy-Item ./wit-unreal/Content -Destination ./voicesdk-unreal/ -recurse -force"

powershell -Command "Copy-Item ../VoiceSDK.uplugin -Destination ./voicesdk-unreal/"
powershell -Command "Copy-Item ../Config -Destination ./voicesdk-unreal/ -recurse"

echo ">> 5. Build"
"C:\Program Files\Epic Games\UE_5.0\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Rocket -Plugin="%CD%\voicesdk-unreal\VoiceSDK.uplugin" -TargetPlatforms=Win64 -Package="%CD%\..\output\voicesdk-unreal" & cd .. & zip_all_in_one.bat
