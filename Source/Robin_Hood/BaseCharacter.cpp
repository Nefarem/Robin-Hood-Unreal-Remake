#include "BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("UFloatingPawnMovement"));

	SelectionSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SelectionSprite"));
	SelectionSpriteComponent->SetupAttachment(RootComponent);
	
	ToggleSelect(false);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigureCharacterMovement();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void ABaseCharacter::ConfigureCharacterMovement()
{
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 640.f, 0.f);
	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->bSnapToPlaneAtStart = true;
}

void ABaseCharacter::MoveToClickedPoint(FVector Location)
{
	TargetLocation = Location;
	CanMove = true;
}

void ABaseCharacter::Move()
{
	constexpr float DistanceThreshold = 93.0f;
	
	if (!CanMove) return;

	FVector ActorLocation = GetActorLocation();
	FVector DirectionVector = (TargetLocation - ActorLocation).GetSafeNormal();
	
	FloatingPawnMovementComponent->AddInputVector(DirectionVector);
	
	if (FVector::Dist(ActorLocation, TargetLocation) <= DistanceThreshold)
	{
		CanMove = false;
		FloatingPawnMovementComponent->StopMovementImmediately();
	}
}

void ABaseCharacter::ToggleSelect(bool Value)
{
	SelectionSpriteComponent->SetVisibility(Value);
}


