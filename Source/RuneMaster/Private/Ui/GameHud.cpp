// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/GameHud.h"

#include "GameHudWidget.h"

void AGameHud::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetClass != nullptr)
	{
		HudWidgetInstance = CreateWidget<UGameHudWidget>(GetOwningPlayerController(), HudWidgetClass);
		HudWidgetInstance->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Hud is missing HudWidgetClass"));
	}
}
