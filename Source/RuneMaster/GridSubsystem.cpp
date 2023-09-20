// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSubsystem.h"

FVector UGridSubsystem::GetNodeFromWorldSpace(const FVector& WorldPosition) const
{
	const FVector RoundedWorldPosition = FVector(
		FMath::RoundHalfFromZero(WorldPosition.X / GridNodeSize),
		FMath::RoundHalfFromZero(WorldPosition.Y / GridNodeSize),
		FMath::CeilToFloat(0.f));

	DrawDebugSphere(GetWorld(), RoundedWorldPosition * GridNodeSize, GridNodeSize / 2, 12, FColor::Red, false, 2.f);
	
	return RoundedWorldPosition;
}
