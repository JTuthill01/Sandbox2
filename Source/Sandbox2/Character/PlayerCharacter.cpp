#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
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

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &APlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerCharacter::StopJump);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::MoveUp(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorUpVector(), Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::TurnRate(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Interact()
{
	
}

void APlayerCharacter::StartJump() { Jump(); }

void APlayerCharacter::StopJump() { StopJumping(); }

