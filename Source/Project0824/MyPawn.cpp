// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyActorComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values ���� �޸𸮿� ����
// CDO ����.
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// ƽ�� �ƹ��͵� �������� �ʴµ� �����ִٸ� �������ϰ� �� �� �����Ƿ� �Ʒ��� �Լ��� ƽ�� ���� �� �ִ�.(���)
	// �������Ʈ������ ���� ���ÿ��� On/Off�� �����ϴ�.
	PrimaryActorTick.bCanEverTick = true;

	// �޸𸮿� �ڽ� ������Ʈ ����. 
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 20, 20));
	// �θ��� ���� �ٲٴ� ���̹Ƿ� ���� ���� ������ �ڽ��� ���� ������ �ʴ´�. ������ �����.

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	// Load Mesh = �������� �ƴ϶� �������ڸ��� CDO�� Mesh�� �ҷ���
	// Fclass = BP class , FObject = ����
	// ������ ���� struture���� �ڷ���, ������ �ڴ� ������ ����.
	// �����Ҷ����� loading�ϸ� �ȵǹǷ� �տ� static�� �ٿ� �ѹ��� �����Ѵ�.
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

	// ���� ������Ʈ�� Ʈ�������� ������ �ʴ´�.(attach�� �ʿ䰡 ����.)
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

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

