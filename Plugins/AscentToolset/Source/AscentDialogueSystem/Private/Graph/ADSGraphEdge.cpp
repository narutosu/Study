// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "Graph/ADSGraphEdge.h"
#include "AGSCondition.h"

bool UADSGraphEdge::CanBeActivated( APlayerController* controller) const 
{
	for (UAGSCondition* cond : ActivationConditions)
	{
		if (!cond->Verify(controller))
			return false;
	}
	return true;
}
