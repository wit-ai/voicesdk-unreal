/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

const readFileValueAsync = require("./readFileValueAsync");

const VERSION_NAME_KEY_STRING_START = '"VersionName": "';
const VERSION_NAME_KEY_STRING_END = '"';

return readFileValueAsync('VoiceSDK.uplugin', VERSION_NAME_KEY_STRING_START, VERSION_NAME_KEY_STRING_END, (version)=>{
  let formattedVersion = version.replace(/\./g, "_");
  console.log(formattedVersion);
});
