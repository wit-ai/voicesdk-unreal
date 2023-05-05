:: Copyright (c) Meta Platforms, Inc. and affiliates.
:: 
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

if not exist Plugins\ mkdir Plugins
cd Plugins

if not exist voicesdk-unreal\ git clone -c core.longpaths=true https://github.com/wit-ai/voicesdk-unreal
if not exist wit-unreal\ git clone -c core.longpaths=true https://github.com/wit-ai/wit-unreal

cd voicesdk-unreal
git checkout main
git pull origin main

cd ..\wit-unreal
git checkout main
git pull origin main
