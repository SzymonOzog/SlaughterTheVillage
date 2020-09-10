// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "Explosion.h"
#include "Engine/World.h"
// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AExplosiveBarrel::OnBarrelOverlap);
}

void AExplosiveBarrel::OnBarrelOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<AExplosion>(OtherActor))
	{
		if (ExplosionClass)
		{
			Destroy();
			GetWorld()->SpawnActor<AExplosion>(ExplosionClass, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}



