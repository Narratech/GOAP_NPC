/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#include "GOAPAction.h"

#if WITH_EDITORONLY_DATA
#include "GameplayTagsEditorModule.h"

void FAtom::PostSerialize(const FArchive& Ar)
{
	if (Ar.IsLoading() && !name_DEPRECATED.IsEmpty())
	{
		FString tagName = TEXT("GOAP.") + name_DEPRECATED;
		tag = UGameplayTagsManager::Get().RequestGameplayTag(FName(tagName), false);
		if (!tag.IsValid())
		{
			IGameplayTagsEditorModule& tagsEditor = IGameplayTagsEditorModule::Get();
			bool result = tagsEditor.AddNewGameplayTagToINI(tagName);

			tag = UGameplayTagsManager::Get().RequestGameplayTag(FName(tagName));
			if (tag.IsValid())
			{
				name_DEPRECATED = "";
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Can't get Gameplay tag for (%s)"), *tagName);
			}
		}
	}

}
#endif // WITH_EDITORONLY_DATA


void UGOAPAction::create_P_E()
{
	for (FAtom& itP : preconditions)
	{
		wsPreconditions.addAtom(itP.tag, itP.value);
	}

	for (FAtom& itE : effects)
	{
		wsEffects.addAtom(itE.tag, itE.value);
	}

	if (targetsType == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Targets' type of '%s' action are not defined."), *name);
	}
}

TArray<AActor*> UGOAPAction::getTargetsList(APawn* p) const
{
	TArray<AActor*> actorsFound;
	// AVOID CRASHES, checking if targetsType is empty or not!
	UGameplayStatics::GetAllActorsOfClass(p->GetWorld(), targetsType, actorsFound);
	return actorsFound;
}

bool UGOAPAction::operator==(const UGOAPAction& a) const
{
	return this->cost == a.getCost() && target == a.getTarget() && wsPreconditions == a.getPreconditions() && wsEffects == a.getEffects();
}

bool UGOAPAction::operator!=(const UGOAPAction& a) const
{
	return !(*this == a);
}

// GETS

FString UGOAPAction::getName() const
{
	return name;
}

float UGOAPAction::getCost() const
{
	return cost;
}

AActor* UGOAPAction::getTarget() const
{
	return target;
}

const GOAPWorldState& UGOAPAction::getPreconditions() const
{
	return wsPreconditions;
}

const GOAPWorldState& UGOAPAction::getEffects() const
{
	return wsEffects;
}

// SETS

void UGOAPAction::setName(FString n)
{
	name = n;
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
