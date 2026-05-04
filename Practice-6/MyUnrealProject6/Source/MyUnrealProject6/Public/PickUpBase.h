// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class MYUNREALPROJECT6_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpBase();
	
	// Указывает, что поле видно в редакторе, можно менять через Blueprint, категория (где появится компонент)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* PickUpMeshComponent;
	
	// Метод - чистая функция (не меняет состояние объекта)
	UFUNCTION(BlueprintPure, Category="PickUp")
	bool IsPickPpActive() const;
	
	// Метод доступный для вызова из Blueprint
	UFUNCTION(BlueprintCallable, Category="PickUp")
	void SetPickUpActive(bool state);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
