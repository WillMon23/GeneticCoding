// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticCodingComponent.h"
#include "GeneticCodingGameManager.h"
#include "GeneticCodingActor.h"


// Sets default values for this component's properties
UGeneticCodingComponent::UGeneticCodingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Spawns the object with a position and a direction/rotation
AGeneticCodingActor* UGeneticCodingComponent::SpawnObject(FVector location, FRotator rotation)
{
	//Sets the perameters to for a new actor on scene  
		FActorSpawnParameters SpawnParams;

		//Takes the refrence GeneticCodeActer being passed in through actorToSpawn
		AGeneticCodingActor* SpawnedActorRef = GetWorld()->SpawnActor<AGeneticCodingActor>(_actorToSpawn, location, rotation, SpawnParams);
		
		return SpawnedActorRef;
}

/// <summary>
/// Takes it's self recreates it with a new set of traits inherited by it's own traits 
/// based on the trait info provided 
/// </summary>
/// <returns>returns true If the inheritance passed perfectly</returns>
bool UGeneticCodingComponent::CanReproduce()
{
	return  CanReproduce(this);
}

/// <summary>
/// Takes Takes some other genes then recreates a new set of traits inherited by it's own traits 
/// based on the trait info provided
/// Then takes the name an attaches To the other 
/// </summary>
/// <param name="otherGenes">the other gene been contribuatting to the inheritance</param>
/// <returns>returns true If the inheritance passed perfectly</returns>
bool UGeneticCodingComponent::CanReproduce(UGeneticCodingComponent* otherGenes)
{
	//Meant to recreate mondels law of inheritance chart
	Allies arr[4];
	//Holds the choosen allieses for that gene
	Allies winningAllies;

	//If it's not ready to reproduce 
	if (!_readyToReproduce)
		//Stop trying to recreate
		return false;
	//Creates a new offspring to make to preping to inherite new genes 
	_offSpring = NewObject<UGeneticCodingComponent>();

	_offSpring->_genePool.SetNum(_genePool.Num());

	for (int j = 0; j < _genePool.Num(); j++) {

		//If the name dose not match 
		if (_genePool[j].TraitsName != otherGenes->_genePool[j].TraitsName)
		{
			//Will insted take the perants gene ins
			_offSpring->_genePool[j] = _genePool[j];
			_offSpring->_genePool.Add(otherGenes->_genePool[j]);
			continue;
		}
		_offSpring->_genePool[j] = _genePool[j];
		
		//Sets all the possible combination in a chart 
		//Recreating mondels law of inheritance chart

																			/* | */
		arr[0].alliesOne = _genePool[j].IsDominateTraitOne;					/* | */        arr[1].alliesOne = _genePool[j].IsDominateTraitTwo;
		arr[0].alliesTwo = otherGenes->_genePool[j].IsDominateTraitOne;		/* | */        arr[1].alliesTwo = otherGenes->_genePool[j].IsDominateTraitOne;
																			/* | */
//_____________________________________________________________________________|___________________________________________________________________________________
																			/* | */
		arr[2].alliesOne = otherGenes->_genePool[j].IsDominateTraitTwo;		/* | */			arr[3].alliesOne = otherGenes->_genePool[j].IsDominateTraitTwo;
		arr[2].alliesTwo = _genePool[j].IsDominateTraitOne;					/* | */			arr[3].alliesTwo = _genePool[j].IsDominateTraitTwo;
																			/* | */
		
		//Gets a random value between 0 and 3 to choose from the 4 spots in the cantainer
		int RNG = FMath::RandRange(0, 3);

		winningAllies = arr[RNG];

		_offSpring->_genePool[j].IsDominateTraitOne = winningAllies.alliesOne;
		_offSpring->_genePool[j].IsDominateTraitTwo = winningAllies.alliesTwo;

		_offSpring->_genePool[j].Value = _offSpring->_genePool[j].GetValue();
	}

	_offSpring->Name = (Name + " , " + otherGenes->Name);
	IsReadyToRepoduce(false);
	return  true;
}

/// <summary>
/// Updates the data asset attached to this component 
/// </summary>
void UGeneticCodingComponent::AddToManager()
{
	//IF datat asset manager attached to component 
	if (_gameManager) {
		
		//Sets the currnet specimen to be this owner
		_gameManager->currentSpecimen = GetOwner();
		//Adds this componnt data asset
		_gameManager->GeneCodes.Add(this);
	}
}

/// <summary>
/// Once ready for recreate it'll spawn a new actor with a new genepool inherited 
/// </summary>
void UGeneticCodingComponent::Recreate(FVector location, FRotator rotation)
{
	//Lets user know they need to add a AGeneticCodingActor
	if (!_actorToSpawn)
	{
		FString DebugMessage = "Missing AGeneticCodingActor";
		UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);
		return;
	}

	if (CanReproduce()) {

		AGeneticCodingActor* MySpawnActor = SpawnObject(location, rotation);

		UGeneticCodingComponent* TransferDNA = NewObject<UGeneticCodingComponent>(MySpawnActor,TEXT("GeneticCoding"));
	
		if (_gameManager)
			TransferDNA->_gameManager = _gameManager;

		//Keeps track of the new generations parent
		TransferDNA->_parent = GetOwner();
		//Sets it's new gene pool
		TransferDNA->_genePool = _offSpring->_genePool;

		//Sets nre name to there geneticCode component
		TransferDNA->Name = _offSpring->Name;

		//Sets bp to be that of this one 
		TransferDNA->_actorToSpawn = _actorToSpawn;

		
		TransferDNA->RegisterComponent();

		MySpawnActor->AddInstanceComponent(TransferDNA);
		AddToManager();
	}
}




