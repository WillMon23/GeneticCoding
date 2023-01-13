// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneticCodingTraitInfoP.h"
#include "GeneticCodingComponentP.generated.h"

class AGeneticCodingActorP;

struct Allies {
	bool alliesOne = false;
	bool alliesTwo = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENETICCODINGPLUGIN_API UGeneticCodingComponentP : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// <summary>
	/// Sets default values for this component's properties
	/// </summary>
	UGeneticCodingComponentP();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Spawns the object with a position and a direction/rotation
	/// </summary>
	/// <param name="location">Position it spawns in</param>
	/// <param name="rotation">direction is spawns in</param>
	/// <returns>New object spawned refrenced from AGeneticCodingActor</returns>
	AGeneticCodingActorP* SpawnObject(FVector location, FRotator rotation);

	UFUNCTION(BlueprintCallable)
	virtual void SetVariables();

	UFUNCTION(BlueprintCallable)
	float AddToGenePool(FString name, bool traitsDomOne, bool traitsDomTwo, float domineteTrait, float resessiveTrait);

	/// <summary>
	/// Takes it's self recreates it with a new set of traits inherited by it's own traits 
	/// based on the trait info provided 
	/// </summary>
	/// <returns>returns true If the inheritance passed perfectly</returns>
	bool CanReproduce();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Takes Takes some other genes then recreates a new set of traits inherited by it's own traits 
	/// based on the trait info provided
	/// Then takes the name an attaches To the other 
	/// </summary>
	/// <param name="otherGenes">the other gene been contribuatting to the inheritance</param>
	/// <returns>returns true If the inheritance passed perfectly</returns>
	bool CanReproduce(UGeneticCodingComponentP* otherGenes);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Updates the data asset attached to this component 
	/// </summary>
	void AddToManager();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Once ready for recreate it'll spawn a new actor with a new genepool inherited 
	/// </summary>
	void Recreate(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Sets the current stat of reproduction
	/// </summary>
	/// <param name="reproductionStat"></param>
	void IsReadyToRepoduce(bool reproductionStat) { _readyToReproduce = reproductionStat; }

public:
	UPROPERTY(EditAnywhere)
	TArray<FGeneticCodingTraitInfoP> GenePool;

	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AGeneticCodingActorP> ActorToSpawn;
private:
	

	UPROPERTY(EditAnywhere)
		bool _readyToReproduce = false;

	UPROPERTY(EditAnywhere)
		class UGeneticCodingGameManagerP* _gameManager;

	UGeneticCodingComponentP* _offSpring;
	AActor* _parent;
};
