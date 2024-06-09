// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHudWidget.generated.h"

class UInventory;
class UPlayerInventoryUi;
/**
 * 
 */
UCLASS()
class UGameHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerInventoryUi* GetInventoryUi() const { return PlayerInventoryUi; }
	
private:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UPlayerInventoryUi* PlayerInventoryUi;
};
