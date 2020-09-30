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
    if(!bIsAtDestination)
    {
        FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Destination, DeltaTime, Speed);
        SetActorLocation(NewLocation);
        if(NewLocation == Destination)
        {
            bIsAtDestination = true;
        }
    }
    else
    {
        FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), DisappearDestination, DeltaTime, DisappearSpeed);
        SetActorLocation(NewLocation);
        if(NewLocation == DisappearDestination)
        {
            Destroy();
        }
    }
}

void ASpellWave::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ASpellWave::OnWaveBeginOverlap);
    Destination = GetActorLocation() + GetActorRotation().Vector() * TravelDistance;
    DisappearDestination = Destination;
    DisappearDestination.Z -= 1000.0f;
}

void ASpellWave::OnWaveBeginOverlap(AActor* OverpalledActor, AActor* OtherActor)
{
    if(ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
    {
        FVector PushDirection = OtherActor->GetActorLocation() - GetActorLocation();
        PushDirection.Normalize();
        //Make the push direction go more forward instead of to the sides
        PushDirection += GetActorForwardVector();
        PushDirection.Z = 0.0f;
        Character->PushBack(PushDirection * PushBackStrength);
    }
}
