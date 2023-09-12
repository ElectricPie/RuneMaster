// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set the meshes direction based on the direction the character is moving
	// May want to set this Directions * their respective values as this method
	//  doesn't turn face the keys direction when hitting an object
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		// Only update the rotation when moving
		const FVector Velocity = GetVelocity();
		if (Velocity.Length() > 10.f)
		{
			// Need to keep track of the direction as it get reset without setting the rotation every frame
			LookDirection = Velocity.Rotation();
			LookDirection.Yaw += RotationOffset;
		}
		MeshComponent->SetRelativeRotation(LookDirection);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		PlayerEnhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Zoom);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	const FVector2d DirectionValue = Value.Get<FVector2d>();

	// Find forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get the directions of the character
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Apply forward and right movement
	AddMovementInput(ForwardDirection, DirectionValue.X);
	AddMovementInput(RightDirection, DirectionValue.Y);
}

void APlayerCharacter::Zoom(const FInputActionValue& Value)
{
	if (!SpringArm) return;
	
	const float ScrollDirection = Value.Get<float>();
	const float ScrollSpeed = FApp::GetDeltaTime() * ZoomSpeedModifier * ScrollDirection;

	// Limit the springs arm length to the Min/Max
	float NewArmLength = SpringArm->TargetArmLength += ScrollSpeed;
	if (NewArmLength > MaxZoom)
	{
		NewArmLength = MaxZoom;
	}
	if (NewArmLength < MinZoom)
	{
		NewArmLength = MinZoom;
	}

	SpringArm->TargetArmLength = NewArmLength;
}

