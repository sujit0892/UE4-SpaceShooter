// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"
#include "ShpController.generated.h"

UCLASS()
class SPACESHOOTER_API AShpController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShpController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		float speed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<ABulletController> BulletBluePrint;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void onShoot();
	void onRestart();

	FVector CurrentVelocity;

	bool died;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
