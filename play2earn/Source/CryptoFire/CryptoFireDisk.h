// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CryptoFireDisk.generated.h"

USTRUCT(BlueprintType)
struct FTokenIds {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TSet<FString> Tokens;
};

USTRUCT(BlueprintType)
struct FTokenIdAmounts {
  GENERATED_BODY()

  // tokenid, tokenamount
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TMap<FString, FString> Tokens;
};

UCLASS()
class CRYPTOFIRE_API ACryptoFireDisk : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ACryptoFireDisk();

protected:
  void read(FString);
  void write(FString);
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // erc 721: tokenid: adress
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  FString erc721Contract;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TArray<FString> erc721Tokens;

  // key: account address, data: tokenid
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TMap<FString, FTokenIds> erc721Holders;

  // erc 1155:  tokenid:(address:amount))
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  FString erc1155Contract;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TArray<FString> erc1155Tokens;

  // key: account address, data: tokenid
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CryptoFireGame")
  TMap<FString, FTokenIdAmounts> erc1155Holders;

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "IntiailizeDisk", Keywords = "Disk"),
            Category = "CryptoFireGame")
  void InitializeDisk(FString &result, int Erc721Start, int Erc721End,
                      int Erc1155Start, int Erc1155End);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "LoadDisk", Keywords = "Disk"),
            Category = "CryptoFireGame")
  void LoadDisk(FString &result);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "SaveDisk", Keywords = "Disk"),
            Category = "CryptoFireGame")
  void SaveDisk(FString &result);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "GiveErc721Token", Keywords = "Disk"),
            Category = "CryptoFireGame")
  void GiveErc721Token(FString AccountAddress, FString TokenId);

  UFUNCTION(BlueprintCallable,
            meta = (DisplayName = "GiveErc1155Token", Keywords = "Disk"),
            Category = "CryptoFireGame")
  void GiveErc1155Token(FString AccountAddress, FString TokenId,
                        FString Amount);
};
