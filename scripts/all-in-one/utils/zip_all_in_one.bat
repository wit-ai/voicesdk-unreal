:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo ">> 6. Zip the output"
cd output
powershell -Command "Copy-Item ../../utils/Config -Destination ./voicesdk-unreal/ -recurse"
rmdir /s /q voicesdk-unreal\Binaries
rmdir /s /q voicesdk-unreal\Intermediate
powershell Compress-Archive voicesdk-unreal voicesdk-marketplace.zip
cd ..
echo "The Marketplace Unreal VoiceSDK plugin is ready in output/voicesdk-marketplace.zip"
