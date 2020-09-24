// Fill out your copyright notice in the Description page of Project Settings.


#include "PushComponent.h"
#include "GameFramework/Actor.h"
UPushComponent::UPushComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPushComponent::SetDestination(FVector _Destination)
{
	Destination = _Destination;
}

void UPushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector CurrentLocation = GetOwner()->GetTargetLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, Destination, DeltaTime, 10.0f);
	GetOwner()->SetActorLocation(NewLocation, false);
	if (CurrentLocation == Destination)
		DestroyComponent();
}

void UPushComponent::BeginPlay()
{
	Super::BeginPlay();
}