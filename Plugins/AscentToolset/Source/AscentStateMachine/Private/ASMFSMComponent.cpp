// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "ASMFSMComponent.h"
#include "Net/UnrealNetwork.h"
#include "ASMBaseFSMState.h"


// Sets default values for this component's properties
UASMFSMComponent::UASMFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UASMFSMComponent::BeginPlay()
{
	Super::BeginPlay();

}

// void UASMFSMComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// 
// }

void UASMFSMComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FSM && FSM->IsActive()) {
		FSM->DispatchTick(DeltaTime);
		if (pendingTransition != FGameplayTag()) {
			FSM->TriggerTransition(pendingTransition);
			pendingTransition = FGameplayTag();
		}
	}
}

void UASMFSMComponent::PostInitProperties()
{
	Super::PostInitProperties();

	SetComponentTickEnabled(true);
	SetIsReplicatedByDefault(true);
}

void UASMFSMComponent::StartFSM()
{
	if (FSM) {
		FSM->StartFSM(GetOwner(), bShouldDisplayDebugInfo);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid State Machine - UASMFSMComponent::StartFSM"));
	}
}


void UASMFSMComponent::StopFSM()
{
	if (FSM) {
		FSM->StopFSM();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid State Machine - UASMFSMComponent::StopFSM"));
	}
}

void UASMFSMComponent::TriggerTransition(const FGameplayTag& transition)
{
	pendingTransition = transition;

}

void UASMFSMComponent::ClientTriggerTransition_Implementation(const FGameplayTag& transition)
{
	TriggerTransition(transition);
}

bool UASMFSMComponent::ClientTriggerTransition_Validate(const FGameplayTag& transition)
{
	return true;
}

FName UASMFSMComponent::GetCurrentStateName() const
{
	if (FSM) {
		return FSM->GetCurrentStateName();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid State Machine - UASMFSMComponent::GetCurrentStateName"));
	}
	return NAME_None;
}

UASMBaseFSMState* UASMFSMComponent::GetCurrentState() const
{
	if (FSM) {
		return FSM->GetCurrentState();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid State Machine - UASMFSMComponent::GetCurrentState"));
	}
	return nullptr;
}

void UASMFSMComponent::SetFsmTickEnabled(bool bIsEnabled)
{
	bCanFsmTick = bIsEnabled;
	
}



void UASMFSMComponent::SynchedStopFSM_Implementation()
{
	Internal_SynchedStop();
}

bool UASMFSMComponent::SynchedStopFSM_Validate()
{
	return true;
}

void UASMFSMComponent::SynchedStartFSM_Implementation()
{
	Internal_SynchedStart();
}

bool UASMFSMComponent::SynchedStartFSM_Validate()
{
	return true;
}

void UASMFSMComponent::SynchedTriggerTransition_Implementation(const FGameplayTag& transition)
{
	Internal_SynchedTriggerTransition(transition);
}

bool UASMFSMComponent::SynchedTriggerTransition_Validate(const FGameplayTag& transition)
{
	return true;
}




void UASMFSMComponent::Internal_SynchedTriggerTransition_Implementation(const FGameplayTag& transition)
{
	TriggerTransition(transition);
}

bool UASMFSMComponent::Internal_SynchedTriggerTransition_Validate(const FGameplayTag& transition)
{
	return true;
}

void UASMFSMComponent::Internal_SynchedStart_Implementation()
{
	StartFSM();
}

bool UASMFSMComponent::Internal_SynchedStart_Validate()
{
	return true;
}

void UASMFSMComponent::Internal_SynchedStop_Implementation()
{
	StopFSM();
}

bool UASMFSMComponent::Internal_SynchedStop_Validate()
{
	return true;
}

