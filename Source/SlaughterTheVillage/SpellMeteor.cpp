// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellMeteor.h"
#include "Components/StaticMeshComponent.h"
ASpellMeteor::ASpellMeteor()
{
    PrimaryActorTick.bCanEverTick = true;
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));
}

void ASpellMeteor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector MeshLocation = FMath::VInterpTo(Mesh->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, 1.0f);
    Mesh->SetRelativeLocation(MeshLocation);
}

void ASpellMeteor::BeginPlay()
{
    Super::BeginPlay();
}
