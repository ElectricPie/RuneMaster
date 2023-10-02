// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataAsset.h"

FString UItemDataAsset::GetItemName() const
{
	return ItemName;
}

UTexture2D* UItemDataAsset::GetItemImage() const
{
	return ItemImage;
}

uint16 UItemDataAsset::GetStackSize() const
{
	return ItemStackSize;
}
