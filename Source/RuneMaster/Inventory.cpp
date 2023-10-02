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
	ItemStacks = TArray<FItemContainer*>();
	ItemStacks.Init(nullptr, InventorySlotCount);
	
	if (!DebugItemDAOne || !DebugItemDATwo) return;
	
	FItemContainer DebugItemOne = {
		*DebugItemDAOne, // Item
		50 // Count
	};

	FItemContainer DebugItemTwo = {
		*DebugItemDATwo, // Item
		20 // Count
	};

	FItemContainer* SwappedItemOne = SwapItem(&DebugItemOne, 1);
	if (SwappedItemOne)
	{
		UE_LOG(LogTemp, Warning, TEXT("Returned %i of %s"), SwappedItemOne->Count, *SwappedItemOne->Item.GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item 1 No items returned"));
	}
	
	FItemContainer* SwappedItemTwo = SwapItem(&DebugItemTwo, 1);
	if (SwappedItemTwo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Returned %i of %s"), SwappedItemTwo->Count, *SwappedItemTwo->Item.GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item 2 No items returned"));
	}
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UInventory::FItemContainer* UInventory::SwapItem(FItemContainer* ItemContainer, int16 SlotIndex)
{
	// Prevent values outside of the inventory size
	SlotIndex = FMath::Clamp(SlotIndex, 0, InventorySlotCount);

	if (ItemStacks[SlotIndex] == nullptr)
	{
		ItemStacks[SlotIndex] = ItemContainer;
		return nullptr;
	}

	// TODO: Implement adding to stack when swapping with same items

	FItemContainer* ReturnContainer = ItemStacks[SlotIndex];
	ItemStacks[SlotIndex] = ItemContainer;
	return ReturnContainer;
}
