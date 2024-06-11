// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHud.generated.h"

class UGameHudWidget;

/**
 * 
 */
UCLASS(Abstract)
class AGameHud : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UGameHudWidget> HudWidgetClass;
	
	UPROPERTY()
	UGameHudWidget* HudWidgetInstance;
};