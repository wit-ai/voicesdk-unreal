/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

var fs = require('fs');

function updateFileAsync(filePath, keyStringStart, replacement, keyStringEnd, callback) {
  fs.readFile(filePath, 'utf-8', function(err, data){
    if (err) throw err;
    let keyStringIndexStart = data.indexOf(keyStringStart);
    if(keyStringIndexStart === -1) {
      console.log(`Cannot find ${keyStringStart}, please check ${filePath}`);
      return;
    }
    keyStringIndexStart = keyStringIndexStart + keyStringStart.length;
    let keyStringIndexEnd = data.substring(keyStringIndexStart).indexOf(keyStringEnd);
    keyStringIndexEnd = keyStringIndexStart + keyStringIndexEnd;

    data = data.substring(0, keyStringIndexStart) + replacement + data.substring(keyStringIndexEnd);

    fs.writeFile(filePath, data, 'utf-8', function (err) {
      if (err) throw err;
      console.log(`${filePath} update complete`);
      if(callback) {
        callback();
      }
    });
  });
}
module.exports = updateFileAsync;
