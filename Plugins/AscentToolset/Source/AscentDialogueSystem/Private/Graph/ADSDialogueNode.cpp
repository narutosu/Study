// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/ADSDialogueNode.h"
#include "Graph/ADSDialogueResponseNode.h"
#include <GameFramework/PlayerController.h>
#include "Graph/ADSGraphEdge.h"
#include "AGSGraphNode.h"

UADSDialogueNode::UADSDialogueNode()
{
#if WITH_EDITOR
	BackgroundColor = FLinearColor::Black;
	ContextMenuName = FText::FromString("Dialogue Node");
#endif
}

TArray<UADSDialogueResponseNode*>  UADSDialogueNode::GetAllValidAnswers( APlayerController* inController)
{
	TArray<UADSDialogueResponseNode*>  outResponses;
	for ( UAGSGraphNode* child : ChildrenNodes)
	{
		UADSDialogueResponseNode* response = Cast<UADSDialogueResponseNode>(child);
		if (response && response->CanBeActivated(inController))
		{
			UADSGraphEdge* edge = Cast< UADSGraphEdge>(GetEdge(response));
			if (edge && edge->CanBeActivated(inController)) {
				outResponses.Add(response);
			}

		}
	}
	return outResponses;
}