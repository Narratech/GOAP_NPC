/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#include "GOAPWorldState.h"

GOAPWorldState::GOAPWorldState() {}

GOAPWorldState::~GOAPWorldState() {}

GOAPWorldState::GOAPWorldState(const TMap<FGameplayTag, bool>& a)
{
	atoms = a;
}

bool GOAPWorldState::operator==(const GOAPWorldState& w) const
{
	return atoms.OrderIndependentCompareEqual(w.getAtoms());
}

bool GOAPWorldState::isIncluded(const GOAPWorldState& w) const
{
	for (auto requirement : w.getAtoms())
	{
		const auto* value = atoms.Find(requirement.Key);
		if (value)
		{
			if (*value != requirement.Value)
				return false;
		}
		else return false;
	}
	return true;

}

const TMap<FGameplayTag, bool>& GOAPWorldState::getAtoms() const
{
	return atoms;
}

void GOAPWorldState::setAtoms(const TMap<FGameplayTag, bool>& a)
{
	atoms = a;
}

void GOAPWorldState::addAtom(FGameplayTag name, bool value)
{
	atoms.Add(name, value);
}

void GOAPWorldState::cleanAtoms()
{
	atoms.Empty();
}

void GOAPWorldState::joinWorldState(const GOAPWorldState& w)
{
	for (auto atom : w.getAtoms())
	{
		atoms.Add(atom.Key, atom.Value);
	}
}

bool GOAPWorldState::isEmpty() const
{
	return atoms.Num() == 0;
}
