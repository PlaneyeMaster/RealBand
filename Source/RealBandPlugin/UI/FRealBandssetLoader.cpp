

#include "FRealBandAssetLoader.h"
#include "Framework/Application/SlateApplication.h"
#include "SAssetView.h"
#include "Editor.h"

FRealBandAssetLoader::~FRealBandAssetLoader()
{

}


void FRealBandAssetLoader::SetAssetFolder(const FString & FolderPath)
{

}

void FRealBandAssetLoader::Construct(const FArguments& InArgs)
{
	OnAssetsActivated = InArgs._AssetPickerConfig.OnAssetsActivated;
	OnAssetSelected = InArgs._AssetPickerConfig.OnAssetSelected;
	OnAssetEnterPressed = InArgs._AssetPickerConfig.OnAssetEnterPressed;

	if (InArgs._AssetPickerConfig.bFocusSearchBoxWhenOpened)
	{
		RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &FRealBandAssetLoader::SetFocusPostConstruct));
	}

	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	ChildSlot
		[
			VerticalBox
		];

	FName AssetPath(InArgs._AssetPathConfig.DefaultPath);
	CurrentSourcesData = FSourcesData(InArgs._AssetPickerConfig.Filter.PackagePaths, InArgs._AssetPickerConfig.Collections);
	//CurrentSourcesData = FSourcesData(AssetPath);

	VerticalBox->AddSlot()
		.FillHeight(1.f)
		[
			SAssignNew(AssetViewPtr, SAssetView)
			.InitialViewType(EAssetViewType::Tile)
		    .InitialSourcesData(CurrentSourcesData)
		    .InitialThumbnailSize(EThumbnailSize::Small)
		    
		];

	if ( AssetViewPtr.IsValid() )
	{
		const FSourcesData SourcesData = AssetViewPtr->GetSourcesData();;
	}

	AssetViewPtr->RequestSlowFullListRefresh();
	AssetViewPtr->SetSourcesData(CurrentSourcesData);
}

EActiveTimerReturnType FRealBandAssetLoader::SetFocusPostConstruct(double InCurrentTime, float InDeltaTime)
{
	return EActiveTimerReturnType::Continue;
}

