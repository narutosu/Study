// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AQSFinishQuestNode.h"
#include "AQSQuestFailedNode.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTQUESTSYSTEM_API UAQSQuestFailedNode : public UAQSFinishQuestNode
{
	GENERATED_BODY()

public:

	


protected: 

	UAQSQuestFailedNode();

#if WITH_EDITOR


	virtual FText GetNodeTitle() const {
		return FText::FromString("Quest Failed");
	}

#endif
};
