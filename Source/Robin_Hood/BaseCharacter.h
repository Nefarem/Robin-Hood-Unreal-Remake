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
	void MoveToClickedPoint();
	void CreateSpringCamera();
	void ConfigureCharacterMovement();

	// Todo: Temporary implementation, in future camera will no spring to player character, but player can move camera on whole map
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
