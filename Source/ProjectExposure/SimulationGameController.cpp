//Fill out your copyright notice in the Description page of Project Settings.

#include "SimulationGameController.h"
#include "Engine/World.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

//Sets default values
ASimulationGameController::ASimulationGameController ()
{
 	//Set this pawn to call Tick () every frame.
	PrimaryActorTick.bCanEverTick = true;

	/*CountdownText = CreateDefaultSubobject <UTextRenderComponent> (TEXT ("CountdownNumber"));
    CountdownText->SetHorizontalAlignment (EHTA_Center);
    CountdownText->SetWorldSize (150.0f);
	CountdownText->SetText ("YOOO");*/
	//CountdownText->SetText (FString::FromInt(FMath::Max(CountdownTime, 0)));
}

//Called when the game starts or when spawned
void ASimulationGameController::BeginPlay ()
{
	Super::BeginPlay ();
}

//Called every frame
void ASimulationGameController::Tick (float DeltaTime)
{
	Super::Tick (DeltaTime);
}

void ASimulationGameController::SpawnUnit (int index)
{
	UWorld* world = GetWorld ();
	
	if (world)
	{
		if (_controlledUnit)
			_controlledUnit->Destroy ();

		//Define the unit to spawn
		TSubclassOf <APlaceableUnit> controlledUnit;
		
		switch (index)
		{
		case 0:
			controlledUnit = _nuclearReactorPrefab;
			break;
		case 1:
			controlledUnit = _windmillPrefab;
			break;
		case 2:
			controlledUnit = _oilRigPrefab;
			break;
		}
		
		FActorSpawnParameters spawnParams;
		//spawnParams.Owner = this;
		
		FVector spawnPosition = GetActorLocation ();
		FRotator rotator = FVector (0.0f, 0.0f, 0.0f).Rotation ();

		//Spawn the unit
		_controlledUnit = world->SpawnActor <APlaceableUnit> (controlledUnit, spawnPosition, rotator, spawnParams);
		_controlledUnit->SetMaterials (normalMaterial, collideMaterial);
	}
}

void ASimulationGameController::PlaceUnit ()
{
	//If the player currently controls a unit, place it
	if (_controlledUnit)
	{
		if (_controlledUnit->PlaceUnit ())
		{
			_controlledUnit = nullptr;

			//When the unit is placed, start simulation
			StartSimulation ();
		}
	}
}

void ASimulationGameController::StartSimulation ()
{
	//Disable UI, the rest is handled by the UI widget blueprint
	showUI = false;
	showSimulationUI = true;
	
	//Temp
	print ("Let the simulation begin!");
}

void ASimulationGameController::StopSimulation ()
{
	showSimulationUI = false;

	//If it's time for a new minigame, enter that, otherwise start new turn
	if (_currentTurn == 1 || _currentTurn == 4 || _currentTurn == 7)
		EnterMiniGame ();
	else
		StartNewTurn ();
}

void ASimulationGameController::EnterMiniGame ()
{
	//Temp
	print ("Let the minigame begin!");
	_miniGameActive = true;

	//After minigame is finished, exit it
	//ExitMiniGame ();
}

void ASimulationGameController::ExitMiniGame ()
{
	//Temp
	print ("Exiting minigame...");
	_miniGameActive = false;

	//After exiting minigame, start new turn
	StartNewTurn ();
}

void ASimulationGameController::StartNewTurn ()
{
	_currentTurn++;
	CHAR* yo = "W";
	IntToChar (_currentTurn, yo);
	currentTurnText = "Turn " + FString::FromInt (_currentTurn);
	
	//Enable UI, the rest is handled by the UI widget blueprint
	showUI = true;
}

void ASimulationGameController::OnSpacePress ()
{
	if (showSimulationUI)
		StopSimulation ();
	else if (_miniGameActive)
		ExitMiniGame ();
}

//Called to bind functionality to input
void ASimulationGameController::SetupPlayerInputComponent (UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent (PlayerInputComponent);

	PlayerInputComponent->BindAction ("MouseClick", IE_Pressed, this, &ASimulationGameController::PlaceUnit);
	PlayerInputComponent->BindAction ("Space", IE_Pressed, this, &ASimulationGameController::OnSpacePress);
}
