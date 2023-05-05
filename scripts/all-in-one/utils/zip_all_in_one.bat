:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

for %%I in (.) do set currDirName=%%~nxI

echo ">> 6. Zip the output"
cd output

powershell -Command "Copy-Item ../../utils/Config -Destination ./voicesdk-unreal/ -recurse"

if not exist voicesdk-unreal\Binaries\ goto:zip_failed
if not exist voicesdk-unreal\Intermediate\ goto:zip_failed

rmdir /s /q voicesdk-unreal\Binaries
rmdir /s /q voicesdk-unreal\Intermediate

set currPath=%CD%
cd ../../utils
for /f %%i in ('node read_Plugin_version.js') do set sdkVersion=%%i
cd %currPath%

set outputName=voicesdk-marketplace-%currDirName%-v%sdkVersion%.zip
powershell Compress-Archive voicesdk-unreal %outputName%
cd ..
echo "The Marketplace Unreal VoiceSDK plugin is ready in output/%outputName%"

goto:eof

:zip_failed
echo ARCHIVE FAILED
