// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AQSBaseNode.h"
#include "GameplayTagContainer.h"
#include "AQSFinishQuestNode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ASCENTQUESTSYSTEM_API UAQSFinishQuestNode : public UAQSBaseNode
{
	GENERATED_BODY()
	
public: 

	UAQSFinishQuestNode();

protected:

	bool bIsSuccessful;

	UPROPERTY(EditDefaultsOnly, Category = AQS)
	FGameplayTag NextQuestTag;

	virtual void ActivateNode() override;

};
