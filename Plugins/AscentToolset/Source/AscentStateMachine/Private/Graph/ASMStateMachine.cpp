// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "Graph/ASMStateMachine.h"
#include "Graph/ASMStartFSMNode.h"
#include "Graph/ASMStateNode.h"
#include "Graph/ASMTransition.h"
#include "ASMBaseFSMState.h"
#include "Engine/Engine.h"

bool UASMStateMachine::ActivateNode(class UAGSGraphNode *node) {
  currentState = Cast<UASMStateNode>(node);

  return Super::ActivateNode(node);
}

void UASMStateMachine::DispatchTick(float DeltaTime)
{
    if (currentState) {
        UASMBaseFSMState* state = currentState->GetState();
        if (state) {
            state->OnUpdate(DeltaTime);
        }
    }
}

UASMStateMachine::UASMStateMachine() {
  NodeType = UASMStateNode::StaticClass();
  EdgeType = UASMTransition::StaticClass();
  Enabled = EFSMState::NotStarted;
}

void UASMStateMachine::StartFSM(class AActor* inOwner, const bool bPrintDebugInfo /*= false*/)
{

	fsmOwner = inOwner;
	if (IsActive()) {
		UE_LOG(LogTemp, Error,
			TEXT("FSM Already Started - UASMStateMachine::StartFSM"));
	}

    bPrintDebug = bPrintDebugInfo;
	Internal_Start();
}

void UASMStateMachine::Internal_Start()
{
	for (UAGSGraphNode* root : RootNodes) {
		UASMStartFSMNode* startNode = Cast<UASMStartFSMNode>(root);
		if (startNode) {
			ActivateNode(startNode);
			Enabled = EFSMState::Started;
			return;
		}
	}
}

bool UASMStateMachine::TriggerTransition(const FGameplayTag &transition) {
  if (!IsActive()) {
    UE_LOG(LogTemp, Error,
           TEXT("FSM Not Started - UASMStateMachine::TriggerTransition"));
    return false;
  }

  for (UAGSGraphNode *node : GetActiveNodes()) {
    UASMStateNode *fsmNode = Cast<UASMStateNode>(node);
    if (fsmNode == currentState) {

      for (auto edge : fsmNode->Edges) {
        UASMTransition *edgeTransition = Cast<UASMTransition>(edge.Value);
        if (edgeTransition &&
            edgeTransition->GetTransitionTag() == transition &&
            edgeTransition->VerifyTransitionConditions()) {
          DeactivateNode(fsmNode);
          UASMStateNode *stateNode = Cast<UASMStateNode>(edge.Key);
          if (stateNode) {
            stateNode->OnTransition(fsmNode->GetState());
            if (bPrintDebug) {
				GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow,
					FString::Printf(TEXT("Current State is: %s"), *stateNode->GetStateName().ToString()));
            }
            return ActivateNode(stateNode);
          } 
        }
      }

    }
  }
  return false;
}

void UASMStateMachine::StopFSM() {
  if (IsActive()) {
    for (UAGSGraphNode *node : GetActiveNodes()) {
      DeactivateNode(node);
    }
    Enabled = EFSMState::NotStarted;
  } else {
    UE_LOG(LogTemp, Error, TEXT("FSM Not Started - UASMStateMachine::StopFSM"));
  }
}

FName UASMStateMachine::GetCurrentStateName() const {
  if (currentState) {
    return currentState->GetStateName();
  }
  return NAME_None;
}

class UASMBaseFSMState* UASMStateMachine::GetCurrentState() const
{
	if (currentState) {
		return currentState->GetState();
	}
	return nullptr;
}
