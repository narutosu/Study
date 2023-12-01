// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "ADSDialogueNode.h"
#include "ADSStartDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTDIALOGUESYSTEM_API UADSStartDialogueNode : public UADSDialogueNode
{
	GENERATED_BODY()

public: 

	UADSStartDialogueNode();

	virtual bool CanBeActivated(APlayerController* controller)  override ;

	void ExecuteEndingActions();

// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ADS)
// 	TArray<FGameplayTag> PartecipantsTag;

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = ADS)
	TArray<class UAGSCondition*> ActivationConditions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = ADS)
	TArray<class UAGSAction*> DialogueEndedActions;



};
