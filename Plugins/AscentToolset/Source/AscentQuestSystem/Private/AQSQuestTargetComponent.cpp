// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#include "AQSQuestTargetComponent.h"
#include "AQSQuestFunctionLibrary.h"
#include "AQSQuestManagerComponent.h"
#include "Graph/AQSObjectiveNode.h"
#include "Net/UnrealNetwork.h"

#include "UObject/CoreNet.h"

// Sets default values for this component's properties
UAQSQuestTargetComponent::UAQSQuestTargetComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);

    // ...
}

void UAQSQuestTargetComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UAQSQuestTargetComponent, bIsCurrentlyTargetOfObjective);
    DOREPLIFETIME(UAQSQuestTargetComponent, currentlyTargetingObjective);
    DOREPLIFETIME(UAQSQuestTargetComponent, currentlyTargetingQuest);
}

void UAQSQuestTargetComponent::CompleteObjective(FGameplayTag objectiveToComplete)
{
    UAQSQuestManagerComponent* questManager = UAQSQuestFunctionLibrary::GetQuestManager(this);
    if (questManager) {
        questManager->ServerCompleteObjective(objectiveToComplete);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Add Quest Manager Component to your player controller! - UAQSQuestTargetComponent::CompleteObjective"));
        return;
    }
}

void UAQSQuestTargetComponent::CompleteReferencingObjetive_Implementation()
{
    UAQSQuestManagerComponent* questManager = UAQSQuestFunctionLibrary::GetQuestManager(this);
    if (questManager && bIsCurrentlyTargetOfObjective) {
        questManager->ServerCompleteObjective(currentlyTargetingObjective);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Add Quest Manager Component to your player controller! - UAQSQuestTargetComponent::CompleteObjective"));
        return;
    }
}

void UAQSQuestTargetComponent::CompleteBranchedObjective(FGameplayTag objectiveToComplete, const TArray<FName>& transitionFilters)
{
    UAQSQuestManagerComponent* questManager = UAQSQuestFunctionLibrary::GetQuestManager(this);
    if (questManager) {
        questManager->ServerCompleteBranchedObjective(objectiveToComplete, transitionFilters);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Add Quest Manager Component to your player controller! - UAQSQuestTargetComponent::CompleteBranchedObjective"));
        return;
    }
}

void UAQSQuestTargetComponent::OnObjectiveStarted_Implementation(const FGameplayTag& objectiveTag, const FGameplayTag& questTag)
{
}

void UAQSQuestTargetComponent::OnObjectiveCompleted_Implementation(const FGameplayTag& objectiveTag, const FGameplayTag& questTag)
{
}

void UAQSQuestTargetComponent::OnObjectiveUpdated_Implementation(const FGameplayTag& objectiveTag, const FGameplayTag& questTag)
{
}

void UAQSQuestTargetComponent::DispatchObjectiveUpdated(const FGameplayTag& objectiveTag, const FGameplayTag& questTag, EQuestUpdateType objectiveUpdate)
{
    switch (objectiveUpdate) {
    case EQuestUpdateType::EStarted:
        bIsCurrentlyTargetOfObjective = true;
        currentlyTargetingQuest = questTag;
        currentlyTargetingObjective = objectiveTag;
        OnReferencingObjectiveStarted.Broadcast(objectiveTag, questTag);
        OnObjectiveStarted(objectiveTag, questTag);
        break;
    case EQuestUpdateType::EUpdated:
        OnReferencingObjectiveUpdated.Broadcast(objectiveTag, questTag);
        OnObjectiveUpdated(objectiveTag, questTag);
        break;
    case EQuestUpdateType::ECompleted:
        bIsCurrentlyTargetOfObjective = false;
        currentlyTargetingQuest = FGameplayTag();
        currentlyTargetingObjective = FGameplayTag();
        OnReferencingObjectiveCompleted.Broadcast(objectiveTag, questTag);
        OnObjectiveCompleted(objectiveTag, questTag);
        break;
    }
}

// Called when the game starts
void UAQSQuestTargetComponent::BeginPlay()
{
    Super::BeginPlay();
    UAQSQuestManagerComponent* questMan = UAQSQuestFunctionLibrary::GetQuestManager(this);
    if (questMan && TargetTag != FGameplayTag()) {
        questMan->RegisterTarget(this);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Add Quest Manager Component to your player controller! - UAQSQuestTargetComponent::BeginPlay"));
    }
}
