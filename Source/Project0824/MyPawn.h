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

	// ��򰡿� �ִ� BoxComponent�� ����ϴ� ���̹Ƿ� �޸𸮿� �����Ͽ� ���.
	// �׷��� ��� �����ͷ� ���.
	
	// instanceonly = ������ ��ġ�� �͸� ����
	// ������Ʈ���� ��� VisibleAnywhere
	// VisibleAnywhere = BP�� ������ �ǿ� ǥ�õ�. ���� ������ �Ұ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Box;

	// BlueprintReadOnly = get���� ���� �������°͸� ����
	// BlueprintReadWrite = get, set ��� ����
	// EditAnywhere = ������Ʈ ���� BP���� ������ �� ����.
	// Category = "Component" �� ��ӵ� ���� ǥ�� �Ҷ� ������ �������� �� ī�װ��� ������ ���.
	// ** ��ӵ� ���� ǥ���ϴ� ��� = �ش� Ŭ������ BP�� ������ �� �������Ʈ ���� ��Ϲ��� ��� Ŭ��. 
	// �� ��, �� ���� ��ӵ� ���� ������ Ŭ���ϸ� C++���� �۾��� �������� ��� Ȯ���� �� �ִ�. **
	// Meta = C++ ���� private, protected�� ������ �� ���� ������ �Լ��� �������Ʈ���� ������ �� �ֵ��� ��.

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
	//int���� �����Ϸ��� ���� ����� �ٸ��Ƿ� int���� ����� ����� �����־�� �Ѵ�.

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
