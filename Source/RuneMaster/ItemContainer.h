// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UItemDataAsset;
/**
 * 
 */
struct RUNEMASTER_API FItemContainer
{
private:
	UItemDataAsset& Item;

public:
	uint16 Count = 0;

	FItemContainer(UItemDataAsset& ItemDataAsset, const uint16 ItemCount);
	~FItemContainer();

	UItemDataAsset& GetItem() const;
	FString GetItemName() const;
	UTexture2D* GetItemImage() const;
	uint16 GetItemMaxStackSize() const;
	
	bool operator==(const FItemContainer& Other) const;
};
