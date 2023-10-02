// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "ItemDataAsset.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ItemStacks = TArray<FItemContainer>();
	
	if (!DebugItem) return;
	
	FItemContainer DebugItemOne = {
		*DebugItem, // Item
		50 // Count
	};

	FItemContainer DebugItemTwo = {
		*DebugItem, // Item
		20 // Count
	};

	AddItem(DebugItemOne);
	AddItem(DebugItemTwo);
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::AddItem(FItemContainer& ItemContainer)
{
	UE_LOG(LogTemp, Warning, TEXT("Boop"));

	// Predicate to check if the item is already in the inventory
	auto Predicate = [&ItemContainer](const FItemContainer& ArrayItem)
	{
		return ArrayItem.Item.GetName() == ItemContainer.Item.GetName();
	};

	if (ItemStacks.ContainsByPredicate(Predicate))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item %s is in inventory"), *ItemContainer.Item.GetItemName());
	}
	else
	{
		ItemStacks.Add(ItemContainer);
	}
	
	return false;
}
