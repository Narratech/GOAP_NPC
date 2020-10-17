// Copyright Epic Games, Inc. All Rights Reserved.

#include "GOAPNPC.h"

#define LOCTEXT_NAMESPACE "FGOAPNPCModule"

void FGOAPNPCModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGOAPNPCModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGOAPNPCModule, GOAPNPC)