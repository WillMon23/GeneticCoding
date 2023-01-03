// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticCodingComponent.h"
#include "GeneticCodingGameManager.h"


// Sets default values for this component's properties
UGeneticCodingComponent::UGeneticCodingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGeneticCodingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneticCodingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UGeneticCodingComponent::CanReproduce()
{
	return  CanReproduce(Traits);
}

bool UGeneticCodingComponent::CanReproduce(TArray<FTraitInfo> otherParentGenes)
{
	//allies, helps with deciding what 
	Allies arr[4];
	Allies winningGen;

	if (!ReadyToReproduce)
		return false;

	_offSpring.SetNum(Traits.Num());

	for (int j = 0; j < Traits.Num(); j++) {

		if (Traits[j].TraitsName != otherParentGenes[j].TraitsName)
		{
			_offSpring[j] = Traits[j];
			continue;
		}
		Traits[j].Value = Traits[j].GetValue();

		_offSpring[j] = Traits[j];
		
		arr[0].alliesOne = Traits[j].IsDominateTraitOne;            arr[1].alliesOne = Traits[j].IsDominateTraitTwo;
		arr[0].alliesTwo = otherParentGenes[j].IsDominateTraitOne;  arr[1].alliesTwo = otherParentGenes[j].IsDominateTraitOne;

//_____________________________________________________________________________________________________________________

		arr[2].alliesOne = otherParentGenes[j].IsDominateTraitTwo;  arr[3].alliesOne = otherParentGenes[j].IsDominateTraitTwo;
		arr[2].alliesTwo = Traits[j].IsDominateTraitOne;            arr[3].alliesTwo = Traits[j].IsDominateTraitTwo;

		RNG = FMath::RandRange(0, 3);

		winningGen = arr[RNG];

		_offSpring[j].IsDominateTraitOne = winningGen.alliesOne;
		_offSpring[j].IsDominateTraitTwo = winningGen.alliesTwo;

		_offSpring[j].Value = _offSpring[j].GetValue();
	}
	//if(UGeneticCodingComponent* other = GetOwner()->FindComponentByClass<UGeneticCodingComponent>())
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
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	FTransform tranform = GetOwner()->GetTransform();

	if (CanReproduce()) {

		AActor* MySpawnActor = GetWorld()->SpawnActor<AActor>(Location, Rotation, SpawnInfo);

		UGeneticCodingComponent* TransferDNA = NewObject<UGeneticCodingComponent>(MySpawnActor,TEXT("GeneticCoding"));

		//Keeps track of the new generations parent
		TransferDNA->_parent = GetOwner();

		if(_gameManager)
			TransferDNA->_gameManager = _gameManager;
		
		TransferDNA->Traits = _offSpring;

		TransferDNA->RegisterComponent();

		MySpawnActor->AddInstanceComponent(TransferDNA);
		AddToManager();
	}
}



