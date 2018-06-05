//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlaceableUnit.h"
#include "CameraMovement.h"
#include "MinigameCartController.h"
#include "MinigameDrill/MinigameDrillController.h"
#include "Simulation/Simulation.h"
#include "UIController.h"
#include "SimulationGameController.generated.h"

UCLASS()
class PROJECTEXPOSURE_API ASimulationGameController : public APawn
{
	GENERATED_BODY ()

public:
	ASimulationGameController ();

	//Called every frame
	virtual void Tick (float DeltaTime) override;

	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent (class UInputComponent* PlayerInputComponent) override;

	void ExitMiniGame ();

	//For blueprints
	UFUNCTION (BlueprintCallable, Category = "ButtonPress")
	void SpawnUnit (int index);

	UPROPERTY (BlueprintReadOnly)
	bool gameStarted = false;

	UPROPERTY (BlueprintReadOnly)
	FString currentTurnText = "Turn 1";

	UFUNCTION (BlueprintImplementableEvent, Category = "Feedback")
	void UpdateCycle ();

protected:
	virtual void BeginPlay () override;

private:
	void PlaceUnit ();
	void StartSimulation ();
	void StopSimulation ();
	void EnterMiniGame ();
	void StartNewTurn ();
	void FadeIn (float delayTime, float fadeTime);
	void FadeOut (float delayTime, float fadeTime);
	void UpdateFading (float deltaTime);
	void UpdateMovingToMine ();
	void CheckAFK ();

	float fadeInTimer;
	float fadeOutTimer;
	float fadeInDelay;
	float fadeOutDelay;
	bool fadingIn = false;
	bool fadingOut = false;
	
	bool _simulationRunning = false;
	bool _placing = false;

	//Variables for camera movement to mine minigame
	bool _movingToMine = false;
	int _currentPositionIndex = 0;
	TArray <FVector> _mineCameraPositions {FVector (-1514, 5644, 483)};
	TArray <FVector> _mineCameraRotations {FVector (0, 0, 161)};

	//Inputs
	void OnSpacePress ();
	void OnMouseClick ();
	void OnMouseRelease ();

	//Default camera position and rotation
	FVector _defaultPosition;
	FVector _defaultRotation;

	CameraMovement* _cameraMovement;

	//Currently controlled unit
	APlaceableUnit* _controlledUnit = nullptr;
	
	//Simulation setup
	int _maxTurns = 9;
	int _currentTurn = 1;

	//Currently active minigame
	int _miniGameActive = 0; //0 = nothing, 1 = nuclear, 2 = windmill, 3 = oilrig
	bool _miniGameIsActive = false;

	//Actual simulation controller
	UPROPERTY (EditAnywhere)
	ASimulation* _simulation;

	//UI controller
	UPROPERTY (EditAnywhere)
	AUIController* _uiController;

	//Prefabs
	UPROPERTY (EditAnywhere)
	TSubclassOf <AActor> _nuclearReactorPrefab;
	UPROPERTY (EditAnywhere)
	TSubclassOf <AActor> _windmillPrefab;
	UPROPERTY (EditAnywhere)
	TSubclassOf <AActor> _oilRigPrefab;

	//Minigame pawns, position and rotation
	//Mine game
	UPROPERTY (EditAnywhere)
	AMinigameCartController* _minePawn;
	UPROPERTY (EditAnywhere)
	FVector _minePosition;
	UPROPERTY (EditAnywhere)
	FVector _mineRotation;

	//Drill game
	UPROPERTY (EditAnywhere)
	AMinigameDrillController* _drillPawn;
	UPROPERTY (EditAnywhere)
	FVector _drillPosition;
	UPROPERTY (EditAnywhere)
	FVector _drillRotation;

	//Windmill game
	//
	//
	UPROPERTY (EditAnywhere)
	FVector _windmillPosition;
	UPROPERTY (EditAnywhere)
	FVector _windmillRotation;

	UPROPERTY (EditAnywhere)
	AActor* _mine;

	//Temp
	UPROPERTY (EditAnywhere) bool _miniGamesOn = true;
};
