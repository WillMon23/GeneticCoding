// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneticCodingComponentP.h"
#include "GeneticCodingGameManagerP.generated.h"

/**
 * 
 */
UCLASS()
class GENETICCODINGPLUGIN_API UGeneticCodingGameManagerP : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		AActor* currentSpecimen;

	UPROPERTY(EditAnywhere)
		TArray<UGeneticCodingComponentP*> GeneCodes;
};
