// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "ItemContainer.h"
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
	// Setup the inventory
	ItemStacks = TArray<TSharedPtr<FItemContainer>>();
	for (int32 i = 0; i < InventorySlotCount; i++)
	{
		ItemStacks.Add(nullptr);
	}

	// TODO: Remove once UI is implemented
	if (!DebugItemDAOne || !DebugItemDATwo) return;

	TSharedPtr<FItemContainer> DebugItemOne = MakeShareable<FItemContainer>(new FItemContainer {*DebugItemDAOne, 97});
	TSharedPtr<FItemContainer> DebugItemTwo = MakeShareable<FItemContainer>(new FItemContainer {*DebugItemDATwo, 20});

	const TSharedPtr<const FItemContainer> DebugPeekZero = PeekItem(1);
	if (DebugPeekZero.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 0: %i of %s"), DebugPeekZero.Get()->Count, *DebugPeekZero.Get()->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 0: Empty"));
	}
	
	TSharedPtr<FItemContainer> SwappedItemOne = SwapItem(DebugItemOne, 1);
	if (SwappedItemOne.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Returned %i of %s"), SwappedItemOne->Count, *SwappedItemOne->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Item 1 No items returned"));
	}
	TSharedPtr<const FItemContainer> DebugPeekOne = PeekItem(1);
	if (DebugPeekOne.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 1: %i of %s"), DebugPeekOne.Get()->Count, *DebugPeekOne.Get()->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 1: Empty"));
	}
	
	TSharedPtr<FItemContainer> SwappedItemTwo = SwapItem(nullptr, 1);
	if (SwappedItemTwo.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Returned %i of %s"), SwappedItemTwo->Count, *SwappedItemTwo->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Item 2 No items returned"));
	}
	TSharedPtr<const FItemContainer> DebugPeekTwo = PeekItem(1);
	if (DebugPeekTwo.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 2: %i of %s"), DebugPeekTwo.Get()->Count, *DebugPeekTwo.Get()->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 2: Empty"));
	}
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSharedPtr<FItemContainer> UInventory::SwapItem(TSharedPtr<FItemContainer> ItemContainer, uint16 SlotIndex)
{
	// Prevent values outside of the inventory size
	SlotIndex = FMath::Clamp(SlotIndex, 0, InventorySlotCount);

	TSharedPtr<FItemContainer> ItemInSlot = ItemStacks[SlotIndex];

	if (ItemInSlot.IsValid() && ItemContainer.IsValid())
	{
		// Combine item stacks if of the same types
		if (*ItemInSlot.Get() == *ItemContainer.Get())
		{
			// Prevent underflow
			uint16 StackFreeSpace = 0;
			if (ItemInSlot->Count < ItemInSlot->GetItemMaxStackSize())
			{
				StackFreeSpace = ItemInSlot->GetItemMaxStackSize() - ItemInSlot->Count;
			}
		
			// Send back the items if the slot is full
			if (StackFreeSpace <= 0)
			{
				return ItemContainer;
			}
		
			// Add only what will fit to the stack and return the rest
			if (StackFreeSpace < ItemContainer->Count)
			{
				const uint16 Overfill = ItemContainer->Count - StackFreeSpace;
				ItemStacks[SlotIndex]->Count = ItemInSlot->GetItemMaxStackSize();

				return MakeShareable<FItemContainer>(new FItemContainer{ItemInSlot->GetItem(), Overfill});
			}
		
			// Added all items to stack
			ItemInSlot->Count += ItemContainer->Count;
			return nullptr;
		}
	}

	// Swap the items
	ItemStacks[SlotIndex] = ItemContainer;
	return ItemInSlot;
}

TSharedPtr<const FItemContainer> UInventory::PeekItem(const uint16 SlotIndex)
{
	return ItemStacks[SlotIndex];
}
