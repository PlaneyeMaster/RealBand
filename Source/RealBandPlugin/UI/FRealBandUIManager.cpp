// Copyright RealEye, Inc. All Rights Reserved.
#include "UI/FRealBandUIManager.h"
#include "UI/FRealBandStyle.h"
//Widgets

#include "Widgets/SWindow.h"
#include "Widgets/SWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "Layout/ChildrenBase.h"

//List of Project files
#include "Interfaces/IProjectManager.h"

//File picker includes
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"



TSharedPtr<FRealBandUIManagerImpl> FRealBandUIManager::Instance;
const FName RealBandTabName = "RealBandTab";

void FRealBandUIManagerImpl::Initialize()
{
	 
//	Array_Resolutions.Add(MakeShareable<FString>(new FString("Project1")));
//	Array_Resolutions.Add(MakeShareable<FString>(new FString("Project2")));

	// Find all the engine installations
	TMap<FString, FString> EngineInstallations;
	FDesktopPlatformModule::Get()->EnumerateEngineInstallations(EngineInstallations);
	TSet<FString> AllFoundProjectFiles;

	for (TMap<FString, FString>::TConstIterator Iter(EngineInstallations); Iter; ++Iter)
	{
		TArray<FString> ProjectFiles;

		if (FDesktopPlatformModule::Get()->EnumerateProjectsKnownByEngine(Iter.Key(), false, ProjectFiles))
		{
			AllFoundProjectFiles.Append(MoveTemp(ProjectFiles));
		}
	}
	for (FString& ProjectFile : AllFoundProjectFiles)
	{
		FString ProjectFilename = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*ProjectFile);

		if (FPaths::FileExists(ProjectFilename))
		{
			FProjectStatus ProjectStatus;
			if (IProjectManager::Get().QueryStatusForProject(ProjectFilename, ProjectStatus))
			{
				// @todo localized project name
				const FText ProjectName = FText::FromString(ProjectStatus.Name);
				Array_Resolutions.Add(MakeShareable<FString>(new FString(ProjectStatus.Name)));
				
			}
			
		}
	}
//	Array_Resolutions.Add(MakeShareable<FString>(new FString("Project 1")));
//	Array_Resolutions.Add(MakeShareable<FString>(new FString("Project 2")));
	//Create the MainWindow
	CreateWindow();

}

void FRealBandUIManager::Initialize()
{
	
	if (!Instance.IsValid())
	{
	//	//Instance = MakeUnique<FBridgeUIManagerImpl>();
		FRealBandStyle::Initialize();
		Instance = MakeShareable(new FRealBandUIManagerImpl);
	
		}
	Instance->Initialize();
}

TSharedPtr<STextBlock> ComboBoxTitleBlock;

void FRealBandUIManagerImpl::CreateWindow()
{

	if (!pDialogMainWindow)
	{
		//TSharedPtr<FString> SelectedProject = (*Array_Resolutions.begin());
		SelectedProject = (*Array_Resolutions.begin());
		pDialogMainWindow = SNew(SWindow)
			.Title(FText::FromString("RealBand"))
			.ClientSize(FVector2D(1000, 650))
			.SupportsMaximize(false)
			.SupportsMinimize(false)

			[
				//SNew(SOverlay)
				SAssignNew(pOverlay, SOverlay)
				+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SCanvas)
				+ SCanvas::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Size(FVector2D(100.0f, 50.0f))
			.Position(FVector2D(30.0f, 80.0f))
			[
				SNew(SButton)
				//SNew(SButton)
				.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(FText::FromString("Local"))
			

			]
		+ SCanvas::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Size(FVector2D(100.0f, 50.0f))
			.Position(FVector2D(30.0f, 180.0f))
			[
				SAssignNew(pSettings, SButton)
				.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(FText::FromString("Settings"))
			.OnClicked(this, &FRealBandUIManagerImpl::LaunchSettings)
			]
		+ SCanvas::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Size(FVector2D(100.0f, 50.0f))
			.Position(FVector2D(750.0f, 5.0f))
			[
				SAssignNew(pImport, SButton)
				//SNew(SButton)
				.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(FText::FromString("Import"))
			]
		    + SCanvas::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Position(FVector2D(50.0f, 105.0f))
			[
				//SNew(SBorder)
				//.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				//.BorderBackgroundColor(FLinearColor(0.4352F, 0.3647F, 0.8862F))
				//.Padding(3.0f)
				//[
				    SAssignNew(pSettingsBox, SBox)
				    //SNew(SBox)
				    .HAlign(HAlign_Center)
		            .VAlign(VAlign_Center)
				    .WidthOverride(400.0f)
			       [
					   SNew(SBorder)
					//   .BorderImage(FPaths::EnginePluginsDir() / TEXT("Bridge/Resources"))
				    //   .BorderBackgroundColor(FLinearColor(0.4352F, 0.3647F, 0.8862F))
				       
				       .Padding(3.0f)
				     [
			           SNew(SCanvas)
			          + SCanvas::Slot()
			          .HAlign(HAlign_Fill)
			          .VAlign(VAlign_Fill)
			          .Size(FVector2D(130.0f, 50.0f))
			          .Position(FVector2D(130.0f, 20.0f))
			          [
					     SNew(STextBlock)
					    .AutoWrapText(true)
			            .Text(FText::FromString("Download folder"))
				        .ColorAndOpacity(FLinearColor(0.4352F, 0.3647F, 0.8862F))
						 //& FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText")
						 .TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))
			         //.TextStyle(FRealBandStyle::Get(), "RealBandStyle")

			           ]
				
		             + SCanvas::Slot()
			         .HAlign(HAlign_Fill)
			         .VAlign(VAlign_Fill)
			         .Size(FVector2D(30.0f, 30.0f))
			         .Position(FVector2D(130.0f, 70.0f))
			         [
				         SNew(STextBlock)
				        .AutoWrapText(true)
			            .Text(FText::FromString("Path"))
					    .ColorAndOpacity(FLinearColor(0.4352F, 0.3647F, 0.8862F))
					
			      //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

			         ]
					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(280.0f, 30.0f))
						 .Position(FVector2D(300.0f, 70.0f))
						 [
							 SNew(SEditableTextBox)
						     .Text(FText::FromString("Select the Loca Path to Asset Folder"))
						 

						 //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

						 ]
					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(20.0f, 20.0f))
						 .Position(FVector2D(590.0f, 70.0f))
						 [
							 SNew(SButton)
							 .HAlign(HAlign_Center)
						     .VAlign(VAlign_Center)
						     .OnClicked(this, &FRealBandUIManagerImpl::LaunchOpenFileDialog)
							 //.Text(FText::FromString("Select the Loca Path to Asset Folder"))


						 //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

						 ]
					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(130.0f, 90.0f))
						 .Position(FVector2D(130.0f, 130.0f))
						 [
							 SNew(STextBlock)
							 .AutoWrapText(true)
						     .Text(FText::FromString("Unreal PluginConnect"))
						     .ColorAndOpacity(FLinearColor(0.4352F, 0.3647F, 0.8862F))
						 ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(130.0f, 120.0f))
						 .Position(FVector2D(130.0f, 170.0f))
						 [
							 SNew(STextBlock)
							 .AutoWrapText(true)
						 .Text(FText::FromString("Path"))
						 .ColorAndOpacity(FLinearColor(0.4352F, 0.3647F, 0.8862F))
						 ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(280.0f, 30.0f))
						 .Position(FVector2D(300.0f, 170.0f))
						 [
							 SNew(SEditableTextBox)
							 .Text(FText::FromString("Select the Path to Asset Folder"))


						 //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

						 ]
					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(20.0f, 20.0f))
						 .Position(FVector2D(590.0f, 170.0f))
						 [
							 SNew(SButton)
							 .HAlign(HAlign_Center)
						     .VAlign(VAlign_Center)
						     .OnClicked(this, &FRealBandUIManagerImpl::LaunchOpenFileDialog)


						 //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

						 ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(130.0f, 120.0f))
						 .Position(FVector2D(130.0f, 220.0f))
						 [
							 SNew(STextBlock)
							 .AutoWrapText(true)
						 .Text(FText::FromString("Project"))
						 .ColorAndOpacity(FLinearColor(0.4352F, 0.3647F, 0.8862F))
						 ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(130.0f, 40.0f))
						 .Position(FVector2D(300.0f, 220.0f))
						 [
							 
							 SNew(SHorizontalBox)
							 + SHorizontalBox::Slot()
						      .VAlign(VAlign_Fill)
						      .HAlign(HAlign_Fill)
						      .AutoWidth()
						     [
								 
								 SAssignNew(ProjectsCombo, SComboBox<TSharedPtr<FString>>)
						
								 .OptionsSource(&Array_Resolutions)
						         
						         .OnSelectionChanged_Lambda([this](TSharedPtr<FString> Value, ESelectInfo::Type)
									 {
										// SAssignNew(ComboBoxTitleBlock, STextBlock).Text(FText::FromString("ComboLabel"));
											 //	 SNew(STextBlock).Text(FText::FromString(*SelectedProject.Get()));
									//		 if (SelectedProject.Get())
											 {
												 SelectedProject = Value;
												 //ProjectsCombo->ClearSelection();
												 ProjectsCombo->SetSelectedItem(Value);
												
												 //TSharedPtr<FString> ValueS = ProjectsCombo->GetSelectedItem();
												 ProjectsCombo->RefreshOptions();
												 pTextBlock->SetText(FText::FromString(*SelectedProject.Get()));
											 }
				
									 })

		
						       
									
						         .OnGenerateWidget_Lambda([this](TSharedPtr< FString > Value)
							     {
									//	 SelectedProject = Value;
								     return SNew(STextBlock).Text(FText::FromString(*Value));
									
									 })
								.InitiallySelectedItem(SelectedProject)
								 [
									 SAssignNew(pTextBlock,STextBlock)
									 .Text(FText::FromString(*SelectedProject.Get()))
								 ]
								 /*.Content()
									 [
										 
										 SNew(STextBlock)
									    .Text(FText::FromString(*SelectedProject.Get()))
								     ]*/
						         ]
						 ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(100.0f, 50.0f))
						 .Position(FVector2D(690.0f, 290.0f))
						 [
							 SNew(SButton)
							 .HAlign(HAlign_Center)
						 .VAlign(VAlign_Center)
						 .Text(FText::FromString("Apply"))
						 .OnClicked(this, &FRealBandUIManagerImpl::ApplySettings)


					 //    .TextStyle(FRealBandStyle::Get(), "RealBandStyle")

						 ]

					 ]// SBorder
			      ]
				//]
			    
			]


			]

			]

			];


		FSlateApplication::Get().AddWindow(pDialogMainWindow.ToSharedRef());

		pSettingsBox->SetVisibility(EVisibility::Hidden);

	}
//	SAssignNew(Canvas, SCanvas).FArguments(Slot().SetSize(FVector2D(700, 700)));
	//if (Windows.Num() > 0)
	{
//		FVector2D MainWindowSize = Windows[0]->GetSizeInScreen();
		float DesiredWidth = 1650;
		float DesiredHeight = 900;

	//	SAssignNew(Canvas, SCanvas);
		
		
		
		//if (DesiredWidth < MainWindowSize.X && DesiredHeight < MainWindowSize.Y && Canvas->GetParentWindow().IsValid())
		{
			// If Bridge is docked as a tab, the parent window will be the main window
		
			//Canvas->Resize(FVector2D(DesiredWidth, DesiredHeight));
			//LocalBrowserDock->GetParentWindow()->MoveWindowTo(FVector2D((MainWindowSize.X - DesiredWidth) - 17, MainWindowSize.Y - DesiredHeight) / 2);
		}
	}

	
//	auto obj = pContent->GetChildren();
	// 
	//TSharedRef<const FChildren*>  pChilderen = TSharedRef<const FChildren*>(pContent->GetChildren());
	

}


void FRealBandUIManagerImpl::HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (Item.IsValid())
	{
		// This will call back into this widget to refresh it
		//EditorModule->SetCurrentRegistrySource(*Item);
	}
}

FReply FRealBandUIManagerImpl::LaunchSettings()
{

	pSettingsBox->SetVisibility(EVisibility::Visible);
	pImport->SetVisibility(EVisibility::Collapsed);
	return FReply::Handled();
}


FReply FRealBandUIManagerImpl::ApplySettings()
{

	pSettingsBox->SetVisibility(EVisibility::Collapsed);
	pImport->SetVisibility(EVisibility::Visible);

	return FReply::Handled();
}

FReply FRealBandUIManagerImpl::LaunchOpenFileDialog()
{

	
	//		void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
			IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
			if (pDialogMainWindow)
			{
				//Opening the file picker!
				uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
				FString FolderPath;
				FString DefaultPath("C:\\Temp");
				DesktopPlatform->OpenDirectoryDialog(pDialogMainWindow->GetNativeWindow()->GetOSWindowHandle(),
					                                 DefaultPath,
					                                 DefaultPath, 
					                                 FolderPath);
	//			DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
			}
	//	}
	//}

	return FReply::Handled();
}


TSharedPtr<SWidget> FRealBandUIManagerImpl::GenerateCBContent(TSharedPtr< FString > Value)
{
	return SNew(STextBlock).Text(FText::FromString(*Value));
}