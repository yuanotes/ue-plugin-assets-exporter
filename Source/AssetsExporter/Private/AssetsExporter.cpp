// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetsExporter.h"
#include "AssetsExporterStyle.h"
#include "AssetsExporterCommands.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FName AssetsExporterTabName("AssetsExporter");

#define LOCTEXT_NAMESPACE "FAssetsExporterModule"

void FAssetsExporterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssetsExporterStyle::Initialize();
	FAssetsExporterStyle::ReloadTextures();

	FAssetsExporterCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetsExporterCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAssetsExporterModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetsExporterModule::RegisterMenus));
}

void FAssetsExporterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetsExporterStyle::Shutdown();

	FAssetsExporterCommands::Unregister();
}

void FAssetsExporterModule::PluginButtonClicked()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	IAssetRegistry& AssetRegistry = AssetRegistryModule.GetRegistry();

	TArray<FAssetData> ObjectList;
	AssetRegistry.GetAllAssets(ObjectList, true);
	TArray<FString> AssetsToExport;
	for (const FAssetData& AssetData : ObjectList)
	{
		const FString ObjectPath = AssetData.ObjectPath.ToString();
		if (ObjectPath.StartsWith(TEXT("/Game")))
		{
			AssetsToExport.Push(ObjectPath);
		}
	}

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.ExportAssets(AssetsToExport, "D:/");
}

void FAssetsExporterModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAssetsExporterCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAssetsExporterCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetsExporterModule, AssetsExporter)