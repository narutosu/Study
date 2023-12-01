// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved.

#include "Graph/ADSGraphNode.h"
#include "ADSDialoguePartecipantComponent.h"
#include "AGSAction.h"
#include "AGSCondition.h"
#include "AGSGraphNode.h"
#include "Graph/ADSDialogue.h"
#include "Graph/ADSDialogueResponseNode.h"
#include "Graph/ADSGraphEdge.h"
#include <Animation/AnimInstance.h>
#include <Animation/AnimMontage.h>
#include <Animation/AnimSequence.h>
#include <Components/AudioComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

void UADSGraphNode::ActivateNode()
{
    Super::ActivateNode();

    partecipant = GatherPartecipant();

    for (UAGSAction* action : ActivationActions) {
        if (action) {
            action->Execute(UGameplayStatics::GetPlayerController(this, 0), this);
        }
    }

    if (!partecipant) {
        UE_LOG(LogTemp, Error, TEXT("Invalid Partecipant!"));
        return;
    }

    USkeletalMeshComponent* skeletal = partecipant->GetOwnerMesh();

    if (skeletal) {
        partecipant->PlayAnimationOnCharacterOwner(Animation);
        audioPlayer = UGameplayStatics::SpawnSoundAttached(SoundToPlay, skeletal, partecipant->GetVoiceSpawningSocketName());
    }
}

void UADSGraphNode::DeactivateNode()
{
    Super::DeactivateNode();
    if (audioPlayer) {
        audioPlayer->Stop();
    }
}

class UADSDialoguePartecipantComponent* UADSGraphNode::GatherPartecipant() const
{
    const UADSDialogue* dialogue = Cast<UADSDialogue>(GetGraph());

    if (!dialogue) {
        return nullptr;
    }
    return dialogue->FindPartecipant(PartecipantTag);
}

class UADSDialoguePartecipantComponent* UADSGraphNode::GetDialogueParticipant() const
{
    return partecipant ? partecipant : GatherPartecipant();
}

bool UADSGraphNode::IsLocalPlayerPartecipant() const
{

    if (controller && GetDialogueParticipant()) {
        return GetDialogueParticipant()->GetOwner() == controller->GetPawn();
    }
    return false;
}

bool UADSGraphNode::CanBeActivated(APlayerController* inController)
{
    return true;
}

#if WITH_EDITOR

FText UADSGraphNode::GetNodeTitle() const
{
    if (PartecipantTag != FGameplayTag()) {
        return FText::FromName(PartecipantTag.GetTagName());
    }
    return FText::FromString("Set Participant Tag!");
}

#endif
/*
FText UADSGraphNode::GetNodeTitle() const
{
        FString left, right;

        PartecipantTag.GetTagName().ToString().Split(".", &left, &right);
        FString nodeS = right + ": " + Text.ToString();

        FText ToBeChopped = Text;

        if (nodeS.Len() > 15)
        {
                FString final = nodeS.Left(25) + "...";
                ToBeChopped = FText::FromString(final);
        }

        return ToBeChopped;
}*/
