// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"
#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ASpikes::ASpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
	
	OnActorBeginOverlap.AddDynamic(this, &ASpikes::OnSpikesOverlap);
}

// Called when the game starts or when spawned
void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikes::OnSpikesOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		Character->TakeDamage(Damage, FDamageEvent(), nullptr, this);
	}
}

