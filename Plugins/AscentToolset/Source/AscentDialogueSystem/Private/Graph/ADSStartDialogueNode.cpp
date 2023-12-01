// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/ADSStartDialogueNode.h"
#include "AGSCondition.h"
#include "AGSAction.h"


UADSStartDialogueNode::UADSStartDialogueNode()
{
#if WITH_EDITOR
	BackgroundColor = FLinearColor::Green;
	ContextMenuName = FText::FromString("Start Dialogue Node");
#endif
}

bool UADSStartDialogueNode::CanBeActivated( APlayerController* inController)  
{
	for (UAGSCondition* cond : ActivationConditions)
	{
		if (cond && !cond->VerifyForNode(inController, this))
			return false;
	}
	return true;
}

void UADSStartDialogueNode::ExecuteEndingActions()
{
	for (UAGSAction* action : DialogueEndedActions)
	{
		if (action)
			action->Execute(controller, this);
	}
}
