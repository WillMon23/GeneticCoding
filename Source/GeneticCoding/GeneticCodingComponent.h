// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraitInfo.h"
#include "GeneticCodingComponent.generated.h"

class AGeneticCodingActor;

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
	
	/// <summary>
	/// Spawns the object with a position and a direction/rotation
	/// </summary>
	/// <param name="location">Position it spawns in</param>
	/// <param name="rotation">direction is spawns in</param>
	/// <returns>New object spawned refrenced from AGeneticCodingActor</returns>
	AGeneticCodingActor* SpawnObject(FVector location, FRotator rotation);
private:
	/// <summary>
	/// Takes it's self recreates it with a new set of traits inherited by it's own traits 
	/// based on the trait info provided 
	/// </summary>
	/// <returns>returns true If the inheritance passed perfectly</returns>
	bool CanReproduce();

	/// <summary>
	/// Takes Takes some other genes then recreates a new set of traits inherited by it's own traits 
	/// based on the trait info provided
	/// Then takes the name an attaches To the other 
	/// </summary>
	/// <param name="otherGenes">the other gene been contribuatting to the inheritance</param>
	/// <returns>returns true If the inheritance passed perfectly</returns>
	bool CanReproduce(UGeneticCodingComponent* otherGenes);

	/// <summary>
	/// Updates the data asset attached to this component 
	/// </summary>
	void AddToManager();

	/// <summary>
	/// Once ready for recreate it'll spawn a new actor with a new genepool inherited 
	/// </summary>
	void Recreate(FVector Location, FRotator Rotation);

	/// <summary>
	/// Sets the current stat of reproduction
	/// </summary>
	/// <param name="reproductionStat"></param>
	void IsReadyToRepoduce( bool reproductionStat) { _readyToReproduce = reproductionStat; }

public:



private:
	UPROPERTY(EditAnywhere)
		TArray<FTraitInfo> _genePool;

	UPROPERTY(EditAnywhere)
		bool _readyToReproduce = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AGeneticCodingActor> _actorToSpawn;

	UPROPERTY(EditAnywhere)
		class UGeneticCodingGameManager* _gameManager;


	UPROPERTY(EditAnywhere)
		FString Name;
	UGeneticCodingComponent* _offSpring;
	AActor* _parent;

	
};
