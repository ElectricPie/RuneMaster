// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/GameHud.h"

#include "GameHudWidget.h"
#include "InventoryUi.h"
#include "RuneMaster/Inventory.h"

void AGameHud::BeginPlay()
{
	Super::BeginPlay();

	// Setup player widgets
	if (HudWidgetClass != nullptr)
	{
		HudWidgetInstance = CreateWidget<UGameHudWidget>(GetOwningPlayerController(), HudWidgetClass);
		HudWidgetInstance->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Hud is missing HudWidgetClass"));
		return;
	}

	if (const UInventory* PlayerInventory = GetOwningPawn()->GetComponentByClass<UInventory>())
	{
		HudWidgetInstance->SetupInventoryGrid(PlayerInventory);
	}
}
