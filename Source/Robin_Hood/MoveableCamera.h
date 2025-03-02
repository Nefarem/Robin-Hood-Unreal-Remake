#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MoveableCamera.generated.h"

UCLASS()
class ROBIN_HOOD_API AMoveableCamera : public APawn
{
	GENERATED_BODY()

public:
	AMoveableCamera();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Camera")
	float EdgeOffset = 30.0f;

	UPROPERTY(EditAnywhere, Category="Camera")
	float MoveSpeed = 600.0f;

	
	FVector2d GetMoveDirection();

	bool IsCursorOverGameViewport();
	
	void CreateCameraComponent();
	void SetCameraRotation();
	void MoveCamera(const FVector2d& DirectionVector);

	class APlayerController* PlayerController;
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	class UCameraComponent* CameraComponent;
};
