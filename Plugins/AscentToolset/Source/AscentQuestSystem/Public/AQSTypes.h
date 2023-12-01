// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#pragma once

#include "AQSQuestObjective.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Graph/AQSQuest.h"
#include "UObject/NoExportTypes.h"

#include "AQSTypes.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FAQSQuestData : public FTableRowBase {
    GENERATED_BODY()

    FAQSQuestData()
    {
        Quest = nullptr;
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AQS)
    class UAQSQuest* Quest;
};

USTRUCT(BlueprintType)
struct FAQSObjectiveRecord {
    GENERATED_BODY()

public:
    FAQSObjectiveRecord()
    {
        CurrentRepetitions = 0;
    };

    FAQSObjectiveRecord(const UAQSQuestObjective* objective)
    {
        Objective = objective->GetObjectiveTag();
        CurrentRepetitions = objective->GetCurrentRepetitions();
    }

    UPROPERTY(BlueprintReadOnly, SaveGame, Category = AQS)
    FGameplayTag Objective;

    UPROPERTY(BlueprintReadOnly, SaveGame, Category = AQS)
    int32 CurrentRepetitions;

    FORCEINLINE bool operator==(const FAQSObjectiveRecord& Other) const
    {
        return this->Objective == Other.Objective;
    }

    FORCEINLINE bool operator!=(const FAQSObjectiveRecord& Other) const
    {
        return this->Objective != Other.Objective;
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return this->Objective == Other;
    }

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return this->Objective != Other;
    }
};

USTRUCT(BlueprintType)
struct FAQSQuestRecord {
    GENERATED_BODY()

public:
    FAQSQuestRecord(const class UAQSQuest* quest)
    {
        Quest = quest->GetQuestTag();
        for (const auto obj : quest->GetAllActiveObjectives()) {
            if (obj) {
                Objectives.Add(FAQSObjectiveRecord(obj));
            }
        }
    }

    FAQSQuestRecord() {};

    UPROPERTY(BlueprintReadOnly, SaveGame, Category = AQS)
    FGameplayTag Quest;

    UPROPERTY(BlueprintReadOnly, SaveGame, Category = AQS)
    TArray<FAQSObjectiveRecord> Objectives;

    FORCEINLINE bool operator==(const FAQSQuestRecord& Other) const
    {
        return this->Quest == Other.Quest;
    }

    FORCEINLINE bool operator!=(const FAQSQuestRecord& Other) const
    {
        return this->Quest != Other.Quest;
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return this->Quest == Other;
    }

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return this->Quest != Other;
    }
};

USTRUCT(BlueprintType)
struct FAQSObjectiveInfo {
    GENERATED_BODY()

public:
    FAQSObjectiveInfo()
    {
        CurrentRepetitions = 0;
        TotalRepetitions = 1;
    };

    FAQSObjectiveInfo(const UAQSQuestObjective* objective, const FAQSObjectiveRecord& objectiveRecord)
    {
        ObjectiveTag = objectiveRecord.Objective;
        CurrentRepetitions = objectiveRecord.CurrentRepetitions;
        ObjectiveName = objective->GetObjectiveName();
        ObjectiveDescription = objective->GetDescription();
        TotalRepetitions = objective->GetRepetitions();
    };

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FGameplayTag ObjectiveTag;

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FText ObjectiveName;

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FText ObjectiveDescription;

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    int32 CurrentRepetitions;

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    int32 TotalRepetitions;
};

USTRUCT(BlueprintType)
struct FAQSQuestInfo {
    GENERATED_BODY()

public:
    FAQSQuestInfo() {};

    FAQSQuestInfo(const UAQSQuest* quest, const FAQSQuestRecord& questRecord)
    {
        QuestTag = quest->GetQuestTag();
        QuestName = quest->GetQuestName();
        QuestDescription = quest->GetQuestDescription();
        QuestIcon = quest->GetQuestIcon();
        Objectives = questRecord.Objectives;
    };

    /*Unique Tag for this quest, is a good practice to use a root GameplayTag for this, and
    child tags for objectives*/
    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FGameplayTag QuestTag;

    /*Name for this quest, can be used for UI*/
    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FText QuestName;

    /*A description for this objective, can be used for UI*/
    UPROPERTY(BlueprintReadOnly, Category = AQS)
    FText QuestDescription;

    /*An icon for this objective, can be used for UI*/
    UPROPERTY(BlueprintReadOnly, Category = AQS)
    class UTexture2D* QuestIcon;

    UPROPERTY(BlueprintReadOnly, Category = AQS)
    TArray<FAQSObjectiveRecord> Objectives;
};

UCLASS()
class ASCENTQUESTSYSTEM_API UAQSTypes : public UObject {
    GENERATED_BODY()
};
