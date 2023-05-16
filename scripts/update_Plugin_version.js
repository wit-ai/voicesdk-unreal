/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

const updateFileAsync = require("./updateFileAsync");

const VERSION_KEY_STRING_START = '"Version": ';
const VERSION_KEY_STRING_END = ',';
const VERSION_NAME_KEY_STRING_START = '"VersionName": "';
const VERSION_NAME_KEY_STRING_END = '"';

console.log(process.argv);

if(process.argv.length < 3) {
      console.log('Please call this script with MAJOR MINOR and PATCH version codes : node update_Plugin_version.js 123 0 1');
}

const majorVersion = process.argv[2];
let minorVersion = '0'
let patchVersion = '0'

if(process.argv.length >= 4) {
  minorVersion = process.argv[3];
}

if(process.argv.length >= 5) {
  patchVersion = process.argv[4];
}

const versionName = majorVersion + '.' + minorVersion + '.' + patchVersion;

updateFileAsync('..\\VoiceSDK.uplugin', VERSION_KEY_STRING_START, majorVersion, VERSION_KEY_STRING_END, ()=>{
  updateFileAsync('..\\VoiceSDK.uplugin', VERSION_NAME_KEY_STRING_START, versionName, VERSION_NAME_KEY_STRING_END);
});

updateFileAsync('all-in-one\\utils\\VoiceSDK.uplugin', VERSION_KEY_STRING_START, majorVersion, VERSION_KEY_STRING_END, ()=>{
  updateFileAsync('all-in-one\\utils\\VoiceSDK.uplugin', VERSION_NAME_KEY_STRING_START, versionName, VERSION_NAME_KEY_STRING_END);
});
