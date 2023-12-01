// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include "Graph/ASMStateMachine.h"
#include "ASMFSMComponent.generated.h"


UCLASS(BlueprintType, ClassGroup=(ATS), meta=(BlueprintSpawnableComponent) )
class ASCENTSTATEMACHINE_API UASMFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASMFSMComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*The actual FSM*/
	UPROPERTY(EditDefaultsOnly, Category = ASM)
	UASMStateMachine* FSM;

	/*Sets if this fsm should tick*/
	UPROPERTY(EditDefaultsOnly, Category = ASM)
	bool bCanFsmTick = false;

	/*Sets if this fsm should print debug info on screen*/
	UPROPERTY(EditDefaultsOnly, Category = ASM)
	bool bShouldDisplayDebugInfo = false;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PostInitProperties() override;
public:	

	/*Starts the actual FSM calling OnEnter on the StartNode State*/
	UFUNCTION(BlueprintCallable, Category = ASM)
	void StartFSM();

	/*Replicated version of StartFSM*/
	UFUNCTION(Server, Reliable, WithValidation,BlueprintCallable, Category = ASM)
	void SynchedStartFSM();

	/*Replicated version of StopFSM*/
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ASM)
	void SynchedStopFSM();

	/*Replicated version of TriggerTransition*/
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ASM)
	void SynchedTriggerTransition(const FGameplayTag& transition);

	/* Stops the actual FSM calling OnExit on current state.
	Triggers will be ignored until the next start */
	UFUNCTION(BlueprintCallable, Category = ASM)
	void StopFSM();

	/* Triggers the transition marked with the selected tag */
	UFUNCTION(BlueprintCallable, Category = ASM)
	void TriggerTransition(const FGameplayTag& transition);

	/* Triggers the transition marked with the selected tag on
	the owning client*/
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = ASM)
	void ClientTriggerTransition(const FGameplayTag& transition);

	/* Returns the name of the currently active state*/
	UFUNCTION(BlueprintPure, Category = ASM)
	FName GetCurrentStateName() const;
	
	UFUNCTION(BlueprintPure, Category = ASM)
	class UASMBaseFSMState* GetCurrentState() const;

	/* Returns whether the actual FSM is active*/
	UFUNCTION(BlueprintPure, Category = ASM)
	FORCEINLINE bool  IsFSMActive() const {
		return FSM ? FSM->IsActive() : false;
	}

	/* Returns whether this FSM can tick*/
	UFUNCTION(BlueprintPure, Category = ASM)
	FORCEINLINE bool  IsFsmTicking() const {
		return bCanFsmTick;
	}
		
	/*Activate and deactivate FSM Tick*/
	UFUNCTION(BlueprintCallable, Category = ASM)
	void SetFsmTickEnabled(bool bIsEnabled);

private:

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Internal_SynchedStart();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Internal_SynchedStop();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Internal_SynchedTriggerTransition(const FGameplayTag& transition);

	FGameplayTag pendingTransition;
};
