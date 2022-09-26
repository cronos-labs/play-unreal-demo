// Fill out your copyright notice in the Description page of Project Settings.

#include "CryptoFireDisk.h"
#include "Misc/FileHelper.h"

// Sets default values
ACryptoFireDisk::ACryptoFireDisk() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk"));

  erc721Contract = "0x";
  erc721Tokens.Empty();

  erc1155Contract = "0x";
  erc1155Tokens.Empty();
}

// Called when the game starts or when spawned
void ACryptoFireDisk::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void ACryptoFireDisk::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ACryptoFireDisk::read(FString filenmae) {
  FString json;
  FFileHelper::LoadFileToString(json, *filenmae);
  UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk read %s"), *json);

  TSharedPtr<FJsonObject> JsonObject;
  TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(json);
  if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
    UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk read %s"), *json);
  }

  erc721Contract = JsonObject->GetStringField(TEXT("Erc721Contract"));
  erc721Tokens.Empty();
  {
    TArray<TSharedPtr<FJsonValue>> Array =
        JsonObject->GetArrayField(TEXT("Erc721NftItems"));
    for (int i = 0; i < Array.Num(); i++) {
      erc721Tokens.Add(Array[i]->AsString());
    }
  }

  erc721Holders.Empty();
  {
    TSharedPtr<FJsonObject> Object =
        JsonObject->GetObjectField(TEXT("Erc721Holders"));
    for (auto &Pair : Object->Values) {
      FString accountAddress = Pair.Key;
      TArray<TSharedPtr<FJsonValue>> Array = Pair.Value->AsArray();
      FTokenIds tokenIds;
      for (int i = 0; i < Array.Num(); i++) {
        tokenIds.Tokens.Add(Array[i]->AsString());
      }
      erc721Holders.Add(accountAddress, tokenIds);
    }
  }

  erc1155Contract = JsonObject->GetStringField(TEXT("Erc1155Contract"));
  erc1155Tokens.Empty();
  {
    TArray<TSharedPtr<FJsonValue>> Array =
        JsonObject->GetArrayField(TEXT("Erc1155NftItems"));
    for (int i = 0; i < Array.Num(); i++) {
      erc1155Tokens.Add(Array[i]->AsString());
    }
  }

  erc1155Holders.Empty();
  {
    TSharedPtr<FJsonObject> Object =
        JsonObject->GetObjectField(TEXT("Erc1155Holders"));
    for (auto &Pair : Object->Values) {
      FString accountAddress = Pair.Key;
      TSharedPtr<FJsonObject> MyObject = Pair.Value->AsObject();
      FTokenIdAmounts tokenIdAmounts;
      for (auto &Pair2 : MyObject->Values) {
        FString tokenId = Pair2.Key;
        FString amount = Pair2.Value->AsString();
        tokenIdAmounts.Tokens.Add(tokenId, amount);
      }

      erc1155Holders.Add(accountAddress, tokenIdAmounts);
    }
  }
}
void ACryptoFireDisk::write(FString filename) {

  TSharedPtr<FJsonObject> myjson = MakeShareable(new FJsonObject);
  myjson->SetStringField(TEXT("Erc721Contract"), erc721Contract);
  {
    TArray<TSharedPtr<FJsonValue>> myarray;
    for (int i = 0; i < erc721Tokens.Num(); i++) {
      myarray.Add(MakeShareable(new FJsonValueString(erc721Tokens[i])));
    }
    myjson->SetArrayField(TEXT("Erc721NftItems"), myarray);
  }

  {
    TSharedPtr<FJsonObject> mymap = MakeShareable(new FJsonObject);
    for (auto &it : erc721Holders) {
      TArray<TSharedPtr<FJsonValue>> myarray;
      for (auto &Elem : it.Value.Tokens) {
        myarray.Add(MakeShareable(new FJsonValueString(Elem)));
      }
      mymap->SetArrayField(it.Key, myarray);
    }
    myjson->SetObjectField(TEXT("Erc721Holders"), mymap);
  }

  myjson->SetStringField(TEXT("Erc1155Contract"), erc1155Contract);
  {
    TArray<TSharedPtr<FJsonValue>> myarray;
    for (int i = 0; i < erc1155Tokens.Num(); i++) {
      myarray.Add(MakeShareable(new FJsonValueString(erc1155Tokens[i])));
    }
    myjson->SetArrayField(TEXT("Erc1155NftItems"), myarray);
  }

  {
    TSharedPtr<FJsonObject> mymap = MakeShareable(new FJsonObject);
    for (auto &it : erc1155Holders) {
      TSharedPtr<FJsonObject> myobject = MakeShareable(new FJsonObject);
      for (auto &Elem : it.Value.Tokens) {
        FString tokenid = Elem.Key;
        FString tokenamount = Elem.Value;
        myobject->SetStringField(tokenid, tokenamount);
      }
      mymap->SetObjectField(it.Key, myobject);
    }
    myjson->SetObjectField(TEXT("Erc1155Holders"), mymap);
  }

  FString json;
  TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&json);
  FJsonSerializer::Serialize(myjson.ToSharedRef(), Writer);
  FString path = FPaths::ProjectConfigDir() + filename;
  FFileHelper::SaveStringToFile(json, *path);
}

FString makeRandom() {
  FString result;
  for (int i = 0; i < 40; i++) {
    int r = FMath::RandRange(0, 15);
    result += FString::Printf(TEXT("%x"), r);
  }
  return result;
}
void ACryptoFireDisk::InitializeDisk(FString &result, int Erc721Start,
                                     int Erc721End, int Erc1155Start,
                                     int Erc1155End) {
  const FString filename = TEXT("test.json");
  UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk InitializeWallet"));
  FString path = FPaths::ProjectConfigDir() + filename;
  if (FPaths::FileExists(path)) {
    read(path);

  } else { // initialize
    int randomCount = 5;
    for (int i = Erc721Start; i < Erc721End; i++) {
      erc721Tokens.Add(FString::Printf(TEXT("%d"), i));
    }

    for (int i = Erc1155Start; i < Erc1155End; i++) {
      erc1155Tokens.Add(FString::Printf(TEXT("%d"), i));
    }

    for (int i = 0; i < randomCount; i++) {
      FString random = makeRandom();
      FTokenIds tokenIds;
      for (int j = 0; j < 2; j++) {
        tokenIds.Tokens.Add(FString::Printf(TEXT("%d"), j));
      }
      erc721Holders.Add(FString::Printf(TEXT("0x%s"), *random), tokenIds);
    }

    for (int i = 0; i < 10; i++) {
      erc1155Tokens.Add(FString::Printf(TEXT("%d"), i));
    }
    for (int i = 0; i < randomCount; i++) {
      FString random = makeRandom();
      FTokenIdAmounts tokenIdAmounts;
      for (int j = 0; j < 3; j++) {
        tokenIdAmounts.Tokens.Add(FString::Printf(TEXT("%d"), j),
                                  FString::Printf(TEXT("%d"), 100));
      }
      erc1155Holders.Add(FString::Printf(TEXT("0x%s"), *random),
                         tokenIdAmounts);
    }
  }
  write(filename);
  result = "C++ CryptoFireDisk InitializeWallet OK";
}

void ACryptoFireDisk::LoadDisk(FString &result) {
  const FString filename = TEXT("test.json");
  UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk LoadDisk"));
  FString path = FPaths::ProjectConfigDir() + filename;
  if (FPaths::FileExists(path)) {
    read(path);
    result = "C++ CryptoFireDisk Load OK";
  } else {
    result = "C++ CryptoFireDisk Load NG";
  }
}

void ACryptoFireDisk::SaveDisk(FString &result) {
  const FString filename = TEXT("test.json");
  UE_LOG(LogTemp, Log, TEXT("C++ CryptoFireDisk SaveDisk"));
  write(filename);
  result = "C++ CryptoFireDisk Save OK";
}

void ACryptoFireDisk::GiveErc721Token(FString AccountAddress, FString TokenId) {
  if (erc721Holders.Contains(AccountAddress)) {
    FTokenIds &tokenIds = erc721Holders[AccountAddress];
    tokenIds.Tokens.Add(TokenId);
  } else {
    FTokenIds tokenIds;
    tokenIds.Tokens.Add(TokenId);
    erc721Holders.Add(AccountAddress, tokenIds);
  }
}

void ACryptoFireDisk::GiveErc1155Token(FString AccountAddress, FString TokenId,
                                       FString Amount) {
  if (erc1155Holders.Contains(AccountAddress)) {
    FTokenIdAmounts &tokenIdAmounts = erc1155Holders[AccountAddress];
    tokenIdAmounts.Tokens.Add(TokenId, Amount);
  } else {
    FTokenIdAmounts tokenIdAmounts;
    tokenIdAmounts.Tokens.Add(TokenId, Amount);
    erc1155Holders.Add(AccountAddress, tokenIdAmounts);
  }
}