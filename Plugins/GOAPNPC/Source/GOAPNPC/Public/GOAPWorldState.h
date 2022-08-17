/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include <map>
#include "CoreMinimal.h"

 /**
  * The state of the world (the 'logic world' for reasoning with GOAP) is made up of atoms. 
  * An atom is a predicate (a simple string) and a boolean as its truth value.  *
  */
class GOAPNPC_API GOAPWorldState
{
private:

	std::map<FString, bool> atoms;

public:

	GOAPWorldState();

	~GOAPWorldState();

	GOAPWorldState(const std::map<FString, bool>& atoms);

	bool operator==(GOAPWorldState w);

	bool isIncluded(GOAPWorldState w);

	const std::map<FString, bool>& getAtoms();

	void setAtoms(const std::map<FString, bool>& atoms);

	void addAtom(FString name, bool value);

	void cleanAtoms();

	// Mixes two states of the world
	void joinWorldState(GOAPWorldState w);

	bool isEmpty();
};
