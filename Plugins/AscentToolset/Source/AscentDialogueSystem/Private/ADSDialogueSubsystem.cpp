// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#include "ADSDialogueSubsystem.h"
#include "ADSDialoguePartecipantComponent.h"

void UADSDialogueSubsystem::RegisterParticipant(UADSDialoguePartecipantComponent* participant)
{
	if (participant) {
		Participants.Add(participant->GetParticipantTag(), participant);
	}

}

void UADSDialogueSubsystem::UnregisterParticipant(const FGameplayTag& participant)
{
	if (Participants.Contains(participant)) {
		Participants.Remove(participant);
	}
}

UADSDialoguePartecipantComponent* UADSDialogueSubsystem::FindParticipant(const FGameplayTag& participant) const
{
	if (Participants.Contains(participant)) {
		return *(Participants.Find(participant));
	}
	return nullptr;
}
