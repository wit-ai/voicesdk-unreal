:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off

IF "%1"=="" (GOTO arg_not_exists) else (SET majorVersion=%1)
IF "%2"=="" (SET minorVersion="0") else (SET minorVersion=%2)
IF "%3"=="" (SET patchVersion="0") else (SET patchVersion=%3)

node update_Plugin_version.js %majorVersion% %minorVersion% %patchVersion%
goto:eof

:arg_not_exists
echo Please run this command with version code as 3 arguments for MAJOR MINOR PATCH. For example: prepare_release.bat 46 0 1
