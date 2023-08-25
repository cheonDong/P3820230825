// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UMyActorComponent;

UCLASS()
class PROJECT0824_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 어딘가에 있는 BoxComponent를 사용하는 것이므로 메모리에 접근하여 사용.
	// 그래서 모두 포인터로 사용.
	
	// instanceonly = 레벨에 배치한 것만 가능
	// 컴포넌트들은 모두 VisibleAnywhere
	// VisibleAnywhere = BP의 디테일 탭에 표시됨. 값의 변경은 불가능
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Box;

	// BlueprintReadOnly = get으로 값을 가져오는것만 가능
	// BlueprintReadWrite = get, set 모두 가능
	// EditAnywhere = 컴포넌트 값을 BP에서 변경할 수 있음.
	// Category = "Component" 는 상속된 변수 표시 할때 생성한 변수들을 한 카테고리로 묶을때 사용.
	// ** 상속된 변수 표시하는 방법 = 해당 클래스의 BP에 들어가보면 내 블루프린트 탭의 톱니바퀴 모양 클릭. 
	// 이 후, 맨 위의 상속된 변수 생성을 클릭하면 C++에서 작업한 변수들을 모두 확인할 수 있다. **
	// Meta = C++ 에서 private, protected로 접근할 수 없는 변수나 함수를 블루프린트에서 접근할 수 있도록 함.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMyActorComponent* MyActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float PropellerSpeed = 3600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BoostValue = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Gold = 100;
	//int형은 컴파일러에 따라 사이즈가 다르므로 int형의 사이즈도 제대로 정해주어야 한다.

	void Pitch(float value);

	void Roll(float Value);

	void Fire();

	void Boost();

	void UnBoost();

	void EnhancedBoost(const FInputActionValue& Value);

	void EnhancedUnBoost(const FInputActionValue& Value);

	void EnhancedFire(const FInputActionValue& Value);

	void EnhancedPitchAndRoll(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Boost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_PitchAndRoll;
};
