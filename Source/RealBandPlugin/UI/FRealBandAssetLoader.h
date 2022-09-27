#pragma once

#include "CoreMinimal.h"

//class header
//#include "FRealBandxportClass.h"
//Slate
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "AssetData.h"
#include "IContentBrowserSingleton.h"
#include "SourcesData.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SAssetView;

class FRealBandAssetLoader :public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(FRealBandAssetLoader) {}

	/** A struct containing details about how the asset picker should behave */
	SLATE_ARGUMENT(FAssetPickerConfig, AssetPickerConfig)
	SLATE_ARGUMENT(FPathPickerConfig, AssetPathConfig)

	SLATE_END_ARGS()

	virtual ~FRealBandAssetLoader();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetAssetFolder(const FString&);
	/** Return the associated AssetView */
	//const TSharedPtr<SAssetView>& GetAssetView() const { return AssetViewPtr; }
	///**
	// * Update the set of input Assets to be only based on the given set of Collections
	// * (or all Assets, if the Collections list is empty)
	// */
	//virtual void UpdateAssetSourceCollections(TArray<FCollectionNameType> Collections);
	///** Handle forwarding picking events. We wrap OnAssetSelected here to prevent 'Direct' selections being identified as user actions */
	//void HandleItemSelectionChanged(const FContentBrowserItem& InSelectedItem, ESelectInfo::Type InSelectInfo);

	///** Handler for when the user double clicks, presses enter, or presses space on an asset */
	//void HandleItemsActivated(TArrayView<const FContentBrowserItem> ActivatedItems, EAssetTypeActivationMethod::Type ActivationMethod);

	///** Forces a refresh */
	//void RefreshAssetView(bool bRefreshSources);

	///** @return The text to highlight on the assets  */
	//FText GetHighlightedText() const;

	/** Focuses the search box post-construct */
	EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);

private:

	/** The list of FrontendFilters currently applied to the asset view */
	TSharedPtr<FAssetFilterCollectionType> FrontendFilters;

	/** The asset view widget */
	TSharedPtr<SAssetView> AssetViewPtr;
	/** Called to when an asset is selected or the none button is pressed */
	FOnAssetSelected OnAssetSelected;

	/** Called when enter is pressed while an asset is selected */
	FOnAssetEnterPressed OnAssetEnterPressed;

	/** Called when any number of assets are activated */
	FOnAssetsActivated OnAssetsActivated;

	/** The sources data currently used by the picker */
	FSourcesData CurrentSourcesData;

	FSetPathPickerPathsDelegate SetPathsDelegate;

	
};