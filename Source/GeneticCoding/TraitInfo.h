#include "TraitInfo.generated.h"


USTRUCT(immutable, noexport, BlueprintType)
/// <summary>
/// 
/// </summary>
/// <typeparam name="T">The type of trait</typeparam>
struct FTraitInfo {

	

	UPROPERTY(EditAnywhere)
		FString TraitsName;

	UPROPERTY(EditAnywhere)
		bool IsDominateTraitOne;

	UPROPERTY(EditAnywhere)
		bool IsDominateTraitTwo;

	UPROPERTY(EditAnywhere)
	float DominateTraitValue = 0;

	UPROPERTY(EditAnywhere)
	float ResessiveTraitValue = 0;
	
	UPROPERTY(EditAnywhere)
		float Value;

	float GetValue() {
		if (IsDominateTraitOne || IsDominateTraitTwo)
			return DominateTraitValue;

		return ResessiveTraitValue;
	}

	bool IsDominant() {
		return IsDominateTraitOne || IsDominateTraitTwo;
	}
	
};