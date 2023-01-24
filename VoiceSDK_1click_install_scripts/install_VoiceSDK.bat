:: Copyright (c) Meta Platforms, Inc. and affiliates.
:: 
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

mkdir Plugins
cd Plugins
git clone https://github.com/wit-ai/voicesdk-unreal
git clone https://github.com/wit-ai/wit-unreal

cd ..

ECHO [Voice]>>.\\Config\\DefaultEngine.ini
ECHO bEnabled=true>>.\\Config\\DefaultEngine.ini
