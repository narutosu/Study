// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AGSGraphNode.h"
#include "ASMStateNode.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTSTATEMACHINE_API UASMStateNode : public UAGSGraphNode
{
	GENERATED_BODY()

public:

	virtual void ActivateNode() override;

	virtual void DeactivateNode() override;

	void OnTransition(const class UASMBaseFSMState* previousState);


#if WITH_EDITOR


	virtual FText GetNodeTitle() const {
		if (GetStateName() != NAME_None) {
			return FText::FromName(GetStateName());
		}
		
		return FText::FromString("Set State Name");
	}

#endif

	FName GetStateName() const{
		return StateName;
	}

	class UASMBaseFSMState* GetState() const {
		return State;
	}

	UASMStateNode();
protected: 

	UPROPERTY(EditDefaultsOnly,  Category = ASM)
	FName StateName;
	
	UPROPERTY(EditDefaultsOnly, Instanced, Category = ASM)
	class UASMBaseFSMState* State;
	
};
