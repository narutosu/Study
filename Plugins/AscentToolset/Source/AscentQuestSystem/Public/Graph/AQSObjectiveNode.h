// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AQSBaseNode.h"
#include <GameplayTagContainer.h>
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "AQSObjectiveNode.generated.h"

struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveUpdated, const FGameplayTag&, objective, const FGameplayTag&, quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveStarted, const FGameplayTag&, objective, const FGameplayTag&, quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveCompleted, const FGameplayTag&, objective, const FGameplayTag&, quest);
/**
 * 
 */
UENUM(BlueprintType)
enum class EQuestUpdateType : uint8
{
	EStarted   UMETA(DisplayName = "Objective Started"),
	EUpdated  UMETA(DisplayName = "Objective Updated"),
	ECompleted UMETA(DisplayName = "Objective Completed"),
    EInterrupted UMETA(DisplayName = "Quest Interrupted")
};

UCLASS()
class ASCENTQUESTSYSTEM_API UAQSObjectiveNode : public UAQSBaseNode
{
	GENERATED_BODY()


	friend class UAQSQuest;

public:

	virtual void ActivateNode() override;

	virtual void DeactivateNode() override;


	UAQSObjectiveNode();

public:

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveStarted OnObjectiveStarted;

	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveCompleted OnObjectiveCompleted;

	/*Called every one of the  objectives is updated*/
	UPROPERTY(BlueprintAssignable, Category = AQS)
	FOnObjectiveUpdated OnObjectiveUpdated;
	
	bool TryToComplete();

	UFUNCTION(BlueprintPure, Category = AQS)
	TArray< class UAQSQuestTargetComponent*>  GetObjectiveTargets() const;

	UFUNCTION(BlueprintPure, Category = AQS)
	int32 GetCurrentRepetitions() const {
		return CurrentRepetitions;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE int32 GetQuestRepetitions() const {
		return Repetitions;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE bool IsTracked() const{
		return bIsTracked;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	 FGameplayTag GetObjectiveTag() const;

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE bool IsObjectiveCompleted() const {
		return bIsCompleted;
	}

	UFUNCTION(BlueprintPure, Category = AQS)
	FORCEINLINE class UAQSQuestObjective* GetQuestObjective() const {
		return Objective;
	}

	void SetCurrentRepetitions(const int32 reps) {
		CurrentRepetitions = reps;
		UpdateReferences(EQuestUpdateType::EUpdated);
	}

#if WITH_EDITOR


	virtual FText GetNodeTitle() const ;

#endif
protected: 

	/*A set of condition that must be verified to complete this objective*/
	UPROPERTY(EditDefaultsOnly, Instanced, Category = AQS)
	TObjectPtr<class UAQSQuestObjective> Objective;

	/*A set of condition that must be verified to complete this objective*/
	UPROPERTY(EditDefaultsOnly, Instanced, Category = AQS)
	TArray<class UAGSCondition*> CompleteConditions;

	/*How many time CompleteObjective must be called with
	this tag to complete this objective*/
	UPROPERTY(EditDefaultsOnly, Category = AQS)
	int32 Repetitions = 1;

	int32 CurrentRepetitions = 0;

private: 

	void SetIsTracked(bool inTracked);

	void UpdateReferences( EQuestUpdateType updateType);

	bool bIsTracked = false;
};
