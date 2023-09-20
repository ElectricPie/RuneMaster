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
	
	/**
	 * Gets the coordinates of the nearest node to the world position
	 * @param WorldPosition The world position to get a node
	 * @return A 2 length array with the X at 0 and Y at 1
	 */
	int* GetNodeFromWorldSpace(const FVector& WorldPosition) const;
	
	/**
	 * Gets the world space of a node at the given coordinates
	 * @param X The X coordinate of the node
	 * @param Y The Y coordinate of the node
	 * @return FVector of the nodes world space
	 */
	FVector GetNodeWorldPosition(const int X, const int Y) const;
	/**
	 * Gets the size of the nodes
	 * @return The node size
	 */
	float GetNodeSize() const;
	
	
private:
	float GridNodeSize = 100.f;
};
