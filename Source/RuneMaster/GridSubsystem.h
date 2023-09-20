// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GridSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class RUNEMASTER_API UGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FVector GetNodeFromWorldSpace(const FVector& WorldPosition) const;
	
private:
	float GridNodeSize = 100.f;
};
