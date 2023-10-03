// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemContainer.h"
#include "ItemDataAsset.h"

FItemContainer::FItemContainer(UItemDataAsset& ItemDataAsset, const uint16 ItemCount) : Item(ItemDataAsset)
{
	Count = ItemCount;
}

FItemContainer::~FItemContainer()
{
}

UItemDataAsset& FItemContainer::GetItem() const
{
	return Item;
}

FString FItemContainer::GetItemName() const
{
	return Item.GetItemName();
}

UTexture2D* FItemContainer::GetItemImage() const
{
	return Item.GetItemImage();
}

uint16 FItemContainer::GetItemMaxStackSize() const
{
	return Item.GetStackSize();
}


bool FItemContainer::operator==(const FItemContainer& Other) const
{
	// Use the name of the Data Asset as they shouldn't have duplicates
	return this->Item.GetName() == Other.Item.GetName();
}
