/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

const updateFileAsync = require("./helper");

const VERSION_KEY_STRING_START = '"Version": ';
const VERSION_KEY_STRING_END = ',';
const VERSION_NAME_KEY_STRING_START = '"VersionName": "';
const VERSION_NAME_KEY_STRING_END = '"';

console.log(process.argv);

if(process.argv.length < 4) {
      console.log('Please call this script with : node update_Plugin_version.js 123 1.2.3');
}

updateFileAsync('..\\VoiceSDK.uplugin', VERSION_KEY_STRING_START,process.argv[2] , VERSION_KEY_STRING_END, ()=>{
  updateFileAsync('..\\VoiceSDK.uplugin', VERSION_NAME_KEY_STRING_START,process.argv[3] , VERSION_NAME_KEY_STRING_END);
});

updateFileAsync('all-in-one\\UE5\\VoiceSDK.uplugin', VERSION_KEY_STRING_START,process.argv[2] , VERSION_KEY_STRING_END, ()=>{
  updateFileAsync('all-in-one\\UE5\\VoiceSDK.uplugin', VERSION_NAME_KEY_STRING_START,process.argv[3] , VERSION_NAME_KEY_STRING_END);
});
