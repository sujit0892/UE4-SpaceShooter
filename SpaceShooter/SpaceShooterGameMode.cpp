// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"
#include "GameWidget.h"
void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	changeMenuWidget(StartingWidgetClass);
	((UGameWidget* ) CurrentWidget )->onLoad();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;
	if (EnemyTimer <= 0.0f)
	{
		float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage;
		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = FVector(600.0f, FMath::FRandRange(-800.0f, 800.0f), 20.0f);
			World->SpawnActor<AEnemy>(EnemyBluePrint, Location, FRotator::ZeroRotator);
		}
	}
}

void ASpaceShooterGameMode::changeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;

	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport();
	}
}
 
void ASpaceShooterGameMode::IncrementScore()
{
	Score += 100;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void ASpaceShooterGameMode::OnGameOver()
{

	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

