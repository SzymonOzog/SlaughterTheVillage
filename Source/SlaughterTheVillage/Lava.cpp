// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"
#include "BaseCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ALava::ALava()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ALava::OnLavaBeginOverlap);
	
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALava::OnLavaBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor overlapped lava"))
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DealLavaDamage"), Character);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, true, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("TimerSet"))	
	}

}

void ALava::DealLavaDamage(ABaseCharacter* Character)
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* OverlappedActor : OverlappingActors)
	{
		if (Character == OverlappedActor)
		{
			Character->TakeDamage(DamagePerSecond, FDamageEvent(), nullptr, this);
			return;
		}
	}
	GetWorldTimerManager().ClearTimer(TimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Timer Cleared"))
}

