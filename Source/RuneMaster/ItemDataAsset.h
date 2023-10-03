// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class RUNEMASTER_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FString GetItemName() const;
	UTexture2D* GetItemImage() const;
	uint16 GetStackSize() const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	FString ItemName;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemImage;
	UPROPERTY(EditDefaultsOnly)
	uint16 ItemStackSize = 100;
};
