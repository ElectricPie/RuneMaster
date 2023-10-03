// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UItemDataAsset;
/**
 * 
 */
struct RUNEMASTER_API FItemContainer
{
public:
	UItemDataAsset* Item = nullptr;
	uint16 Count = 0;

	FItemContainer(UItemDataAsset* ItemDataAsset, const uint16 ItemCount);
	~FItemContainer();
	
	bool operator==(const FItemContainer& Other) const;
};
