// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GridSubsystem.h"

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	Grid = GetWorld()->GetSubsystem<UGridSubsystem>();
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::Select);
	}
}

bool ATopDownPlayerController::RaycastToMouse(FVector& HitLocation, AActor*& HitActor)
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	// Get the screen position of the mouse
	if (FVector2D MouseScreenLocation; GetMousePosition(MouseScreenLocation.X, MouseScreenLocation.Y))
	{
		// Get the direction of the mouse
		FVector WorldPosition;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseScreenLocation.X, MouseScreenLocation.Y, WorldPosition, WorldDirection);
	
		// Raycast
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
	
		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition,
			WorldPosition + WorldDirection * SelectionRaycastDistance, ECC_Visibility, QueryParams))
		{
			HitActor = HitResult.GetActor();
			HitLocation = HitResult.ImpactPoint;
			return true;
		}
	}

	return false;
}

void ATopDownPlayerController::Select()
{
	FVector HitLocation;
	AActor* HitActor = nullptr;
	if (RaycastToMouse(HitLocation, HitActor))
	{
		FVector GridPos = Grid->GetNodeFromWorldSpace(HitLocation);

		
	}
}
