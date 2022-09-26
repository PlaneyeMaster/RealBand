#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Input/SComboBox.h"
//#include "SWebBrowser.h"
//#include "UI/BrowserBinding.h"
//#include "Framework/MultiBox/MultiBoxBuilder.h"
//#include "Framework/Docking/TabManager.h"


class FRealBandUIManagerImpl : public TSharedFromThis<FRealBandUIManagerImpl>
{

private:
	TSharedPtr<SCanvas> pCanvas;
	TSharedPtr<SOverlay> pOverlay;
	TSharedPtr<SButton> pSettings;
	TSharedPtr<SBox> pSettingsBox;
	TSharedPtr<SButton> pLocal;
	TSharedPtr<SButton> pImport;
	TSharedPtr<SWindow> pDialogMainWindow;
	TSharedPtr<SWindow> pSettingsWindow;
	TSharedPtr<SBox> pBox;
	TSharedPtr<SBorder> pBorder;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ProjectsCombo;
	TSharedPtr<STextBlock> pTextBlock;
	
	FReply LaunchSettings();
	FReply ApplySettings();
	FReply LaunchOpenFileDialog();
	TSharedPtr<SWidget> GenerateCBContent(TSharedPtr< FString > );
	void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
	TArray<TSharedPtr <FString>> Array_Resolutions; 
	TSharedPtr<FString> SelectedProject;

public:
	void Initialize();
	void CreateWindow();
	void CreateWindowEx();
	TSharedPtr<SDockTab> LocalBrowserDock;
	TSharedPtr<SWindow> DragDropWindow;
};


class FRealBandUIManager
{
public:
	static void Initialize();
	static TSharedPtr<FRealBandUIManagerImpl> Instance;
};
