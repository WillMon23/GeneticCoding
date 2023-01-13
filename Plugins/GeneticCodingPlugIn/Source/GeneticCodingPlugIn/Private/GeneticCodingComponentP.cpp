// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneticCodingComponentP.h"
#include "GeneticCodingGameManagerP.h"
#include "GeneticCodingActorP.h"

// Sets default values for this component's properties
UGeneticCodingComponentP::UGeneticCodingComponentP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Spawns the object with a position and a direction/rotation
AGeneticCodingActorP* UGeneticCodingComponentP::SpawnObject(FVector location, FRotator rotation)
{
	//Sets the perameters to for a new actor on scene  
	FActorSpawnParameters SpawnParams;

	//Takes the refrence GeneticCodeActer being passed in through actorToSpawn
	AGeneticCodingActorP* SpawnedActorRef = GetWorld()->SpawnActor<AGeneticCodingActorP>(ActorToSpawn, location, rotation, SpawnParams);

	return SpawnedActorRef;
}

void UGeneticCodingComponentP::SetVariables()
{
}

float UGeneticCodingComponentP::AddToGenePool(FString name, bool traitsDomOne, bool traitsDomTwo, float domineteTrait, float resessiveTrait)
{
	FGeneticCodingTraitInfoP Trait = FGeneticCodingTraitInfoP();
	Trait.TraitsName = name;

	Trait.IsDominateTraitOne = traitsDomOne;
	Trait.IsDominateTraitTwo = traitsDomTwo;

	Trait.DominateTraitValue = domineteTrait;
	Trait.ResessiveTraitValue = resessiveTrait;
	GenePool.Add(Trait);
	return Trait.GetValue();
}

/// <summary>
/// Takes it's self recreates it with a new set of traits inherited by it's own traits 
/// based on the trait info provided 
/// </summary>
/// <returns>returns true If the inheritance passed perfectly</returns>
bool UGeneticCodingComponentP::CanReproduce()
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
bool UGeneticCodingComponentP::CanReproduce(UGeneticCodingComponentP* otherGenes)
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
	_offSpring = NewObject<UGeneticCodingComponentP>();

	_offSpring->GenePool.SetNum(GenePool.Num());

	for (int j = 0; j < GenePool.Num(); j++) {

		//If the name dose not match 
		if (GenePool[j].TraitsName != otherGenes->GenePool[j].TraitsName)
		{
			//Will insted take the perants gene ins
			_offSpring->GenePool[j] = GenePool[j];
			_offSpring->GenePool.Add(otherGenes->GenePool[j]);
			continue;
		}
		_offSpring->GenePool[j] = GenePool[j];

		//Sets all the possible combination in a chart 
		//Recreating mondels law of inheritance chart

																			/* | */
		arr[0].alliesOne = GenePool[j].IsDominateTraitOne;					/* | */        arr[1].alliesOne = GenePool[j].IsDominateTraitTwo;
		arr[0].alliesTwo = otherGenes->GenePool[j].IsDominateTraitOne;		/* | */        arr[1].alliesTwo = otherGenes->GenePool[j].IsDominateTraitOne;
		/* | */
//_____________________________________________________________________________|___________________________________________________________________________________
																			/* | */
		arr[2].alliesOne = otherGenes->GenePool[j].IsDominateTraitTwo;		/* | */			arr[3].alliesOne = otherGenes->GenePool[j].IsDominateTraitTwo;
		arr[2].alliesTwo = GenePool[j].IsDominateTraitOne;					/* | */			arr[3].alliesTwo = GenePool[j].IsDominateTraitTwo;
		/* | */

//Gets a random value between 0 and 3 to choose from the 4 spots in the cantainer
		int RNG = FMath::RandRange(0, 3);

		winningAllies = arr[RNG];

		_offSpring->GenePool[j].IsDominateTraitOne = winningAllies.alliesOne;
		_offSpring->GenePool[j].IsDominateTraitTwo = winningAllies.alliesTwo;
	}

	_offSpring->Name = (Name + " , " + otherGenes->Name);
	IsReadyToRepoduce(false);
	return  true;
}

/// <summary>
/// Updates the data asset attached to this component 
/// </summary>
void UGeneticCodingComponentP::AddToManager()
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
void UGeneticCodingComponentP::Recreate(FVector location, FRotator rotation)
{
	//Lets user know they need to add a AGeneticCodingActor
	if (!ActorToSpawn)
	{
		FString DebugMessage = "Missing AGeneticCodingActor";
		UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);
		return;
	}


	AGeneticCodingActorP* MySpawnActor = SpawnObject(location, rotation);

	UGeneticCodingComponentP* TransferDNA = NewObject<UGeneticCodingComponentP>(MySpawnActor, TEXT("GeneticCoding"));

	if (_gameManager)
		TransferDNA->_gameManager = _gameManager;

	AActor* MyActorDefaultObject = ActorToSpawn.GetDefaultObject();
	
	if (UGeneticCodingComponentP* curremtGenes = MyActorDefaultObject->FindComponentByClass<UGeneticCodingComponentP>())
		curremtGenes = TransferDNA;

	//Keeps track of the new generations parent
	TransferDNA->_parent = GetOwner();
	//Sets it's new gene pool
	TransferDNA->GenePool = _offSpring->GenePool;

	//Sets nre name to there geneticCode component
	TransferDNA->Name = _offSpring->Name;

	//Sets bp to be that of this one 
	TransferDNA->ActorToSpawn = ActorToSpawn;


	TransferDNA->RegisterComponent();

	if (UGeneticCodingComponentP* curremtGenes = MyActorDefaultObject->FindComponentByClass<UGeneticCodingComponentP>())
		curremtGenes = TransferDNA;
	else 
		MySpawnActor->AddInstanceComponent(TransferDNA);

	AddToManager();
}