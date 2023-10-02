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
		UItemDataAsset& Item;
		int16 Count;
	};

	UPROPERTY(EditAnywhere)
	uint16 InventorySlotCount = 20;
	
	UPROPERTY(EditAnywhere)
	UItemDataAsset* DebugItem;
	
	TArray<FItemContainer> ItemStacks;

public:
	/**
	 * Attempts to add the item to the inventory
	 * @param ItemContainer 
	 * @return 
	 */
	bool AddItem(FItemContainer& ItemContainer);
};
