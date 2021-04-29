// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0.0f;
	CanAttack = true;
	AttackStarted = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.0f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &APlayerCharacter::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &APlayerCharacter::Pitch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::OnAttack);


}

void APlayerCharacter::MoveForward(float Amount)
{
	if (Controller && Amount) {
		IsWalking = true;
		FVector fwd = GetActorForwardVector();
		AddMovementInput(fwd, Amount);
	}

	if (Amount == 0)
		IsWalking = false;


}

void APlayerCharacter::MoveRight(float Amount)
{
	if (Controller && Amount) {
		FVector right = GetActorRightVector();
		AddMovementInput(right, Amount);
	}
}

void APlayerCharacter::Yaw(float Amount)
{
	AddControllerYawInput(200.0f * Amount * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::Pitch(float Amount)
{
	AddControllerPitchInput(200.0f * Amount * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::OnAttack()
{
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
