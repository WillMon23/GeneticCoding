// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneticCodingComponentP.h"
#include "SpawnBoxBabies.generated.h"

/**
 * 
 */
UCLASS()
class GENETICCODING_API USpawnBoxBabies : public UGeneticCodingComponentP
{
	GENERATED_BODY()
	
public:
	void SetVariables() override;
};
