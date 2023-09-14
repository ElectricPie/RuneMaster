// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class UGridSubsystem;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class RUNEMASTER_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectInputAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float SelectionRaycastDistance = 2000.f;

	UPROPERTY()
	UGridSubsystem* Grid;

	bool RaycastToMouse(FVector& HitLocation, AActor*& HitActor);
	void Select();
};
