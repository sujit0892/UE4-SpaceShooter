// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"


void UGameWidget::onLoad()
{
	const FName TextBlockName = FName(TEXT("GameTextBlock"));
	if (ScoreText == nullptr)
	{
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::SetScore(int score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("score : ")) + FString::FromInt(score)));
	}
}

void UGameWidget::OnGameOver(int score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("score : ")) + FString::FromInt(score) + TEXT("\nPress R to Restart")));
	}
}

