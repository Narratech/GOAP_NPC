/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "GOAPAction.h"
#include "CoreMinimal.h"

 /**
  * Node used in A* algorithm. Represents a possible state of the world.
  */
class GOAPNPC_API GOAPNode
{
private:

	GOAPWorldState world;

	int h;

	float g;

	int parent;

	// Chosen action to reach this node.
	UGOAPAction* action;

public:
	GOAPNode();

	GOAPNode(UGOAPAction* a);

	//OPERATORS 
	bool operator==(GOAPNode n);

	// GETS

	int getH();

	float getG();

	float getF();

	int getParent();

	GOAPWorldState getWorld();

	UGOAPAction* getAction();

	// SETS

	void setH(int value);

	void setH(GOAPWorldState w);

	void setG(GOAPNode p);

	void setParent(int p);

	void setWorld(GOAPWorldState w);

	void setAction(UGOAPAction* a);
};
