// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris_UE4GameModeBase.h"
#include "Board.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ATetris_UE4GameModeBase::ATetris_UE4GameModeBase()
{
    DefaultPawnClass = ABoard::StaticClass();
}

void ATetris_UE4GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    //Create 2 Board
    for (int i = 0; i < 1 ; i++)
    {
        ABoard* SpawnedBoard = GetWorld()->SpawnActor<ABoard>(ABoard::StaticClass());
        if (SpawnedBoard)
        {
            //If the Spawn succeeds, set the Spawned inventory to the local one and log the success string
            Board = SpawnedBoard;
            GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s ha sido creado"), *Board->GetName()));
        }
    }
        
    
    for(TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Find camera: %s"), *(it->GetFName().ToString()));
        if(it->GetFName() == TEXT("BoardCamera"))
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            PC->SetViewTargetWithBlend(*it, 0.5);
            break;
        }
    }

    
}
