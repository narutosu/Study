// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/ADSDialogueResponseNode.h"
#include "Graph/ADSDialogue.h"
#include "Graph/ADSGraphNode.h"
#include <ADSDialoguePartecipantComponent.h>

bool UADSDialogueResponseNode::CanBeActivated(class APlayerController* inController)
{
	
	if (!GetDialogueParticipant()) {
		return false;
	}
	if (PartecipantTag != GetDialogueParticipant()->GetParticipantTag() && !bAllowedForEveryPlayer) {
		return false;
	}
	return Super::CanBeActivated(inController);
}

UADSDialogueResponseNode::UADSDialogueResponseNode()
{
#if WITH_EDITOR

	BackgroundColor = FLinearColor::White;
	ContextMenuName = FText::FromString("Response Button Node");
#endif
}

UADSDialogueNode* UADSDialogueResponseNode::ResponseSelected()
{
	UADSDialogue* dialogue = Cast< UADSDialogue>(GetGraph());
	if (dialogue && dialogue->ActivateNode(this))
	{
		return dialogue->MoveToNextNode();
	}
	return nullptr;
}
