#include "MoveableCamera.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AMoveableCamera::AMoveableCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateCameraComponent();
}

void AMoveableCamera::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	SetCameraRotation();
}

void AMoveableCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveCamera(GetMoveDirection());
}

void AMoveableCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMoveableCamera::CreateCameraComponent()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
}

void AMoveableCamera::SetCameraRotation()
{
	FRotator BeginRotation;
	BeginRotation.Pitch = 315.0f;
	BeginRotation.Yaw = 270.0f;
	BeginRotation.Roll = 0.0f;
	
	SetActorRotation(BeginRotation);
}

FVector2d AMoveableCamera::GetMoveDirection()
{
	float LocationX;
	float LocationY;

	GetWorld()->GetFirstPlayerController()->GetMousePosition(LocationX, LocationY);
	
	FVector2d Viewport;
	GEngine->GameViewport->GetViewportSize(Viewport);

	FVector2d DirectionVector = FVector2d::Zero();

	if (LocationX <= EdgeOffset)
	{
		DirectionVector.X = -1.0f;
	}
	else if (LocationX >= Viewport.X - EdgeOffset)
	{
		DirectionVector.X = 1.0f;
	}

	if (LocationY <= EdgeOffset)
	{
		DirectionVector.Y = -1.0f;
		
	}
	else if (LocationY >= Viewport.Y - EdgeOffset)
	{
		DirectionVector.Y = 1.0f;
	}

	return DirectionVector;
}

void AMoveableCamera::MoveCamera(const FVector2d& DirectionVector)
{
	if (PlayerController == nullptr) return;
	if (!IsCursorOverGameViewport()) return;
	if (DirectionVector.IsZero()) return;
	
	FVector CameraLocation = GetActorLocation();

	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	CameraLocation += FVector(DirectionVector.X * MoveSpeed * DeltaTime, DirectionVector.Y * MoveSpeed * DeltaTime, 0.0f);

	SetActorLocation(CameraLocation);
}

bool AMoveableCamera::IsCursorOverGameViewport()
{
	if (PlayerController == nullptr) return false;
	
	UGameViewportClient* GameViewport = GEngine->GameViewport;

	if (GameViewport == nullptr) return false;
	
	if (GameViewport->Viewport)
	{
		FViewport* Viewport = GameViewport->Viewport;
		return Viewport->HasFocus() || Viewport->HasMouseCapture();
	}

	return false;
}
