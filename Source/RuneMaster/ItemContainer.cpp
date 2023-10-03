// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemContainer.h"
#include "ItemDataAsset.h"

FItemContainer::FItemContainer(UItemDataAsset* ItemDataAsset, const uint16 ItemCount)
{
	Item = ItemDataAsset;
	Count = ItemCount;
}

FItemContainer::~FItemContainer()
{
}

bool FItemContainer::operator==(const FItemContainer& Other) const
{
	if (!Item || !Other.Item) return false;

	// Use the name of the Data Asset 
	return this->Item->GetName() == Other.Item->GetName();
}
