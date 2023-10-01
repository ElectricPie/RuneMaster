// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataAsset.h"

FString UItemDataAsset::GetItemName()
{
	return ItemName;
}

UTexture2D* UItemDataAsset::GetItemImage() const
{
	return ItemImage;
}
