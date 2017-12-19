// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShooterGameMode.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);

}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += speed * DeltaTime;
	SetActorLocation(NewLocation);
	if (NewLocation.X > 600.0f)
		this->Destroy();

}
void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (otherActor->IsA(AEnemy::StaticClass()))
	{
		
		this->Destroy();
		otherActor->Destroy();
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
		
	}
}

