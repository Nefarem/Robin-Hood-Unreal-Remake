#include "BaseCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseCharacter::ConfigureCharacterMovement()
{
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 640.f, 0.f);
	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->bSnapToPlaneAtStart = true;
}

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ConfigureCharacterMovement();
	CreateSpringCamera();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Move"), IE_Pressed, this, &ABaseCharacter::MoveToClickedPoint);
}

void ABaseCharacter::CreateSpringCamera()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ABaseCharacter::MoveToClickedPoint()
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController == nullptr) return;
	
	FHitResult HitResult;

	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		UE_LOG(LogTemp, Display, TEXT("Click location: %s"), *HitResult.Location.ToString());
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, HitResult.Location);
	}
}