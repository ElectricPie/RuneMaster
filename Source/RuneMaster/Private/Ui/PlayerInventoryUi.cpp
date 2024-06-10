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
