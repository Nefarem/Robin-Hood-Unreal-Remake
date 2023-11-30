#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RobinHoodPlayerController.generated.h"

UCLASS()
class ROBIN_HOOD_API ARobinHoodPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARobinHoodPlayerController();

protected:
	virtual void SetupInputComponent() override;
};