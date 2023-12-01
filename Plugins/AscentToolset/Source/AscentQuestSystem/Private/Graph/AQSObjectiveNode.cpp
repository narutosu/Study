// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/AQSObjectiveNode.h"
#include "AGSCondition.h"
#include <Kismet/GameplayStatics.h>
#include "AQSQuestTargetComponent.h"
#include <GameFramework/Actor.h>
#include "Graph/AQSQuest.h"
#include <GameFramework/PlayerController.h>
#include "AQSQuestObjective.h"
#include "AQSQuestManagerComponent.h"

void UAQSObjectiveNode::ActivateNode()
{
	Super::ActivateNode();
	APlayerController* contr = GetPlayerController();
	CurrentRepetitions = 0;

	if (!Objective) {
		Objective = NewObject<UAQSQuestObjective>();
	}

	if (Objective) {
		Objective->Internal_OnObjectiveStarted(this);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing Objective! - UAQSObjectiveNode::ActivateNode"));
	}
	UpdateReferences(EQuestUpdateType::EStarted);
	bIsCompleted = false;
	UAQSQuest* quest = Cast< UAQSQuest>(GetGraph());
	
	SetIsTracked(quest->IsCurrentTrackedQuest());


}

void UAQSObjectiveNode::DeactivateNode()
{
	Super::DeactivateNode();
	bIsCompleted = true;
	UpdateReferences(EQuestUpdateType::ECompleted);

	if (Objective) {
		Objective->OnObjectiveCompleted();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing Objective! - UAQSObjectiveNode::DeactivateNode"));
	}
}

UAQSObjectiveNode::UAQSObjectiveNode()
{
#if WITH_EDITOR
	BackgroundColor = FLinearColor::Black;
	#endif

	//Objective = CreateDefaultSubobject<UAQSQuestObjective>("Default Objective");
}

bool UAQSObjectiveNode::TryToComplete()
{
	CurrentRepetitions++;

	UpdateReferences(EQuestUpdateType::EUpdated);
	if (CurrentRepetitions >= Repetitions) {

		for (UAGSCondition* condition : CompleteConditions) {
			if (!condition->VerifyForNode(GetPlayerController(), this)) {

				return false;
			}
		}
		
		return true;
	}
	return false;
}
   
 TArray<class UAQSQuestTargetComponent*> UAQSObjectiveNode::GetObjectiveTargets() const
{
	 if (!Objective) {
		 UE_LOG(LogTemp, Error, TEXT("Missing Objective! - UAQSObjectiveNode::GetObjectiveTargets"));
		 return TArray< UAQSQuestTargetComponent*>();
	 }

	 return Objective->GetObjectiveTargets();
}

 FGameplayTag UAQSObjectiveNode::GetObjectiveTag() const
 {
	 if (!Objective) {
		 UE_LOG(LogTemp, Error, TEXT("Missing Objective! - UAQSObjectiveNode::GetObjectiveTag"));
		 return FGameplayTag();
	 }

	 return Objective->GetObjectiveTag();
 }



void UAQSObjectiveNode::SetIsTracked(bool inTracked)
{
	bIsTracked = inTracked;
	UpdateReferences(EQuestUpdateType::EUpdated);
}

void UAQSObjectiveNode::UpdateReferences(EQuestUpdateType updateType)
{
	if (!Objective) {
		UE_LOG(LogTemp, Error, TEXT("Missing Objective! - UAQSObjectiveNode::UpdateReferences"));
		return;
	}

	UAQSQuest* quest = Cast< UAQSQuest>(GetGraph());
	if (!quest) {
		UE_LOG(LogTemp, Error, TEXT("Missing Quest! - UAQSObjectiveNode::UpdateReferences"));
		return;
	}

	const FGameplayTag& questTag = quest->GetQuestTag();
	TObjectPtr<class UAQSQuestManagerComponent> questMan = quest->GetQuestManager();

	if (questMan) {
		questMan->ServerDispatchObjectiveUpdate(Objective->GetObjectiveTag(), questTag, updateType);
	}
}

#if WITH_EDITOR

FText UAQSObjectiveNode::GetNodeTitle() const
{
	if (!Objective) {
		return FText::FromString("Set Objective");
	}

	if (Objective->GetObjectiveName().IsEmpty()) {
		return FText::FromString("Set Objective Name");
	}
	return Objective->GetObjectiveName();
}

#endif