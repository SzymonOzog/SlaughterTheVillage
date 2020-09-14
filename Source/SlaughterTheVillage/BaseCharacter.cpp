// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "SlaughterTheVillageGameModeBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	SetupCharacterMovement();
	PlayerReach = CalculatePlayerReach();
}

void ABaseCharacter::SetupCharacterMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = this->AirControl;
	GetCharacterMovement()->MaxWalkSpeed *= Speed;
	GetCharacterMovement()->JumpZVelocity = JumpHeight;
}

float ABaseCharacter::CalculatePlayerReach()
{
	FVector UpperArmLocation = GetMesh()->GetSocketLocation(TEXT("upperarm_r"));
	FVector WeaponLocation = GetMesh()->GetSocketLocation(TEXT("WeaponSocket"));
	float Reach = FVector::Dist(UpperArmLocation, WeaponLocation);
	return Reach;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageApplied, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *GetName(), CurrentHealth)
		if (IsPlayerDead())
		{
			HandleDeath();
			//Notify the game mode that this has died
			Cast<ASlaughterTheVillageGameModeBase>(GetWorld()->GetAuthGameMode())->CharacterKilled(this);
		}
	return DamageAmount;
}


void ABaseCharacter::HandleDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetachFromControllerPendingDestroy();
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ABaseCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ABaseCharacter::StopAttacking);

}

void ABaseCharacter::MoveForward(float AxisValue)
{
	if (Controller && AxisValue)
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector& Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue * Speed);
	}
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	if (Controller && AxisValue)
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector& Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue * Speed);
	}
}

void ABaseCharacter::Attack()
{
	//attacks are made with respect to controller rotation so
	//we are rotating to prevent attacking with our back
	RotateToControllerYaw();
	bIsAttacking = true;
	UE_LOG(LogTemp, Warning, TEXT("Atttacked"))

}

void ABaseCharacter::PushBack(FVector PushDirection)
{
	PushDirection *= GetMesh()->GetMass();
	//Lift the character to eliminate friction
	PushDirection.Z = 100.0f;
	GetController()->StopMovement();
	GetCharacterMovement()->AddImpulse(PushDirection, true);
}

void ABaseCharacter::HitSpikes()
{
	SpikeHitTime = GetWorld()->GetTimeSeconds();
}

void ABaseCharacter::RotateToControllerYaw()
{
	FRotator playerRotation = GetActorRotation();
	FRotator controllerRotation = GetControlRotation();
	playerRotation.Yaw = controllerRotation.Yaw;
	SetActorRotation(playerRotation);
}

void ABaseCharacter::StopAttacking()
{
	bIsAttacking = false;
}

