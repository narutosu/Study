// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/AQSStartQuestNode.h"

UAQSStartQuestNode::UAQSStartQuestNode()
{
#if WITH_EDITOR
	BackgroundColor = FLinearColor::Blue;
	#endif
	bIsCompleted = true;
}


