// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneticCodingActorP.generated.h"



UCLASS()
/// <summary>
/// Meant to limite user from adding unwantd actors 
/// 
/// How to use: 
/// You can either inherate from GeneticCodingActorP.h or you can create a blueprite from this actor class
/// </summary>
class GENETICCODINGPLUGIN_API AGeneticCodingActorP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneticCodingActorP();
};
