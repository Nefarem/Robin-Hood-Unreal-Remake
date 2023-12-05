#include "RobinHoodPlayerController.h"

#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

ARobinHoodPlayerController::ARobinHoodPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARobinHoodPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobinHoodPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Move"), IE_Pressed, this, &ARobinHoodPlayerController::SendPawnsToClickedPoint);
}

// Todo: Temporary implementation, in future player will select specific characters and move to (X,Y,Z) position.
void ARobinHoodPlayerController::SendPawnsToClickedPoint()
{
	FHitResult HitResult;
	bool bIsHit = GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!bIsHit) return;

	TArray<AActor*> BaseCharacters;
	UClass* BaseCharacterClass = ABaseCharacter::StaticClass();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BaseCharacterClass, BaseCharacters);

	for (AActor* baseCharacter : BaseCharacters)
	{
		ABaseCharacter* tmpBaseCharacter = Cast<ABaseCharacter>(baseCharacter);

		if (tmpBaseCharacter == nullptr) continue;

		tmpBaseCharacter->MoveToClickedPoint(HitResult.Location);
	}
}
