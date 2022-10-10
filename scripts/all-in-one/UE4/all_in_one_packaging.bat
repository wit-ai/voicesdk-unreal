:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

rmdir /s /q output
mkdir output
rmdir /s /q workspace
mkdir workspace

cd workspace

git clone https://github.com/wit-ai/voicesdk-unreal
git clone https://github.com/wit-ai/wit-unreal

cd voicesdk-unreal
rmdir /s /q .git
rmdir /s /q scripts

cd ..
cd wit-unreal
rmdir /s /q .git
rmdir /s /q scripts

cd ..

powershell Compress-Archive -Path wit-unreal, voicesdk-unreal -DestinationPath ../output/voicesdk-all-in-one-ue4.zip
cd ..
echo "The UE4 VoiceSDK all-in-one plugin is ready in output/voicesdk-all-in-one-ue4.zip"
