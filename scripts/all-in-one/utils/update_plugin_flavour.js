/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

const updateFileAsync = require("../../helper");

const FILE_PATH = 'wit-unreal\\Source\\Wit\\Private\\Wit\\Request\\HTTP\\WitHttpRequest.cpp';
const PLUGIN_FLAVOUR_KEY_STRING_START = 'const FString PluginFlavour = FString("';
const PLUGIN_FLAVOUR_KEY_STRING_END = '"';

console.log(process.argv);

if(process.argv.length < 3) {
      console.log('Please call this script with : node update_Plugin_flavour.js xxx');
}

updateFileAsync(FILE_PATH, PLUGIN_FLAVOUR_KEY_STRING_START, process.argv[2], PLUGIN_FLAVOUR_KEY_STRING_END);
