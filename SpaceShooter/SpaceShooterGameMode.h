// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Enemy.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterGameMode : public AGameMode
{
	GENERATED_BODY()

	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;


public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemy> EnemyBluePrint;
	    

	float EnemyTimer;
	float GameTimer;
	void IncrementScore();
	void OnGameOver();


	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void changeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	int Score=0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> StartingWidgetClass;
	   
	UPROPERTY()
		UUserWidget* CurrentWidget;

	
	
	
};
