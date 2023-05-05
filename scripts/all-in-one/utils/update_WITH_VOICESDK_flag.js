/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

var fs = require('fs');
const updateFileAsync = require("../../updateFileAsync");

const FILE_PATH = 'wit-unreal\\Source\\WitEditor\\WitEditor.Build.cs';
const KEY_STRING_START = 'PrivateDefinitions.Add("WITH_VOICESDK=';
const KEY_STRING_END = '"';
const replacement = '1'

updateFileAsync(FILE_PATH, KEY_STRING_START, replacement, KEY_STRING_END);
