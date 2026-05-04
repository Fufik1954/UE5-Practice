// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/AsteroidSpawner.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArena"));
	
	MinSpawnDelay = 0.5f;
	MaxSpawnDelay = 2.5f;
}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	StartSpawnTimer();
	
}

FVector AAsteroidSpawner::GetRandomSpawnPoint()
{
	const FVector SpawnOrigin = SpawnArea->Bounds.Origin;
	const FVector SpawnLimits = SpawnArea->Bounds.BoxExtent;
	
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnLimits);
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroidSpawner::SpawnActors()
{
	if(!ActorToSpawn || !GetWorld())
	{
		return;
	}
	
	// Создаем структуру
	FActorSpawnParameters Parameters;
	// Владелец актора (наш спавнер)
	Parameters.Owner = this;
	// Задает инифиализатора спавна (вернет объект, который вызвал спавн)
	Parameters.Instigator = GetInstigator();
	// Обработка столкновений 
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	// Спавн объекта: спавн объекта типа APickUpBase, Позиция из метода, поворот рандом, передаем параметры
	APickUpBase* SpawnerActor = GetWorld()->SpawnActor<APickUpBase>(ActorToSpawn, GetRandomSpawnPoint(),
		UKismetMathLibrary::RandomRotator(), Parameters);
	
	StartSpawnTimer();
}

void AAsteroidSpawner::StartSpawnTimer()
{
	// Случайное время задержки
	RandomSpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
	
	// Создание таймера: менеджер таймера, настраиваем таймер: где хранится, кто вызывает, сам метод для вызова, задержка, сработает 1 раз
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this,
		&AAsteroidSpawner::SpawnActors, RandomSpawnDelay, false);
}

