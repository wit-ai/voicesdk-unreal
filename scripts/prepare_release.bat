:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off
IF "%1"=="" GOTO arg_not_exists
IF "%2"=="" GOTO arg_not_exists
set version=%1
set versionName=%2
node update_Plugin_version.js %version% %versionName%
goto:eof

:arg_not_exists
echo Please run this command with version and versionName. For example: prepare_release.bat 46 46.0.1
