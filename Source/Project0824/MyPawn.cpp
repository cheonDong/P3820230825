// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyActorComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values 원본 메모리에 세팅
// CDO 생성.
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 틱이 아무것도 실행하지 않는데 켜져있다면 성능저하가 올 수 있으므로 아래의 함수로 틱을 꺼둘 수 있다.(배경)
	// 블루프린트에서도 셀프 세팅에서 On/Off가 가능하다.
	PrimaryActorTick.bCanEverTick = true;

	// 메모리에 박스 컴포넌트 생성. 
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 20, 20));
	// 부모의 값을 바꾸는 것이므로 변경 전에 생성된 자식의 값을 변하지 않는다. 에디터 재실행.

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	// Load Mesh = 실행중이 아니라 시작하자마자 CDO에 Mesh를 불러옴
	// Fclass = BP class , FObject = 에셋
	// 변수명 앞은 struture형의 자료형, 변수명 뒤는 생성자 인자.
	// 생성할때마다 loading하면 안되므로 앞에 static을 붙여 한번만 실행한다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.0f, -21.0f, 1.0f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.0f, 21.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Body.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	// 액터 컴포넌트는 트리구조로 만들지 않는다.(attach할 필요가 없다.)
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("aaaa"));
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedBoost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::EnhancedUnBoost);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedFire);
		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedPitchAndRoll);
	}
	else
	{
		// 예전 입력 방식. 이제는 언리얼 에디터의 에셋을 사용하여 입력 방식 생성
		/*PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
		PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

		PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
		PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &AMyPawn::Boost);
		PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &AMyPawn::UnBoost);*/
	}

}

void AMyPawn::Pitch(float value)
{
	AddActorLocalRotation(FRotator(value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f,
		0,
		0));
}

void AMyPawn::Roll(float value)
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalRotation(FRotator(0, 0, value * DeltaSeconds * 60.0f));
}

void AMyPawn::Fire()
{
	// GetWorld()->SpawnActor<>();
}

void AMyPawn::Boost()
{

}

void AMyPawn::UnBoost()
{
}

void AMyPawn::EnhancedBoost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("EnhancedBoost"));

	BoostValue = 1.0f;
}

void AMyPawn::EnhancedUnBoost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("EnhancedUnBoost"));

	BoostValue = 0.5f;
}

void AMyPawn::EnhancedFire(const FInputActionValue& Value)
{
}

void AMyPawn::EnhancedPitchAndRoll(const FInputActionValue& Value)
{
}

