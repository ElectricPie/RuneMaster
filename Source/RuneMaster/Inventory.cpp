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

// TSharedPtr<FItemContainerOld> UInventory::SwapItem(TSharedPtr<FItemContainerOld> ItemContainer, uint16 SlotIndex)
// {
// 	// Prevent values outside of the inventory size
// 	SlotIndex = FMath::Clamp(SlotIndex, 0, InventorySlotCount);
//
// 	TSharedPtr<FItemContainerOld> ItemInSlot = ItemStacks[SlotIndex];
//
// 	if (ItemInSlot.IsValid() && ItemContainer.IsValid())
// 	{
// 		// Combine item stacks if of the same types
// 		if (*ItemInSlot.Get() == *ItemContainer.Get())
// 		{
// 			// Prevent underflow
// 			uint16 StackFreeSpace = 0;
// 			if (ItemInSlot->Count < ItemInSlot->GetItemMaxStackSize())
// 			{
// 				StackFreeSpace = ItemInSlot->GetItemMaxStackSize() - ItemInSlot->Count;
// 			}
// 		
// 			// Send back the items if the slot is full
// 			if (StackFreeSpace <= 0)
// 			{
// 				return ItemContainer;
// 			}
// 		
// 			// Add only what will fit to the stack and return the rest
// 			if (StackFreeSpace < ItemContainer->Count)
// 			{
// 				const uint16 Overfill = ItemContainer->Count - StackFreeSpace;
// 				ItemStacks[SlotIndex]->Count = ItemInSlot->GetItemMaxStackSize();
//
// 				return MakeShareable<FItemContainerOld>(new FItemContainerOld{ItemInSlot->GetItem(), Overfill});
// 			}
// 		
// 			// Added all items to stack
// 			ItemInSlot->Count += ItemContainer->Count;
// 			return nullptr;
// 		}
// 	}
//
// 	// Swap the items
// 	ItemStacks[SlotIndex] = ItemContainer;
// 	return ItemInSlot;
// }
//
// TSharedPtr<const FItemContainerOld> UInventory::PeekItem(const uint16 SlotIndex)
// {
// 	return ItemStacks[SlotIndex];
// }


int32 UInventory::AddItem(UItemDataAsset* DataAsset, int32 AmountToAdd)
{
	const int32 ItemStackSize = DataAsset->GetStackSize();
	if (Items.Contains(DataAsset))
	{
		const int32 RemainingSpaceInCurrentStack = ItemStackSize - (Items[DataAsset] % ItemStackSize);
		// Fill the stack with as much as possible
		if (AmountToAdd < RemainingSpaceInCurrentStack)
		{
			Items[DataAsset] += AmountToAdd;
			return 0;
		}

		// Fill the current stack
		Items[DataAsset] += RemainingSpaceInCurrentStack;
		AmountToAdd -= RemainingSpaceInCurrentStack;
	}
	else
	{
		// New Item type added
		if (UsedSlots >= InventorySlotCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("No slot left in inventory"));
			return AmountToAdd;
		}

		Items.Add(DataAsset, 0);
		// Only one stack needed
		if (AmountToAdd < ItemStackSize)
		{
			Items[DataAsset] = AmountToAdd;
			UsedSlots++;
			return 0;
		}
	}
		
	// No more space for additional stacks
	if (UsedSlots >= InventorySlotCount)
	{
		return AmountToAdd;
	}

	// Add as many stacks of the item as possible
	const int32 RemainingSlotsNeeded = AmountToAdd / ItemStackSize + 1;
	const int32 AvailableSlots = InventorySlotCount - UsedSlots;
	// No leftovers if enough slots available
	if (RemainingSlotsNeeded <= AvailableSlots)
	{
		Items[DataAsset] += AmountToAdd;
		UsedSlots += RemainingSlotsNeeded;
		return 0;
	}

	// Add as may stack till inventory is full
	const int32 CanBeAddedAmount = ItemStackSize * AvailableSlots;
	Items[DataAsset] += CanBeAddedAmount;
	UsedSlots += AvailableSlots;

	return AmountToAdd - CanBeAddedAmount;
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Remove once UI is implemented
	if (!DebugItemDAOne || !DebugItemDATwo) return;

	int32 LeftOvers = 0;
	LeftOvers = AddItem(DebugItemDAOne, 99);
	UE_LOG(LogTemp, Warning, TEXT("1 LeftOvers: %d"), LeftOvers);
	LeftOvers = AddItem(DebugItemDATwo, 500);
	UE_LOG(LogTemp, Warning, TEXT("2 LeftOvers: %d"), LeftOvers);
	LeftOvers = AddItem(DebugItemDAOne, 2000);
	UE_LOG(LogTemp, Warning, TEXT("1 LeftOvers: %d"), LeftOvers);

	// const TSharedPtr<const FItemContainer> DebugPeekZero = PeekItem(1);
	// if (DebugPeekZero.IsValid())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 0: %i of %s"), DebugPeekZero.Get()->Count, *DebugPeekZero.Get()->GetItemName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 0: Empty"));
	// }
	//
	// TSharedPtr<FItemContainer> SwappedItemOne = SwapItem(DebugItemOne, 1);
	// if (SwappedItemOne.IsValid())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("1: Returned %i of %s"), SwappedItemOne->Count, *SwappedItemOne->GetItemName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("1: Item 1 No items returned"));
	// }
	// TSharedPtr<const FItemContainer> DebugPeekOne = PeekItem(1);
	// if (DebugPeekOne.IsValid())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 1: %i of %s"), DebugPeekOne.Get()->Count, *DebugPeekOne.Get()->GetItemName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 1: Empty"));
	// }
	//
	// TSharedPtr<FItemContainer> SwappedItemTwo = SwapItem(nullptr, 1);
	// if (SwappedItemTwo.IsValid())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("2: Returned %i of %s"), SwappedItemTwo->Count, *SwappedItemTwo->GetItemName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("2: Item 2 No items returned"));
	// }
	// TSharedPtr<const FItemContainer> DebugPeekTwo = PeekItem(1);
	// if (DebugPeekTwo.IsValid())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 2: %i of %s"), DebugPeekTwo.Get()->Count, *DebugPeekTwo.Get()->GetItemName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Peak 2: Empty"));
	// }
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
