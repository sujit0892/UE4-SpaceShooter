// Fill out your copyright notice in the Description page of Project Settings.

#include "ShpController.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShooterGameMode.h"

// Sets default values
AShpController::AShpController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	CollisionBox->bGenerateOverlapEvents = true;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShpController::OnOverlap);

}

// Called when the game starts or when spawned
void AShpController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShpController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = CurrentVelocity * speed * DeltaTime + GetActorLocation();
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AShpController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &AShpController::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AShpController::Move_YAxis);
	PlayerInputComponent->BindAction("shoot", IE_Pressed, this, &AShpController::onShoot);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AShpController::onRestart).bExecuteWhenPaused = true;

}

void AShpController::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}
void AShpController::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void AShpController::onShoot()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector Location = GetActorLocation();
		World->SpawnActor<ABulletController>(BulletBluePrint, Location, FRotator::ZeroRotator);
	}
}

void AShpController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (otherActor->IsA(AEnemy::StaticClass()))
	{
		died = true;
		this->SetActorHiddenInGame(true);
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}

void AShpController::onRestart()
{
	if (died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}