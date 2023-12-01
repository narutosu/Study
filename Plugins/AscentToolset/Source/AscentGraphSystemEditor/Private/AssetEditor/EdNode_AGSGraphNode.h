// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "AGSGraphNode.h"
#include "EdNode_AGSGraphNode.generated.h"

class UEdNode_AGSGraphEdge;
class UEdGraph_AGSGraph;
class SEdNode_AGSGraphNode;

UCLASS(MinimalAPI)
class UEdNode_AGSGraphNode : public UEdGraphNode {
	GENERATED_BODY()

public:
	UEdNode_AGSGraphNode();
	virtual ~UEdNode_AGSGraphNode();

	UPROPERTY(VisibleAnywhere, Instanced, Category = AGS)
	UAGSGraphNode* AGSGraphNode;

	void SetAGSGraphNode(UAGSGraphNode* InNode);
	UEdGraph_AGSGraph* GetAGSGraphEdGraph();

	SEdNode_AGSGraphNode* SEdNode;

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	virtual FLinearColor GetBackgroundColor() const;
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif

};
