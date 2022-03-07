// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetsExporterCommands.h"

#define LOCTEXT_NAMESPACE "FAssetsExporterModule"

void FAssetsExporterCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AssetsExporter", "Execute AssetsExporter action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
