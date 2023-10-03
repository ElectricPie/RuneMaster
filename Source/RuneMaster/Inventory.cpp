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
	ItemStacks = TArray<TSharedRef<FItemContainer>>();
	for (int32 i = 0; i < InventorySlotCount; i++)
	{
		TSharedRef<FItemContainer> NewItemContainer = MakeShared<FItemContainer>(nullptr, 0);
		ItemStacks.Add(NewItemContainer);
	}
	
	if (!DebugItemDAOne || !DebugItemDATwo) return;

	TSharedRef<FItemContainer> DebugItemOne = MakeShared<FItemContainer>(DebugItemDAOne, 97);
	TSharedRef<FItemContainer> DebugItemTwo = MakeShared<FItemContainer>(DebugItemDAOne, 20);
	TSharedRef<FItemContainer> DebugEmptyOne = MakeShared<FItemContainer>(nullptr, 0);
	TSharedRef<FItemContainer> DebugEmptyTwo = MakeShared<FItemContainer>(nullptr, 0);
	
	const TWeakPtr<const FItemContainer> DebugPeekZero = PeakItem(1);
	if (DebugPeekZero.Pin()->Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 0: %i of %s"), DebugPeekZero.Pin()->Count, *DebugPeekZero.Pin()->Item->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Peak 0: Empty"));
	}
	
	TSharedRef<FItemContainer> SwappedItemOne = SwapItem(DebugItemOne, 1);
	if (SwappedItemOne->Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Returned %i of %s"), SwappedItemOne->Count, *SwappedItemOne->Item->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("1: Item 1 No items returned"));
	}
	TWeakPtr<const FItemContainer> DebugPeekOne = PeakItem(1);
	UE_LOG(LogTemp, Warning, TEXT("Peak 1: %i of %s"), DebugPeekOne.Pin()->Count, *DebugPeekOne.Pin()->Item->GetItemName());
	
	TSharedRef<FItemContainer> SwappedItemTwo = SwapItem(DebugItemTwo, 1);
	if (SwappedItemTwo->Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Returned %i of %s"), SwappedItemTwo->Count, *SwappedItemTwo->Item->GetItemName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("2: Item 2 No items returned"));
	}
	TWeakPtr<const FItemContainer> DebugPeekTwo = PeakItem(1);
	UE_LOG(LogTemp, Warning, TEXT("Peak 2: %i of %s"), DebugPeekTwo.Pin()->Count, *DebugPeekTwo.Pin()->Item->GetItemName());
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSharedRef<FItemContainer> UInventory::SwapItem(TSharedRef<FItemContainer> ItemContainer, int16 SlotIndex)
{
	// Prevent values outside of the inventory size
	SlotIndex = FMath::Clamp(SlotIndex, 0, InventorySlotCount);

	TSharedRef<FItemContainer> ItemInSlot = ItemStacks[SlotIndex];
	
	// Combine item stacks if of the same types
	if (ItemInSlot.Get() == ItemContainer.Get())
	{
		// Prevent underflow
		uint16 StackFreeSpace = 0;
		if (ItemInSlot->Count < ItemInSlot->Item->GetStackSize())
		{
			StackFreeSpace = ItemInSlot->Item->GetStackSize() - ItemInSlot->Count;
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
			ItemStacks[SlotIndex]->Count = ItemInSlot->Item->GetStackSize();
			
			return MakeShared<FItemContainer>(ItemInSlot->Item, Overfill);
		}
		
		// Added all items to stack
		ItemInSlot->Count += ItemContainer->Count;
		return MakeShared<FItemContainer>(nullptr, 0);
	}

	// Swap the items
	ItemStacks[SlotIndex] = ItemContainer;
	return ItemInSlot;
}

TWeakPtr<const FItemContainer> UInventory::PeakItem(const int16 SlotIndex)
{
	return ItemStacks[SlotIndex];
}
