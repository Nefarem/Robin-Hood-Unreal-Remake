#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/HUD.h"
#include "RobinHoodHUD.generated.h"

UCLASS()
class ROBIN_HOOD_API ARobinHoodHUD : public AHUD
{
	GENERATED_BODY()

public:
	FVector2d InitialPoint;
	FVector2d CurrentPoint;
	
	bool bStartSelect;

	TArray<ABaseCharacter*> GetSelelectedCharacters();

	bool GetSelectionAreaOverMinSize();
	
	virtual void DrawHUD() override;
	
	void DrawSelectionBox();

private:
	TArray<ABaseCharacter*> SelectedCharacters;

	bool bSelectionAreaOverMinSize;
	
	const int SelectionBoxRectangleAreaMinSize = 50;
	
	int CalculateRectangleArea() const;
};
