#pragma once

#include "CoreMinimal.h"
#include "RobinHoodHUD.h"
#include "GameFramework/PlayerController.h"
#include "RobinHoodPlayerController.generated.h"

UCLASS()
class ROBIN_HOOD_API ARobinHoodPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARobinHoodPlayerController();
	FVector2d GetMousePos2D();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	ARobinHoodHUD* HUD;

	TArray<ABaseCharacter*> PreviousSelectedCharacters;
	
	void SelectionPressed();
	void SelectionReleased();
	void ShowSelectionIndicators();
	void MoveSelectedPawnsToClickedPoint();
};
