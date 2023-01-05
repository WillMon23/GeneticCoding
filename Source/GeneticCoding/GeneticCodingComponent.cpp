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

AGeneticCodingActor* UGeneticCodingComponent::SpawnObject(FVector location, FRotator rotation)
{
		FActorSpawnParameters SpawnParams;
		AGeneticCodingActor* SpawnedActorRef = GetWorld()->SpawnActor<AGeneticCodingActor>(_actorToSpawn, location, rotation, SpawnParams);
		return SpawnedActorRef;
	
}

bool UGeneticCodingComponent::CanReproduce()
{
	return  CanReproduce(this);
}

bool UGeneticCodingComponent::CanReproduce(UGeneticCodingComponent* otherGenes)
{
	//meant to recreate mondelas law of inheritance chart
	Allies arr[4];
	//Holds the 
	Allies winningAllies;

	if (!ReadyToReproduce)
		return false;

	_offSpring = NewObject<UGeneticCodingComponent>();

	_offSpring->GenePool.SetNum(GenePool.Num());

	for (int j = 0; j < GenePool.Num(); j++) {

		if (GenePool[j].TraitsName != otherGenes->GenePool[j].TraitsName)
		{
			_offSpring->GenePool[j] = GenePool[j];
			continue;
		}
		_offSpring->GenePool[j] = GenePool[j];
		


		arr[0].alliesOne = GenePool[j].IsDominateTraitOne;            arr[1].alliesOne = GenePool[j].IsDominateTraitTwo;
		arr[0].alliesTwo = otherGenes->GenePool[j].IsDominateTraitOne;  arr[1].alliesTwo = otherGenes->GenePool[j].IsDominateTraitOne;

//_____________________________________________________________________________________________________________________

		arr[2].alliesOne = otherGenes->GenePool[j].IsDominateTraitTwo;  arr[3].alliesOne = otherGenes->GenePool[j].IsDominateTraitTwo;
		arr[2].alliesTwo = GenePool[j].IsDominateTraitOne;            arr[3].alliesTwo = GenePool[j].IsDominateTraitTwo;

		RNG = FMath::RandRange(0, 3);

		winningAllies = arr[RNG];

		_offSpring->GenePool[j].IsDominateTraitOne = winningAllies.alliesOne;
		_offSpring->GenePool[j].IsDominateTraitTwo = winningAllies.alliesTwo;

		_offSpring->GenePool[j].Value = _offSpring->GenePool[j].GetValue();
	}
	//if(UGeneticCodingComponent* other = GetOwner()->FindComponentByClass<UGeneticCodingComponent>())

	_offSpring->Name = (Name + " , " + otherGenes->Name);
	return  true;
}

void UGeneticCodingComponent::AddToManager()
{
	if (_gameManager) {
		_gameManager->currentSpecimen = GetOwner();
		_gameManager->GeneCodes.Add(this);
	}
}

void UGeneticCodingComponent::Recreate()
{
	FVector Location = GetOwner()->GetActorTransform().GetLocation();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	if (!_actorToSpawn)
	{
		FString DebugMessage = "Missing AGeneticCodingActor";
		UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);
		return;
	}

	if (CanReproduce()) {

		AGeneticCodingActor* MySpawnActor = SpawnObject(Location, Rotation);

		UGeneticCodingComponent* TransferDNA = NewObject<UGeneticCodingComponent>(MySpawnActor,TEXT("GeneticCoding"));
	
		if (_gameManager)
			TransferDNA->_gameManager = _gameManager;

		//Keeps track of the new generations parent
		TransferDNA->_parent = GetOwner();
	
		TransferDNA->GenePool = _offSpring->GenePool;

		TransferDNA->Name = _offSpring->Name;

		TransferDNA->_actorToSpawn = _actorToSpawn;

		TransferDNA->RegisterComponent();

		MySpawnActor->AddInstanceComponent(TransferDNA);
		AddToManager();
	}
}




