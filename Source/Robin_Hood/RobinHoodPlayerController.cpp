#include "RobinHoodPlayerController.h"
#include "BaseCharacter.h"

ARobinHoodPlayerController::ARobinHoodPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

FVector2d ARobinHoodPlayerController::GetMousePos2D()
{
	float LocationX, LocationY;
	
	GetMousePosition(LocationX, LocationY);

	return FVector2d(LocationX, LocationY);
}

void ARobinHoodPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ARobinHoodHUD>(GetHUD());
}

void ARobinHoodPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobinHoodPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(TEXT("LeftMouseClick"), IE_Pressed, this, &ARobinHoodPlayerController::SelectionPressed);
	InputComponent->BindAction(TEXT("LeftMouseClick"), IE_Released, this, &ARobinHoodPlayerController::SelectionReleased);
	InputComponent->BindAction(TEXT("LeftMouseClick"), IE_Released, this, &ARobinHoodPlayerController::MoveSelectedPawnsToClickedPoint);
}

void ARobinHoodPlayerController::SelectionPressed()
{
	HUD->InitialPoint = GetMousePos2D();
	HUD->bStartSelect = true;
}

void ARobinHoodPlayerController::SelectionReleased()
{
	HUD->bStartSelect = false;
	
	ShowSelectionIndicators();
}

void ARobinHoodPlayerController::ShowSelectionIndicators()
{
	if (!HUD->GetSelectionAreaOverMinSize()) return;
	
	if (PreviousSelectedCharacters.Num() > 0)
	{
		for (ABaseCharacter* SelectedCharacter : PreviousSelectedCharacters)
		{
			SelectedCharacter->ToggleSelect(false);
		}

		PreviousSelectedCharacters.Empty();
	}
	
	TArray<ABaseCharacter*> SelectedCharacters = HUD->GetSelelectedCharacters();
	PreviousSelectedCharacters = SelectedCharacters;
	
	for (ABaseCharacter* SelectedCharacter : SelectedCharacters)
	{
		SelectedCharacter->ToggleSelect(true);
	}
}

void ARobinHoodPlayerController::MoveSelectedPawnsToClickedPoint()
{
	if (HUD->GetSelectionAreaOverMinSize()) return;
	
	FHitResult HitResult;
	bool bIsHit = GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!bIsHit) return;
	
	TArray<ABaseCharacter*> SelectedCharacters = HUD->GetSelelectedCharacters();
	
	for (ABaseCharacter* SelectedCharacter : SelectedCharacters)
	{
		SelectedCharacter->MoveToClickedPoint(HitResult.Location);
	}
}
