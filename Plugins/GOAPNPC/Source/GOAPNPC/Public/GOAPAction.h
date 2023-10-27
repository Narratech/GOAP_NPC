/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "GOAPWorldState.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTags.h"

#include "GOAPAction.generated.h"

 /**
 * Auxiliary struct to get WorldState's atoms from Blueprints' description.
 */
USTRUCT(BlueprintType)
struct GOAPNPC_API FAtom
{
	GENERATED_USTRUCT_BODY()

	FAtom() = default;

	FAtom(FGameplayTag _tag, bool _value)
		: tag(_tag)
		, value(_value)
	{}

#if WITH_EDITORONLY_DATA
		// DEPRECATED: Name of the atom (predicate).
		UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use gameplay tag instead."))
		FString name_DEPRECATED;

	void PostSerialize(const FArchive& Ar);
#endif

	// Name of the atom (predicate).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Category = "Atom"))
	FGameplayTag tag;

	// Value of the atom (truth value).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Atom)
		bool value = false;

};

#if WITH_EDITORONLY_DATA
template<>
struct TStructOpsTypeTraits<FAtom> : public TStructOpsTypeTraitsBase2<FAtom>
{
	enum
	{
		WithPostSerialize = true
	};
};
#endif

/**
 * GOAPAction class contains every attribute and function needed to define an action.
 * Represent edges in the planner algorithm.
 */
UCLASS(Blueprintable)
class GOAPNPC_API UGOAPAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		FString name;

	// Cost of the action. The planner will take this into account when making the cheapest plan.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float cost;

	// Object or class type of actor this action's target should have. This can be None if your action doesn't need a target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		TSubclassOf<AActor> targetsType;

	// Preconditions or requirements needed to perform the action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WorldState)
		TArray<FAtom> preconditions;

	// Effects or postconditions caused by the action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WorldState)
		TArray<FAtom> effects;


private:

	AActor* target = nullptr;

	GOAPWorldState wsPreconditions;

	GOAPWorldState wsEffects;

public:
	// Search all actors of targetsType class located in the world.
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		TArray<AActor*> getTargetsList(APawn* p) const;

	// Optional function to check if it's possible to perform the action.
	UFUNCTION(BlueprintImplementableEvent, Category = GOAPAction)
		bool checkProceduralPrecondition(APawn* p);

	// Performs the action.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = GOAPAction)
		bool doAction(APawn* p);

	// Generate action's preconditions and effects.
	void create_P_E();

	// COMPARATORS

	bool operator==(const UGOAPAction& action) const;

	bool operator!=(const UGOAPAction& action) const;

	// GETS

	FString getName() const;

	float getCost() const;

	// Gets the chosen target from targetList or the one specific in setTarget().
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		AActor* getTarget() const;

	const GOAPWorldState& getPreconditions() const;

	const GOAPWorldState& getEffects() const;

	// SETS

	void setName(FString n);

	void setCost(float c);

	// Sets a specific target.
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		void setTarget(AActor* t);

	void setPreconditions(GOAPWorldState preconditionAtoms);

	void setEffects(GOAPWorldState effectAtoms);
};
