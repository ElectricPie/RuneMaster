// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerInventoryUi.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UPlayerInventoryUi::FillGrid(const int32 InventorySlots)
{
	if (InventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInventoryUI is missing InventoryGrid widget"));
		return;
	}

	// Dummy slot to set the width of other slot items
	if (InventorySlots < SlotColumns)
	{
		UUserWidget* BlankSlot = CreateWidget(this, InventorySlotWidget);
		UUniformGridSlot* EndGridSlot = InventoryGridPanel->AddChildToUniformGrid(BlankSlot, 0, SlotColumns - 1); 
		EndGridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		EndGridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		BlankSlot->SetVisibility(ESlateVisibility::Hidden);
	}

	int32 SlotCount = 0;
	int32 Rows = 0;
	int32 Columns = 0;
	while (SlotCount < InventorySlots)
	{
		UUserWidget* NewSlot = CreateWidget(this, InventorySlotWidget);
		UUniformGridSlot* NewGridSlot = InventoryGridPanel->AddChildToUniformGrid(NewSlot, Rows, Columns);
		NewGridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		NewGridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		SlotCount++;

		// Move to the next row if the current one reach the column limit
		if (SlotCount % SlotColumns == 0)
		{
			Rows++;
			Columns = 0;
		}
		else
		{
			Columns++;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Total: %d, Rows: %d"), SlotCount, Rows);
}
