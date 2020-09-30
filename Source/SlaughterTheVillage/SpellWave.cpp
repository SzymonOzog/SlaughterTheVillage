// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellWave.h"

#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

ASpellWave::ASpellWave()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ASpellWave::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Destination, DeltaTime, Speed);
    SetActorLocation(NewLocation);
}

void ASpellWave::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ASpellWave::OnWaveBeginOverlap);
    Destination = GetActorLocation() + GetActorRotation().Vector() * TravelDistance;
}

void ASpellWave::OnWaveBeginOverlap(AActor* OverpalledActor, AActor* OtherActor)
{
    if(ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
    {
        FVector ActorDirection = OtherActor->GetActorLocation() - GetActorLocation();
        ActorDirection.Normalize();
        Character->PushBack(ActorDirection * PushBackStrength);
    }
}
