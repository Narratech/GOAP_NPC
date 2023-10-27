/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "GOAPPlanner.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h" // To avoid GOAPController.cpp(93): error C2065: 'GEngine': undeclared identifier
#include "GOAPController.generated.h"


 /**
 * AIController containg the planner, states of the current and desired world, and the list of available actions the AI can perform.
 * Current world and desired world are private for each AI, but it's possible to create a global current world to notify changes to other AIs.
  */
UCLASS()
class GOAPNPC_API AGOAPController : public AAIController
{
	GENERATED_BODY()

public:

	// State of the current world.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<FAtom> currentWorld;

	// State of the world in wich the goal has been achieved.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<FAtom> desiredWorld;

	// List of actions AI can do.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<TSubclassOf<UGOAPAction>> actions;


	// Maximum algorithm depth.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		int maxDepth = 100;

	//Debug info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		bool debug;

	//Include controller's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		bool controller;
	


private:

	GOAPPlanner* planner;

	TArray<UGOAPAction*> auxActions;

	TArray<UGOAPAction*> plan;

	GOAPWorldState wsCurrentWorld;

	GOAPWorldState wsDesiredWorld;

public:

	AGOAPController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* pawn) override;

	virtual void Tick(float DeltaSeconds) override;

	// Creates and execute the plan.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		bool executeGOAP();

	// Creates actions plan
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		bool generatePlan();

	// Returns the actions that make up the plan.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<UGOAPAction*> getPlan();

	// Sets the goal of the AI, this function can also be used to change the goal.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void setGoal(const TArray<FAtom>& newGoal);

	// Adds or modifies atoms from the desired world state. Atoms already existing in the desired world state are modified by new input values.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void updateGoal(const TArray<FAtom>& atoms);

	// Sets the current world state of the AI, this function can also be used to change the current world state.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void setCurrentWorld(const TArray<FAtom>& newCurrentWorld);

	// Adds or modifies atoms from the current world state. Atoms already existing in the current world state are modified by new input values.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void updateCurrentWorld(const TArray<FAtom>& atoms);

	// Returns the current world state atoms.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<FAtom> getCurrentWorldStateAtoms() const;

	// Returns the desired world state atoms.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<FAtom> getDesiredWorldStateAtoms() const;

private:
	void debugInfo();
};
