// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraitInfo.h"
#include "GeneticCodingComponent.generated.h"

struct Allies {
	bool alliesOne = false;
	bool alliesTwo = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENETICCODING_API UGeneticCodingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneticCodingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SpawnObject(FVector location, FRotator rotation);
private:
	bool CanReproduce();
	bool CanReproduce(TArray<FTraitInfo> parent);

	void AddToManager();

	UFUNCTION(CallInEditor)
	void Recreate();

public:
	UPROPERTY(EditAnywhere)
	TArray<FTraitInfo> Traits;
	
	UPROPERTY(EditAnywhere)
	bool ReadyToReproduce = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _actorToSpawn;

	UPROPERTY(EditAnywhere)
	class UGeneticCodingGameManager* _gameManager;

	UPROPERTY(EditAnywhere)
	int RNG = 0;

	UPROPERTY(EditAnywhere)
	FString Name;


private:
	TArray<FTraitInfo> _offSpring;
	AActor* _parent;

	
};
