// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUi.generated.h"

class UInventory;
class USizeBox;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class UInventoryUi : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetupInventory(UInventory* InventoryComponent, const FVector2D GridCanvasSize);
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	USizeBox* GridSizeBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UUniformGridPanel* InventoryGridPanel;

private:
	UPROPERTY(EditAnywhere, Category="Inventory Grid")
	TSubclassOf<UUserWidget> InventorySlotWidget;
	UPROPERTY(EditAnywhere, Category="Grid Slots")
	int32 MaxColumns = 9;
	int32 Rows = 0;

	TWeakObjectPtr<UInventory> Inventory;
};
