/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#include "GOAPAction.h"


UGOAPAction::UGOAPAction() {}

void UGOAPAction::create_P_E()
{
	for (FAtom itP : preconditions)
	{
		wsPreconditions.addAtom(itP.name, itP.value);
	}
	for (FAtom itE : effects)
	{
		wsEffects.addAtom(itE.name, itE.value);
	}
	if (targetsType == NULL)
		UE_LOG(LogTemp, Warning, TEXT("Targets' type of '%s' action are not defined."), *name);
}

TArray<AActor*> UGOAPAction::getTargetsList(APawn* p)
{
	TArray<AActor*> actorsFound;
	// AVOID CRASHES, checking if targetsType is empty or not!
	UGameplayStatics::GetAllActorsOfClass(p->GetWorld(), targetsType, actorsFound);
	return actorsFound;
}

bool UGOAPAction::operator==(UGOAPAction& a)
{
	return this->cost == a.getCost() && target == a.getTarget() && wsPreconditions == a.getPreconditions() && wsEffects == a.getEffects();
}

bool UGOAPAction::operator!=(UGOAPAction& a)
{
	return !(*this == a);
}

// GETS

FString UGOAPAction::getName()
{
	return this->name;
}

float UGOAPAction::getCost()
{
	return this->cost;
}

AActor* UGOAPAction::getTarget()
{
	return target;
}

GOAPWorldState UGOAPAction::getPreconditions()
{
	return wsPreconditions;
}

GOAPWorldState UGOAPAction::getEffects()
{
	return wsEffects;
}

// SETS

void UGOAPAction::setName(FString n)
{
	this->name = n;
}

void UGOAPAction::setCost(float c)
{
	cost = c;
}

void UGOAPAction::setTarget(AActor* t)
{
	target = t;
}

void UGOAPAction::setPreconditions(GOAPWorldState pre)
{
	wsPreconditions = pre;
}

void UGOAPAction::setEffects(GOAPWorldState ef)
{
	wsEffects = ef;
}
