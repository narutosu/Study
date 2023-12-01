// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AGSGraph.h"
#include <GameplayTagContainer.h>
#include "AQSQuestTargetComponent.h"
#include "AQSQuest.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStarted,  const FGameplayTag&, quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestEnded, const FGameplayTag&, quest, bool, bSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, const FGameplayTag&, quest);



UCLASS()
class ASCENTQUESTSYSTEM_API UAQSQuest : public UAGSGraph
{
	GENERATED_BODY()

	friend class UAQSQuestManagerComponent;

private:

	bool bIsTracked;

	bool StartQuest(class APlayerController* inController, TObjectPtr<UAQSQuestManagerComponent> inQuestManager, bool bActivateChildNodes = true);

	void SetQuestTracked(bool inTracked);

	bool CompleteBranchedObjective(const FGameplayTag& objectiveTag, const TArray<FName>& transitionFilters );

	bool CompleteObjective(const FGameplayTag& objectiveTag);

	TObjectPtr<class UAQSQuestManagerComponent> questManager;
protected:

	virtual bool ActivateNode(class UAGSGraphNode* node) override;


	/*Unique Tag for this quest, is a good practice to use a root GameplayTag for this, and
	child tags for objectives*/
	UPROPERTY(EditDefaultsOnly, Category = AQS)
	FGameplayTag QuestTag;

	/*Name for this quest, can be used for UI*/
	UPROPERTY(EditDefaultsOnly, Category = AQS)
	FText QuestName;

	/*A description for this objective, can be used for UI*/
	UPROPERTY(EditDefaultsOnly, Category = AQS)
	FText QuestDescription;

	/*An icon for this objective, can be used for UI*/
	UPROPERTY(EditDefaultsOnly, Category = AQS)
	class UTexture2D* QuestIcon;

public:

	UAQSQuest();

	void CompleteQuest(bool bSucceded);

	
	TObjectPtr<class UAQSQuestManagerComponent> GetQuestManager() const {
		return questManager;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE bool IsCurrentTrackedQuest() const {
		return bIsTracked;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE FGameplayTag GetQuestTag() const {
		return QuestTag;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE FText GetQuestName() const {
		return QuestName;
	}
	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE FText GetQuestDescription() const {
		return QuestDescription;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE UTexture2D* GetQuestIcon() const {
		return QuestIcon;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	bool HasActiveObjective(const FGameplayTag& objectiveTag) const;

	UFUNCTION(BlueprintPure, Category = AQS)
	UAQSObjectiveNode* GetActiveObjectiveNode(const FGameplayTag& objectiveTag) const;

	UFUNCTION(BlueprintPure, Category = AQS)
	UAQSQuestObjective* GetActiveObjective(const FGameplayTag& objectiveTag) const;
    
	UFUNCTION(BlueprintPure, Category = AQS)
	UAQSObjectiveNode* GetObjectiveNode(const FGameplayTag& objectiveTag) const;

	UFUNCTION(BlueprintPure, Category = AQS)
	TArray<UAQSQuestObjective*> GetAllActiveObjectives() const;

	UFUNCTION(BlueprintPure, Category = AQS)
	UAQSQuestObjective* GetObjectiveByTag(const FGameplayTag& objectiveTag) const;

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnQuestStarted OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnQuestEnded OnQuestEnded;

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveStarted OnObjectiveStarted;

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveCompleted OnObjectiveCompleted;

	/*Called every one of the  objectives is updated*/
	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveUpdated OnObjectiveUpdated;


	FORCEINLINE bool operator==(const FGameplayTag& OtherTag) const
	{
		return this->QuestTag == OtherTag;
	}

	FORCEINLINE bool operator!=(const FGameplayTag& OtherTag) const
	{
		return this->QuestTag != OtherTag;
	}
	FORCEINLINE bool operator==(const UAQSQuest* &Other) const
	{
		return QuestTag == Other->QuestTag;
	}

	FORCEINLINE bool operator!=(const UAQSQuest* &Other) const
	{
		return QuestTag != Other->QuestTag;
	}

};
