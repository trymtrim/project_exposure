//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XmlParser.h"

class PROJECTEXPOSURE_API Highscore
{
public:
	Highscore ();
	~Highscore ();

	void AddScore (FString name, int score);
};
