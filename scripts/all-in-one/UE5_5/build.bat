:: Copyright (c) Meta Platforms, Inc. and affiliates.
::
:: This source code is licensed under the license found in the
:: LICENSE file in the root directory of this source tree.

echo off

SET witBranch=%1
SET vsdkBranch=%2

../utils/all_in_one_packaging.bat 5.5 %witBranch% %vsdkBranch%
