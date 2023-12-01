// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Graph/ADSGraphNode.h"
#include "ADSDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTDIALOGUESYSTEM_API UADSDialogueNode : public UADSGraphNode
{
	GENERATED_BODY()

protected:



public: 

	UADSDialogueNode();

	UFUNCTION(BlueprintCallable, Category = ADS)
	TArray<class UADSDialogueResponseNode*>  GetAllValidAnswers( APlayerController* inController);


};
