// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/CallDynamicContract.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"

// Called when the game starts or when spawned
void ACallDynamicContract::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ACallDynamicContract::OnCallDynamicContractBeginOverlap);

    // connect member function to callback variable
    CallDynamicContractCallback.BindDynamic(
        this, &ACallDynamicContract::OnCallDynamicContract);
}

void ACallDynamicContract::Setup() {
    const char *contractId = std::getenv("MYCONTRACT721");
    std::string usercontractId = "";
    if (contractId != nullptr) {
        usercontractId = contractId;
    }
    UE_LOG(LogTemp, Display, TEXT("MYCONTRACT721: %s"),
           UTF8_TO_TCHAR(usercontractId.c_str()));
    UserContractAddress = UTF8_TO_TCHAR(usercontractId.c_str());

    UserContractAbiJson = TEXT(
        "[{\"inputs\":[],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"constructor\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,"
        "\"internalType\":\"address\",\"name\":\"owner\",\"type\":\"address\"},"
        "{\"indexed\":true,\"internalType\":\"address\",\"name\":\"approved\","
        "\"type\":\"address\"},{\"indexed\":true,\"internalType\":\"uint256\","
        "\"name\":\"tokenId\",\"type\":\"uint256\"}],\"name\":\"Approval\","
        "\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":"
        "true,\"internalType\":\"address\",\"name\":\"owner\",\"type\":"
        "\"address\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":"
        "\"operator\",\"type\":\"address\"},{\"indexed\":false,"
        "\"internalType\":\"bool\",\"name\":\"approved\",\"type\":\"bool\"}],"
        "\"name\":\"ApprovalForAll\",\"type\":\"event\"},{\"anonymous\":false,"
        "\"inputs\":[{\"indexed\":true,\"internalType\":\"address\",\"name\":"
        "\"previousOwner\",\"type\":\"address\"},{\"indexed\":true,"
        "\"internalType\":\"address\",\"name\":\"newOwner\",\"type\":"
        "\"address\"}],\"name\":\"OwnershipTransferred\",\"type\":\"event\"},{"
        "\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":"
        "\"address\",\"name\":\"from\",\"type\":\"address\"},{\"indexed\":true,"
        "\"internalType\":\"address\",\"name\":\"to\",\"type\":\"address\"},{"
        "\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"tokenId\","
        "\"type\":\"uint256\"}],\"name\":\"Transfer\",\"type\":\"event\"},{"
        "\"inputs\":[],\"name\":\"_tokenIdCounter\",\"outputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"_value\",\"type\":\"uint256\"}"
        "],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{"
        "\"internalType\":\"address\",\"name\":\"to\",\"type\":\"address\"},{"
        "\"internalType\":\"uint256\",\"name\":\"tokenId\",\"type\":"
        "\"uint256\"}],\"name\":\"approve\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"owner\",\"type\":\"address\"}],\"name\":"
        "\"balanceOf\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"\",\"type\":\"uint256\"}],\"stateMutability\":\"view\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"tokenId\",\"type\":\"uint256\"}],\"name\":\"getApproved\","
        "\"outputs\":[{\"internalType\":\"address\",\"name\":\"\",\"type\":"
        "\"address\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{"
        "\"inputs\":[{\"internalType\":\"address\",\"name\":\"owner\",\"type\":"
        "\"address\"},{\"internalType\":\"address\",\"name\":\"operator\","
        "\"type\":\"address\"}],\"name\":\"isApprovedForAll\",\"outputs\":[{"
        "\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],"
        "\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],"
        "\"name\":\"name\",\"outputs\":[{\"internalType\":\"string\",\"name\":"
        "\"\",\"type\":\"string\"}],\"stateMutability\":\"view\",\"type\":"
        "\"function\"},{\"inputs\":[],\"name\":\"owner\",\"outputs\":[{"
        "\"internalType\":\"address\",\"name\":\"\",\"type\":\"address\"}],"
        "\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"tokenId\",\"type\":"
        "\"uint256\"}],\"name\":\"ownerOf\",\"outputs\":[{\"internalType\":"
        "\"address\",\"name\":\"\",\"type\":\"address\"}],\"stateMutability\":"
        "\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":"
        "\"renounceOwnership\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"to\",\"type\":\"address\"},{\"internalType\":"
        "\"string\",\"name\":\"uri\",\"type\":\"string\"}],\"name\":"
        "\"safeMint\",\"outputs\":[],\"stateMutability\":\"nonpayable\","
        "\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\","
        "\"name\":\"from\",\"type\":\"address\"},{\"internalType\":\"address\","
        "\"name\":\"to\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"tokenId\",\"type\":\"uint256\"}],\"name\":"
        "\"safeTransferFrom\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"from\",\"type\":\"address\"},{\"internalType\":"
        "\"address\",\"name\":\"to\",\"type\":\"address\"},{\"internalType\":"
        "\"uint256\",\"name\":\"tokenId\",\"type\":\"uint256\"},{"
        "\"internalType\":\"bytes\",\"name\":\"data\",\"type\":\"bytes\"}],"
        "\"name\":\"safeTransferFrom\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"operator\",\"type\":\"address\"},{"
        "\"internalType\":\"bool\",\"name\":\"approved\",\"type\":\"bool\"}],"
        "\"name\":\"setApprovalForAll\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"bytes4\",\"name\":\"interfaceId\",\"type\":\"bytes4\"}],\"name\":"
        "\"supportsInterface\",\"outputs\":[{\"internalType\":\"bool\","
        "\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\","
        "\"type\":\"function\"},{\"inputs\":[],\"name\":\"symbol\",\"outputs\":"
        "[{\"internalType\":\"string\",\"name\":\"\",\"type\":\"string\"}],"
        "\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"tokenId\",\"type\":"
        "\"uint256\"}],\"name\":\"tokenURI\",\"outputs\":[{\"internalType\":"
        "\"string\",\"name\":\"\",\"type\":\"string\"}],\"stateMutability\":"
        "\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"from\",\"type\":\"address\"},{\"internalType\":"
        "\"address\",\"name\":\"to\",\"type\":\"address\"},{\"internalType\":"
        "\"uint256\",\"name\":\"tokenId\",\"type\":\"uint256\"}],\"name\":"
        "\"transferFrom\",\"outputs\":[],\"stateMutability\":\"nonpayable\","
        "\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\","
        "\"name\":\"newOwner\",\"type\":\"address\"}],\"name\":"
        "\"transferOwnership\",\"outputs\":[],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"}]");
    UserFunctionName = TEXT("ownerOf");
    UserFunctionArgs = TEXT("[{\"Uint\":{\"data\":\"2\"}}]");
}

void ACallDynamicContract::OnCallDynamicContractBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {

    // setup contract
    Setup();

    AMetaverseCharacter *MetaverseCharacter =
        Cast<AMetaverseCharacter>(OtherActor);
    if (MetaverseCharacter != nullptr) {
        if (UserDynamicContractObject == nullptr) {
            bool success = false;
            FString output_message = "";
            UserDynamicContractObject =
                MetaverseCharacter->CreateDynamicContract(
                    UserContractAddress, UserContractAbiJson, success,
                    output_message);

            if (GEngine) {
                FString ouput = FString::Printf(
                    TEXT("CreateDynamicContract success: %s, output_message: "
                         "%s"),
                    success ? TEXT("true") : TEXT("false"), *output_message);
                GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, ouput);
            }
        }

        if (UserDynamicContractObject != nullptr) {
            UserDynamicContractObject->CallDynamicContract(
                UserFunctionName, UserFunctionArgs,
                CallDynamicContractCallback);
        }
    }
}

void ACallDynamicContract::OnCallDynamicContract(FString JsonResult,
                                                 FString Result) {
    if (GEngine) {
        FString ouput = FString::Printf(
            TEXT("OnCallDynamicContract JsonResult: %s, Result: %s"),
            *JsonResult, *Result);
        GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, ouput);
    }
}