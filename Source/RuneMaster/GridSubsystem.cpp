// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSubsystem.h"

int* UGridSubsystem::GetNodeFromWorldSpace(const FVector& WorldPosition) const
{
	const int GridX = WorldPosition.X == 0 ? 0 : FMath::RoundHalfFromZero(WorldPosition.X / GridNodeSize);
	const int GridY = WorldPosition.Y == 0 ? 0 : FMath::RoundHalfFromZero(WorldPosition.Y / GridNodeSize);
	
	int* GridPosition = new int[2] {GridX, GridY};
	
	return GridPosition;
}

FVector UGridSubsystem::GetNodeWorldPosition(const int X, const int Y) const
{
	const FVector NodeWorldPosition(X * GridNodeSize, Y * GridNodeSize, 0.f);
	return NodeWorldPosition;
}

float UGridSubsystem::GetNodeSize() const
{
	return GridNodeSize;
}
