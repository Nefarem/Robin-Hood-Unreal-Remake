#include "RobinHoodHUD.h"
#include "BaseCharacter.h"
#include "RobinHoodPlayerController.h"

TArray<ABaseCharacter*> ARobinHoodHUD::GetSelelectedCharacters()
{
	return SelectedCharacters;
}

bool ARobinHoodHUD::GetSelectionAreaOverMinSize()
{
	return bSelectionAreaOverMinSize;
}

void ARobinHoodHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawSelectionBox();
}

void ARobinHoodHUD::DrawSelectionBox()
{
	if (!bStartSelect) return;
	
	CurrentPoint = Cast<ARobinHoodPlayerController>(GetOwningPlayerController())->GetMousePos2D();

	FVector2d DiffLocation = FVector2d(CurrentPoint.X - InitialPoint.X,
										CurrentPoint.Y - InitialPoint.Y);

	bSelectionAreaOverMinSize = CalculateRectangleArea() >= SelectionBoxRectangleAreaMinSize;
	
	const FLinearColor GreenColor = FLinearColor::Green;
	constexpr float RectAlpha = 0.2f;
	
	DrawRect(FLinearColor(GreenColor.R, GreenColor.G, GreenColor.B, RectAlpha),
						  InitialPoint.X, InitialPoint.Y,
						  DiffLocation.X, DiffLocation.Y);

	if (!bSelectionAreaOverMinSize) return;

	SelectedCharacters.Empty();
	GetActorsInSelectionRectangle<ABaseCharacter>(InitialPoint, CurrentPoint, SelectedCharacters, false, false);
}

int ARobinHoodHUD::CalculateRectangleArea() const
{
	int Length = FMath::Abs(InitialPoint.X - CurrentPoint.X);
	int Width = FMath::Abs(InitialPoint.Y - CurrentPoint.Y);

	return Length * Width;
}
