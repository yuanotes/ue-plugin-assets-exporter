// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AssetsExporterStyle.h"

class FAssetsExporterCommands : public TCommands<FAssetsExporterCommands>
{
public:

	FAssetsExporterCommands()
		: TCommands<FAssetsExporterCommands>(TEXT("AssetsExporter"), NSLOCTEXT("Contexts", "AssetsExporter", "AssetsExporter Plugin"), NAME_None, FAssetsExporterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
