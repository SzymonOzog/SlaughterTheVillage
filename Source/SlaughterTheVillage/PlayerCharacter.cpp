// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BaseMissile.h"
#include "Engine/World.h"
#include "Engine/DecalActor.h"
#include "GameFramework/PlayerController.h"
#include "BaseSpell.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Class.h"
#include "Explosion.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"

APlayerCharacter::APlayerCharacter()
{

}
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupMissileSpawnParams();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAimingSpell && SpellIndicator)
	{
		RotateToControllerYaw();
		RotateSpellIndicator(DeltaTime);
		SetSpellIndicatorLocation();
	}
}

void APlayerCharacter::RotateSpellIndicator(float DeltaTime)
{
	SpellIndicatorRotator.Yaw += 50.0f * DeltaTime;
	FRotator PlayerRollRotation = FRotator::ZeroRotator;
	PlayerRollRotation.Yaw = GetActorRotation().Yaw;
	SpellIndicator->SetActorRotation(SpellIndicatorRotator + PlayerRollRotation);
}

void APlayerCharacter::SetSpellIndicatorLocation() const
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	Controller->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
	float SpellRange = 	SpellClass->GetDefaultObject<ABaseSpell>()->GetCastingRange();
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * SpellRange;
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		SpellIndicator->SetActorLocation(Hit.Location);
	}
	else// Line trace from the end to the ground and draw the Spell Indicator there
	{
		FVector LineTraceEndToGround = LineTraceEnd;
		LineTraceEndToGround.Z -= SpellRange;
		if (GetWorld()->LineTraceSingleByChannel(Hit, LineTraceEnd, LineTraceEndToGround, ECollisionChannel::ECC_Visibility))
		{
			SpellIndicator->SetActorLocation(Hit.Location);				
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("NextMissile"), IE_Pressed, this, &APlayerCharacter::NextMissile);
	PlayerInputComponent->BindAction(TEXT("PreviousMissile"), IE_Pressed, this, &APlayerCharacter::PreviousMissile);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &APlayerCharacter::HideUnderground);
	PlayerInputComponent->BindAction(TEXT("CastSpell"), IE_Pressed, this, &APlayerCharacter::AimSpell);
	PlayerInputComponent->BindAction(TEXT("CastSpell"), IE_Released, this, &APlayerCharacter::CastSpell);
}

void APlayerCharacter::SetupUndergroundInput(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
}

void APlayerCharacter::Attack()
{
	Super::Attack();
	if (GetWorld()->GetTimeSeconds() - MissileLastCast < MissileCooldown)
	{
		return;
	}
	MissileLastCast = GetWorld()->GetTimeSeconds();
	MissileClass = MissileClasses[MissileIndex];
	if (MissileClass)
	{
		GetWorld()->SpawnActor<ABaseMissile>(MissileClass, CalculateMissileSpawnTransform(), MissileSpawnParams);
	}
}

void APlayerCharacter::SetupMissileSpawnParams()
{
	MissileSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MissileSpawnParams.bNoFail = true;
	MissileSpawnParams.Owner = this;
	MissileSpawnParams.Instigator = this;
}

void APlayerCharacter::PreviousMissile()
{
	MissileIndex--;
	if (MissileIndex < 0)
	{
		MissileIndex = MissileClasses.Num() - 1;
	}
}

void APlayerCharacter::NextMissile()
{
	MissileIndex++;
	if (MissileIndex >= MissileClasses.Num())
	{
		MissileIndex = 0;
	}
}

void APlayerCharacter::Dash()
{
	if (GetWorld()->GetTimeSeconds() - DashLastCast < DashCooldown)
	{
		return;
	}
	DashLastCast = GetWorld()->GetTimeSeconds();
	PushBack(GetActorRotation().Vector() * DashStrength);
}

void APlayerCharacter::RocketJump()
{
	if(!GetCharacterMovement()->IsFalling())
	{
		if(RocketJumpExplosionClass)
		{
			GetWorld()->SpawnActor<AExplosion>(RocketJumpExplosionClass, GetActorLocation(), GetActorRotation());
		}
		FVector JumpDirection = GetActorForwardVector() * RocketJumpForwardDistance;
		JumpDirection.Z = RocketJumpHeight;
	
		GetCharacterMovement()->AddImpulse(JumpDirection, true);
		JumpCurrentCount--;
		
	}
}

void APlayerCharacter::HideUnderground()
{
	SetActorHiddenInGame(true);
	FName CapsuleCollision = GetCapsuleComponent()->GetCollisionProfileName();
	FName MeshCollision = GetMesh()->GetCollisionProfileName();
	GetCapsuleComponent()->SetCollisionProfileName(FName("Ghost"));
	GetMesh()->SetCollisionProfileName(FName("Ghost"));
	InputComponent->ClearActionBindings();
	SetupUndergroundInput(InputComponent);

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle,
		[this, CapsuleCollision, MeshCollision]()
		{
			GetCapsuleComponent()->SetCollisionProfileName(CapsuleCollision);
			GetMesh()->SetCollisionProfileName(MeshCollision);
			SetActorHiddenInGame(false);
			SetupPlayerInputComponent(InputComponent);
		}, HideUndergroundLength, false);
}

void APlayerCharacter::AimSpell()
{
	if (SpellIndicatorClass)
	{
		bIsAimingSpell = true;
		SpellIndicator = GetWorld()->SpawnActor<ADecalActor>(SpellIndicatorClass, GetActorLocation(), FRotator::ZeroRotator);
		SpellIndicatorRotator = SpellIndicator->GetActorRotation();
	}
}

void APlayerCharacter::CastSpell()
{
	bIsAimingSpell = false;
	if (SpellIndicator)
	{
		GetWorld()->SpawnActor<ABaseSpell>(SpellClass, SpellIndicator->GetActorLocation(), GetActorRotation());
		SpellIndicator->Destroy();
	}
	 
}

FTransform APlayerCharacter::CalculateMissileSpawnTransform() const
{
	FTransform MissileSpawnTransform;
	FRotator ControllerRotation = GetControlRotation();
	MissileSpawnTransform.SetLocation(ControllerRotation.Vector() * MissileSpawnDistance + GetActorLocation());
	MissileSpawnTransform.SetRotation(ControllerRotation.Quaternion());
	return MissileSpawnTransform;
}

