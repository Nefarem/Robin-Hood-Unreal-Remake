#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ROBIN_HOOD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;
	
	float Health = 100.0f;
	float Stamina = 100.0f;

private:
	void ConfigureCharacterMovement();
	void Move();
	
	class UFloatingPawnMovement* FloatingPawnMovementComponent;

	FVector TargetLocation;
	bool CanMove;
	
public:
	virtual void Tick(float DeltaTime) override;

	void MoveToClickedPoint(FVector Location);
};
