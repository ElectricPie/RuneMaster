// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Will probably need to move this to its own class
	struct FItemContainer
	{
		UItemDataAsset* Item = nullptr;
		uint16 Count = 0;

		FItemContainer(UItemDataAsset* ItemDataAsset, uint16 ItemCount)
		{
			Item = ItemDataAsset;
			Count = ItemCount;
		}

		bool operator==(const FItemContainer& Other) const
		{
			if (!Item || !Other.Item) return false;
			
			return Other.Item->GetName() == this->Item->GetName();
		}
	};

	UPROPERTY(EditAnywhere)
	uint16 InventorySlotCount = 20;
	
	UPROPERTY(EditAnywhere)
	UItemDataAsset* DebugItemDAOne;
	UPROPERTY(EditAnywhere)
	UItemDataAsset* DebugItemDATwo;
	
	TArray<TSharedRef<FItemContainer>> ItemStacks;

public:
	/**
	 * Swaps the ItemContainer with the items in the slot.
	 * @param ItemContainer The item to be swapped.
	 * @param SlotIndex The slot in the inventory to be swapped with.
	 * @return Returns item at the slot, can be a nullptr. If the same item is in the slot already then it increases the
	 * inventories item count and return an ItemContainer with a count that would not fit in the inventories container.
	 */
	TSharedRef<FItemContainer> SwapItem(TSharedRef<FItemContainer> ItemContainer, int16 SlotIndex);
};
