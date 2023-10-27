/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"

 /**
  * The state of the world (the 'logic world' for reasoning with GOAP) is made up of atoms. 
  * An atom is a predicate (a simple string) and a boolean as its truth value.  *
  */
class GOAPNPC_API GOAPWorldState
{
private:

	TMap<FGameplayTag, bool> atoms;

public:

	GOAPWorldState();

	~GOAPWorldState();

	GOAPWorldState(const TMap<FGameplayTag, bool>& atoms);

	bool operator==(const GOAPWorldState& w) const;

	bool isIncluded(const GOAPWorldState& w) const;

	const TMap<FGameplayTag, bool>& getAtoms() const;

	void setAtoms(const TMap<FGameplayTag, bool>& atoms);

	void addAtom(FGameplayTag name, bool value);

	void cleanAtoms();

	// Mixes two states of the world
	void joinWorldState(const GOAPWorldState& w);

	bool isEmpty() const;
};
