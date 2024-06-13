// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UItemDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNEMASTER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetSlotCount() const { return InventorySlotCount; }

	
	/**
	 * @brief Adds the item to the inventory if there is space
	 * @param DataAsset The type of item to add
	 * @param AmountToAdd How many of the item to add
	 * @return Any items that will not fit in the inventory
	 */
	UFUNCTION(BlueprintCallable)
	int32 AddItem(UItemDataAsset* DataAsset, int32 AmountToAdd);
	
	// 	/**
	// 	 * Swaps the ItemContainer with the items in the slot.
	// 	 * @param ItemContainer The item to be swapped, can be nullptr.
	// 	 * @param SlotIndex The slot in the inventory to be swapped with.
	// 	 * @return Returns item at the slot, can be a nullptr. If the same item is in the slot already then it increases the
	// 	 * inventories item count and return an ItemContainer with a count that would not fit in the inventories container.
	// 	 */
	// 	TSharedPtr<FItemContainerOld> SwapItem(TSharedPtr<FItemContainerOld> ItemContainer, uint16 SlotIndex);
	// 	
	// 	/**
	// 	 * Gets the item in the requested slot
	// 	 * @param SlotIndex The index of the slot to peek
	// 	 * @return The item container at the slot, can be nullptr
	// 	 */
	// 	TSharedPtr<const FItemContainerOld> PeekItem(uint16 SlotIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, meta=(ClampMin=1, UIMin=1))
	int32 InventorySlotCount = 20;
	int32 UsedSlots = 0;
	
	UPROPERTY(EditAnywhere)
	UItemDataAsset* DebugItemDAOne;
	UPROPERTY(EditAnywhere)
	UItemDataAsset* DebugItemDATwo;

	UPROPERTY(VisibleAnywhere)
	TMap<UItemDataAsset*, uint32> Items;
};
