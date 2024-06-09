  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryUi.generated.h"

class UPlayerInventorySlot;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class UPlayerInventoryUi : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void FillGrid(const int32 GridWidth);
	
private:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UUniformGridPanel* InventoryGridPanel;
	UPROPERTY(EditAnywhere, Category="Grid Slots")
	TSubclassOf<UUserWidget> InventorySlotWidget;
	UPROPERTY(EditAnywhere, Category="Grid Slots")
	int32 SlotColumns = 9;
};
