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
		100 // Count
	};

	FItemContainer DebugItemTwo = {
		*DebugItemDAOne, // Item
		52 // Count
	};

	FItemContainer* SwappedItemOne = SwapItem(&DebugItemOne, 1);
	if (SwappedItemOne)
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Returned %i of %s"), SwappedItemOne->Count, *SwappedItemOne->Item.GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Item 1 No items returned"));
	}
	
	FItemContainer* SwappedItemTwo = SwapItem(&DebugItemTwo, 1);
	if (SwappedItemTwo)
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Returned %i of %s"), SwappedItemTwo->Count, *SwappedItemTwo->Item.GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Item 2 No items returned"));
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
	FItemContainer* ReturnContainer = nullptr;
	
	// Prevent values outside of the inventory size
	SlotIndex = FMath::Clamp(SlotIndex, 0, InventorySlotCount);

	FItemContainer* ItemInSlot = ItemStacks[SlotIndex];
	
	// Empty slot or emp
	if (!ItemInSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty"));
		ItemStacks[SlotIndex] = ItemContainer;
		return nullptr;
	}

	// TODO: Implement replacing with nothing
	// Temp solution for replacing slot with nothing
	if (!ItemInSlot)
	{
		return nullptr;
	}

	// Combine item stacks if of the same types
	if (*ItemInSlot == *ItemContainer)
	{
		// TODO: Prevent any possible underflow's
		const uint16 StackFreeSpace = ItemInSlot->Item.GetStackSize() - ItemInSlot->Count;
		
		// Send back the items if the slot is full
		if (StackFreeSpace <= 0)
		{
			return ItemContainer;
		}
		
		// Add only what will fit to the stack and return the rest
		if (StackFreeSpace < ItemContainer->Count)
		{
			const uint16 Overfill = ItemContainer->Count - StackFreeSpace;
			ItemStacks[SlotIndex]->Count = ItemInSlot->Item.GetStackSize();
			ReturnContainer = new FItemContainer {
				ItemInSlot->Item, // Item
				Overfill // Count
			};
			return ReturnContainer;
		}
		
		// Added all items to stack
		ItemInSlot->Count += ItemContainer->Count;
		return nullptr;
	}

	// Swap the items
	ReturnContainer = ItemStacks[SlotIndex];
	ItemStacks[SlotIndex] = ItemContainer;
	return ReturnContainer;
}
