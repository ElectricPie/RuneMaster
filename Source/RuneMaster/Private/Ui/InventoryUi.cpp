// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/InventoryUi.h"

#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "RuneMaster/Inventory.h"

void UInventoryUi::SetupInventory(UInventory* InventoryComponent, const FVector2D GridCanvasSize)
{
	if (InventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInventoryUI is missing InventoryGrid widget"));
		return;
	}
	if (InventoryComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to setup Inventory UI with null Inventory Component"));
		return;
	}

	// Get Inventory updates
	FOnInventoryChangedSignature::FDelegate Delegate;
	Delegate.BindUObject(this, &UInventoryUi::OnInventoryChanged);
	InventoryChangedHandle = InventoryComponent->RegisterToInventoryChangedEvent(Delegate);

	Inventory = InventoryComponent;
	const int32 InventorySlots = Inventory->GetSlotCount();
	// Dummy slot to set the width of other slot items if less than the column max
	if (InventorySlots < MaxColumns)
	{
		UUserWidget* BlankSlot = CreateWidget(this, InventorySlotWidget);
		UUniformGridSlot* EndGridSlot = InventoryGridPanel->AddChildToUniformGrid(BlankSlot, 0, MaxColumns - 1); 
		EndGridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		EndGridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		BlankSlot->SetVisibility(ESlateVisibility::Hidden);
	}
	
	// Create the slots
	int32 SlotCount = 0;
	int32 Columns = 1;
	Rows = 1;
	while (SlotCount < InventorySlots)
	{
		UUserWidget* NewSlot = CreateWidget(this, InventorySlotWidget);
		UUniformGridSlot* NewGridSlot = InventoryGridPanel->AddChildToUniformGrid(NewSlot, Rows - 1, Columns - 1);
		NewGridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		NewGridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		SlotCount++;

		// Move to the next row if the current one reach the column limit
		if (SlotCount % MaxColumns == 0)
		{
			Rows++;
			Columns = 1;
		}
		else
		{
			Columns++;
		}
	}

	// Set the size of height of the grid
	const float CellSize = GridCanvasSize.X / MaxColumns;
	GridSizeBox->SetHeightOverride(CellSize * Rows);
}

void UInventoryUi::OnInventoryChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Changed4"));
}
