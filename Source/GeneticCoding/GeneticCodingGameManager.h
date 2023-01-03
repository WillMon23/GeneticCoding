// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneticCodingComponent.h"
#include "GeneticCodingGameManager.generated.h"

/**
 * Collect and holds the data bring created by the genetic Code
 */
UCLASS()
class GENETICCODING_API UGeneticCodingGameManager : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	AActor* currentSpecimen;

	UPROPERTY(EditAnywhere)
	TArray<UGeneticCodingComponent*> GeneCodes;
	
};
