//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlaceableUnit.h"
#include "CameraMovement.h"
#include "MinigameCartController.h"
#include "MinigameDrill/MinigameDrillController.h"
#include "MinigameSolar/MinigameSolarController.h"
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
	void StartClickDelay ();
	void EndGame (bool gameWon); //True if won, false if lost

	bool CanContinue ();

	//For blueprints
	UFUNCTION (BlueprintCallable, Category = "ButtonPress")
	void SpawnUnit (int index);

	UPROPERTY (BlueprintReadOnly)
	FString currentTurnText = "Year 1";

	UFUNCTION (BlueprintImplementableEvent, Category = "Feedback")
	void UpdateCycle ();

	//Debug
	UFUNCTION (BlueprintImplementableEvent, Category = "Reset")
	void ResetLevel ();
	UFUNCTION (BlueprintImplementableEvent, Category = "ReloadGame")
	void ReloadGame ();

protected:
	virtual void BeginPlay () override;

private:
	void PlaceUnit ();
	void RemoveUnit ();
	void ClearRemovable ();
	void ActivateOutlines (bool status);
	void StartSimulation ();
	void StopSimulation ();
	void EnterMiniGame ();
	void StartNewTurn ();
	void FadeIn (float delayTime, float fadeTime);
	void FadeOut (float delayTime, float fadeTime);
	void UpdateFading (float deltaTime);
	void UpdateMovingToMine (bool toMine);
	void CheckAFK ();

	UPROPERTY () TArray <APlaceableUnit*> _powerPlants;

	float fadeInTimer;
	float fadeOutTimer;
	float fadeInDelay;
	float fadeOutDelay;
	bool fadingIn = false;
	bool fadingOut = false;
	
	float _simulationTimer = 0.0f;
	bool _playSimulation = false;
	bool _simulationRunning = false;
	bool _placing = false;

	float _startPanelTimer = 0.0f;
	bool _startPanelEnabled = true;

	bool _mineGamePlayed = false;
	bool _windGamePlayed = false;
	bool _oilGamePlayed = false;

	UPROPERTY () AActor* _messageBox;
	UPROPERTY () AActor* _removeBox;
	AActor* _removePP;

	bool _waitingForResponse = false;

	//For minigame panels
	bool _panelDelay = false;
	float _panelTimer = 0.0f;
	float _panelDelayTime = 2.0f;

	//UI
	bool _uiEnabled = false;

	//Variables for camera movement to mine minigame
	bool _movingToMine = false;
	bool _movingFromMine = false;
	int _currentPositionIndex = 0;
	TArray <FVector> _mineCameraPositions {FVector (-1800, 6191, 615), FVector (-5700, 7014, -948)};
	TArray <FVector> _mineCameraRotations {FVector (0, -10, 173), FVector (0, 0, 170)};
	
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
	UPROPERTY (EditAnywhere)
	AMinigameSolarController* _windmillPawn;
	UPROPERTY (EditAnywhere)
	FVector _windmillPosition;
	UPROPERTY (EditAnywhere)
	FVector _windmillRotation;

	UPROPERTY (EditAnywhere)
	float _simulationTime;

	UPROPERTY (EditAnywhere)
	TSubclassOf <AActor> _optionalMinigameMessage;
	UPROPERTY (EditAnywhere)
	TSubclassOf <AActor> _removeMessage;

	//Debug
	UPROPERTY (EditAnywhere) bool _miniGamesOn = true;
};
