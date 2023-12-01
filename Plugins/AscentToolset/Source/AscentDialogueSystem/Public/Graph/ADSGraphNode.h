// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AGSGraphNode.h"
#include <GameplayTagContainer.h>
#include "ADSGraphNode.generated.h"

/**
 * 
 */
UCLASS(abstract)
class ASCENTDIALOGUESYSTEM_API UADSGraphNode : public UAGSGraphNode
{
	GENERATED_BODY()

		friend class UADSDialogue;
	
public: 

	UFUNCTION(BlueprintPure, Category = ADS)
	class UADSDialoguePartecipantComponent* GetDialogueParticipant() const;


	UFUNCTION(BlueprintPure, Category = ADS)
	class USoundCue* GetSoundToPlay() const {
		return SoundToPlay;
	}

	UFUNCTION(BlueprintPure, Category = ADS)
	bool IsLocalPlayerPartecipant() const;

	UFUNCTION(BlueprintCallable, Category = ADS)
	virtual bool CanBeActivated(class APlayerController* inController);

	UFUNCTION(BlueprintPure, Category = ADS)
	FORCEINLINE FText GetDialogueText() const { return Text; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;

#endif
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ADS)
	FGameplayTag PartecipantTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = ADS)
	TArray<class UAGSAction*> ActivationActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ADS)
	class USoundCue* SoundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ADS)
    class UAnimMontage* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ADS)
	FText Text;

	virtual void ActivateNode() override;

	virtual void DeactivateNode() override;

	UPROPERTY()
	class APlayerController* controller;

	FText ContextMenuName;

	UPROPERTY()
	class UADSDialoguePartecipantComponent* partecipant;

	UPROPERTY()
	class UAudioComponent* audioPlayer;

	class UADSDialoguePartecipantComponent* GatherPartecipant() const;
};
