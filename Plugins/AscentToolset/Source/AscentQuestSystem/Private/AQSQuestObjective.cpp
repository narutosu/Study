// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#include "AQSQuestObjective.h"
#include "AQSQuestFunctionLibrary.h"
#include "AQSQuestManagerComponent.h"

UAQSQuestObjective::UAQSQuestObjective()
{
}

TArray<class AActor*> UAQSQuestObjective::GetObjectiveTargetsActors() const
{
    TArray<class AActor*> outActors;
    for (const UAQSQuestTargetComponent* targetComp : questTargets) {
        if (targetComp) {
            outActors.Add(targetComp->GetOwner());
        }
    }
    return outActors;
}



void UAQSQuestObjective::Internal_OnObjectiveStarted(UAQSObjectiveNode* inNodeOwner)
{
    nodeOwner = inNodeOwner;

    FillTargetsRef();

    OnObjectiveStarted();
}

void UAQSQuestObjective::FillTargetsRef()
{
    questTargets.Empty();
    const UAQSQuestManagerComponent* questMan = UAQSQuestFunctionLibrary::GetQuestManager(this);

    switch (TargetRefType) {
    case ETargetReferenceType::ETag:
        if (questMan) {
            questTargets = questMan->GetAllTargetsWithTags(ReferencedTargets);
        } else {
            UE_LOG(LogTemp, Error, TEXT("Add Quest Manager Component to your player controller! - AQSQuestObjective::Internal_OnObjectiveStarted"));
        }
        break;
    case ETargetReferenceType::ESoftRef:
        for (const TSoftObjectPtr<AActor>& actor : ReferencedActors) {
            if (actor) {
                UAQSQuestTargetComponent* targetComp = actor->FindComponentByClass<UAQSQuestTargetComponent>();
                if (targetComp) {
                    questTargets.Add(targetComp);
                } else {
                    UE_LOG(LogTemp, Error, TEXT("Add Quest Target Component to your target actors! - AQSQuestObjective::Internal_OnObjectiveStarted"));
                }
            }
        }
    }
}

void UAQSQuestObjective::OnObjectiveStarted_Implementation()
{
}

void UAQSQuestObjective::OnObjectiveCompleted_Implementation()
{
}

void UAQSQuestObjective::OnObjectiveUpdated_Implementation()
{
}
