#include "RobinHoodPlayerController.h"

ARobinHoodPlayerController::ARobinHoodPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARobinHoodPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
}