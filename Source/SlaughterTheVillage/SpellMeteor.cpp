// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellMeteor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
ASpellMeteor::ASpellMeteor()
{
    PrimaryActorTick.bCanEverTick = true;
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, SpawnHeight));
    Mesh->SetWorldScale3D(FVector(Size));
    
}

void ASpellMeteor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector MeshLocation = FMath::VInterpConstantTo(Mesh->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, Speed);
    Mesh->SetRelativeLocation(MeshLocation, true);
}

void ASpellMeteor::BeginPlay()
{
    Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ASpellMeteor::OnMeteorHit);
}

void ASpellMeteor::OnMeteorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if(ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
    {
        Character->TakeDamage(Damage, FDamageEvent(), nullptr, this);
    }
    Destroy();
}
