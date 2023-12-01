// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#include "Graph/ADSDialogue.h"
#include "ADSDialoguePartecipantComponent.h"
#include "ADSDialogueSubsystem.h"
#include "AGSGraphNode.h"
#include "Graph/ADSDialogueNode.h"
#include "Graph/ADSDialogueResponseNode.h"
#include "Graph/ADSGraphEdge.h"
#include "Graph/ADSGraphNode.h"
#include "Graph/ADSStartDialogueNode.h"
#include "UObject/UObjectIterator.h"
#include <Engine/GameInstance.h>
#include <Kismet/GameplayStatics.h>

UADSDialogue::UADSDialogue()
{
    NodeType = UADSGraphNode::StaticClass();
    EdgeType = UADSGraphEdge::StaticClass();
}

UAGSGraphNode* UADSDialogue::StartDialogue(class APlayerController* inController, const TArray<UADSDialoguePartecipantComponent*>& participants)
{
    controller = inController;
    partecipantsRef.Empty();
    for (const auto participant : participants) {
        partecipantsRef.Add(participant->GetParticipantTag(), participant);
    }

    if (partecipantsRef.Num() == 0) {
        UE_LOG(LogTemp, Error, TEXT("Missing Partecipants! - UADSDialogue::StartDialogue"));
        return nullptr;
    }

    for (UAGSGraphNode* root : RootNodes) {
        UADSStartDialogueNode* startNode = Cast<UADSStartDialogueNode>(root);
        if (startNode) {
            if (startNode->CanBeActivated(controller)) {
                currentDialogueStart = startNode;
                currentNode = startNode;
                OnDialogueStarted.Broadcast();
                ensure(ActivateNode(startNode));
                bIsStarted = true;
                return startNode;
            }
        }
    }

    return nullptr;
}

bool UADSDialogue::ActivateNode(class UAGSGraphNode* node)
{
    if (node && AllNodes.Contains(node)) {
        if (currentNode)
            currentNode->DeactivateNode();

        currentNode = Cast<UADSDialogueNode>(node);
        OnDialogueNodeActivated.Broadcast(currentNode);
    }
    return Super::ActivateNode(node);
}

TArray<UADSDialogueResponseNode*> UADSDialogue::GetAllButtonAnswersForCurrentNode() const
{
    UADSDialogueNode* currentDialogueNode = Cast<UADSDialogueNode>(currentNode);
    if (currentDialogueNode) {
        return currentDialogueNode->GetAllValidAnswers(controller);
    }

    return TArray<class UADSDialogueResponseNode*>();
}

class UADSDialogueNode* UADSDialogue::MoveToNextNode()
{
    if (currentNode) {
        for (UAGSGraphNode* child : currentNode->ChildrenNodes) {
            UADSDialogueNode* response = Cast<UADSDialogueNode>(child);
            if (response && response->CanBeActivated(controller)) {
                const UADSGraphEdge* edge = Cast<UADSGraphEdge>(currentNode->GetEdge(response));
                if (edge && edge->CanBeActivated(controller)) {
                    ensure(ActivateNode(response));
                    return response;
                }
            }
        }
        bIsStarted = false;

        if (currentDialogueStart) {
            currentDialogueStart->ExecuteEndingActions();
        }
        OnDialogueEnded.Broadcast();
    }

    return nullptr;
}

class UADSDialoguePartecipantComponent* UADSDialogue::FindPartecipant(FGameplayTag partecipantTag) const
{
    if (HasPartecipant(partecipantTag)) {
        return *(partecipantsRef.Find(partecipantTag));
    }

    return nullptr;
}
