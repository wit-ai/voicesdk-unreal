/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "Modules/ModuleManager.h"


/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class IPlatformIntegration : public IModuleInterface
{
public:
	static inline IPlatformIntegration& Get()
	{
		return FModuleManager::LoadModuleChecked<IPlatformIntegration>("PlatformIntegration");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PlatformIntegration");
	}
};
