// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AQSBaseNode.h"
#include "AQSStartQuestNode.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTQUESTSYSTEM_API UAQSStartQuestNode : public UAQSBaseNode
{
	GENERATED_BODY()
	
public: 

	UAQSStartQuestNode();

#if WITH_EDITOR


	virtual FText GetNodeTitle() const {
		return FText::FromString("Quest Start");
	}

#endif

};
