#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UPaperSprite;
class ASelectionBox;
class UFloatingPawnMovement;
class UPaperSpriteComponent;

UCLASS()
class ROBIN_HOOD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	void ToggleSelect(bool Value);

protected:
	virtual void BeginPlay() override;
	
	float Health = 100.0f;
	float Stamina = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ASelectionBox> SelectionBoxClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperSprite* SelectionSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* SelectionSpriteComponent;
	
private:
	void ConfigureCharacterMovement();
	void Move();

	UFloatingPawnMovement* FloatingPawnMovementComponent;
	
	FVector TargetLocation;
	bool CanMove;
	
public:
	virtual void Tick(float DeltaTime) override;

	void MoveToClickedPoint(FVector Location);
};
