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

void ACallDynamicContract::SetupForSwap() {
    const char *contractId = std::getenv("MYCONTRACT721");
    std::string usercontractId = "";
    if (contractId != nullptr) {
        usercontractId = contractId;
    }
    UserContractAddress = UTF8_TO_TCHAR(usercontractId.c_str());

    UserContractAbiJson = TEXT(
        "[{\"inputs\":[{\"internalType\":\"address\",\"name\":\"_factory\","
        "\"type\":\"address\"},{\"internalType\":\"address\",\"name\":\"_"
        "WETH\",\"type\":\"address\"}],\"stateMutability\":\"nonpayable\","
        "\"type\":\"constructor\"},{\"inputs\":[],\"name\":\"WETH\","
        "\"outputs\":[{\"internalType\":\"address\",\"name\":\"\",\"type\":"
        "\"address\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{"
        "\"inputs\":[{\"internalType\":\"address\",\"name\":\"tokenA\","
        "\"type\":\"address\"},{\"internalType\":\"address\",\"name\":"
        "\"tokenB\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"amountADesired\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountBDesired\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountAMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountBMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"address\",\"name\":\"to\","
        "\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":"
        "\"deadline\",\"type\":\"uint256\"}],\"name\":\"addLiquidity\","
        "\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"amountA\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"amountB\",\"type\":\"uint256\"},{\"internalType\":\"uint256\","
        "\"name\":\"liquidity\",\"type\":\"uint256\"}],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"address\",\"name\":\"token\",\"type\":\"address\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountTokenDesired\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"amountTokenMin\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountETHMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"address\",\"name\":\"to\",\"type\":\"address\"},{"
        "\"internalType\":\"uint256\",\"name\":\"deadline\",\"type\":"
        "\"uint256\"}],\"name\":\"addLiquidityETH\",\"outputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"amountToken\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountETH\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"liquidity\",\"type\":\"uint256\"}],\"stateMutability\":\"payable\","
        "\"type\":\"function\"},{\"inputs\":[],\"name\":\"factory\","
        "\"outputs\":[{\"internalType\":\"address\",\"name\":\"\",\"type\":"
        "\"address\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{"
        "\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"amountOut\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"reserveIn\",\"type\":\"uint256\"},{\"internalType\":\"uint256\","
        "\"name\":\"reserveOut\",\"type\":\"uint256\"}],\"name\":"
        "\"getAmountIn\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"amountIn\",\"type\":\"uint256\"}],\"stateMutability\":\"pure\","
        "\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\","
        "\"name\":\"amountIn\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"reserveIn\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"reserveOut\",\"type\":"
        "\"uint256\"}],\"name\":\"getAmountOut\",\"outputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"amountOut\",\"type\":"
        "\"uint256\"}],\"stateMutability\":\"pure\",\"type\":\"function\"},{"
        "\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"amountOut\","
        "\"type\":\"uint256\"},{\"internalType\":\"address[]\",\"name\":"
        "\"path\",\"type\":\"address[]\"}],\"name\":\"getAmountsIn\","
        "\"outputs\":[{\"internalType\":\"uint256[]\",\"name\":\"amounts\","
        "\"type\":\"uint256[]\"}],\"stateMutability\":\"view\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"amountIn\",\"type\":\"uint256\"},{\"internalType\":\"address[]\","
        "\"name\":\"path\",\"type\":\"address[]\"}],\"name\":\"getAmountsOut\","
        "\"outputs\":[{\"internalType\":\"uint256[]\",\"name\":\"amounts\","
        "\"type\":\"uint256[]\"}],\"stateMutability\":\"view\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"amountA\",\"type\":\"uint256\"},{\"internalType\":\"uint256\","
        "\"name\":\"reserveA\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"reserveB\",\"type\":\"uint256\"}],\"name\":"
        "\"quote\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"amountB\",\"type\":\"uint256\"}],\"stateMutability\":\"pure\","
        "\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\","
        "\"name\":\"tokenA\",\"type\":\"address\"},{\"internalType\":"
        "\"address\",\"name\":\"tokenB\",\"type\":\"address\"},{"
        "\"internalType\":\"uint256\",\"name\":\"liquidity\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountAMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"amountBMin\",\"type\":\"uint256\"},{\"internalType\":\"address\","
        "\"name\":\"to\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"removeLiquidity\",\"outputs\":[{\"internalType\":\"uint256\","
        "\"name\":\"amountA\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountB\",\"type\":\"uint256\"}],"
        "\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":"
        "[{\"internalType\":\"address\",\"name\":\"token\",\"type\":"
        "\"address\"},{\"internalType\":\"uint256\",\"name\":\"liquidity\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"amountTokenMin\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountETHMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"address\",\"name\":\"to\",\"type\":\"address\"},{"
        "\"internalType\":\"uint256\",\"name\":\"deadline\",\"type\":"
        "\"uint256\"}],\"name\":\"removeLiquidityETH\",\"outputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"amountToken\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountETH\","
        "\"type\":\"uint256\"}],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":"
        "\"token\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"liquidity\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountTokenMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountETHMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address\",\"name\":\"to\",\"type\":"
        "\"address\"},{\"internalType\":\"uint256\",\"name\":\"deadline\","
        "\"type\":\"uint256\"}],\"name\":"
        "\"removeLiquidityETHSupportingFeeOnTransferTokens\",\"outputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"amountETH\",\"type\":"
        "\"uint256\"}],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":"
        "\"token\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"liquidity\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountTokenMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountETHMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address\",\"name\":\"to\",\"type\":"
        "\"address\"},{\"internalType\":\"uint256\",\"name\":\"deadline\","
        "\"type\":\"uint256\"},{\"internalType\":\"bool\",\"name\":"
        "\"approveMax\",\"type\":\"bool\"},{\"internalType\":\"uint8\","
        "\"name\":\"v\",\"type\":\"uint8\"},{\"internalType\":\"bytes32\","
        "\"name\":\"r\",\"type\":\"bytes32\"},{\"internalType\":\"bytes32\","
        "\"name\":\"s\",\"type\":\"bytes32\"}],\"name\":"
        "\"removeLiquidityETHWithPermit\",\"outputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountToken\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountETH\",\"type\":"
        "\"uint256\"}],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":"
        "\"token\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"liquidity\",\"type\":\"uint256\"},{\"internalType\":"
        "\"uint256\",\"name\":\"amountTokenMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountETHMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address\",\"name\":\"to\",\"type\":"
        "\"address\"},{\"internalType\":\"uint256\",\"name\":\"deadline\","
        "\"type\":\"uint256\"},{\"internalType\":\"bool\",\"name\":"
        "\"approveMax\",\"type\":\"bool\"},{\"internalType\":\"uint8\","
        "\"name\":\"v\",\"type\":\"uint8\"},{\"internalType\":\"bytes32\","
        "\"name\":\"r\",\"type\":\"bytes32\"},{\"internalType\":\"bytes32\","
        "\"name\":\"s\",\"type\":\"bytes32\"}],\"name\":"
        "\"removeLiquidityETHWithPermitSupportingFeeOnTransferTokens\","
        "\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"amountETH\","
        "\"type\":\"uint256\"}],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":"
        "\"tokenA\",\"type\":\"address\"},{\"internalType\":\"address\","
        "\"name\":\"tokenB\",\"type\":\"address\"},{\"internalType\":"
        "\"uint256\",\"name\":\"liquidity\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountAMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountBMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"address\",\"name\":\"to\","
        "\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":"
        "\"deadline\",\"type\":\"uint256\"},{\"internalType\":\"bool\","
        "\"name\":\"approveMax\",\"type\":\"bool\"},{\"internalType\":"
        "\"uint8\",\"name\":\"v\",\"type\":\"uint8\"},{\"internalType\":"
        "\"bytes32\",\"name\":\"r\",\"type\":\"bytes32\"},{\"internalType\":"
        "\"bytes32\",\"name\":\"s\",\"type\":\"bytes32\"}],\"name\":"
        "\"removeLiquidityWithPermit\",\"outputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountA\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountB\",\"type\":"
        "\"uint256\"}],\"stateMutability\":\"nonpayable\",\"type\":"
        "\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":"
        "\"amountOut\",\"type\":\"uint256\"},{\"internalType\":\"address[]\","
        "\"name\":\"path\",\"type\":\"address[]\"},{\"internalType\":"
        "\"address\",\"name\":\"to\",\"type\":\"address\"},{\"internalType\":"
        "\"uint256\",\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapETHForExactTokens\",\"outputs\":[{\"internalType\":\"uint256[]"
        "\",\"name\":\"amounts\",\"type\":\"uint256[]\"}],\"stateMutability\":"
        "\"payable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountOutMin\",\"type\":\"uint256\"},{"
        "\"internalType\":\"address[]\",\"name\":\"path\",\"type\":\"address[]"
        "\"},{\"internalType\":\"address\",\"name\":\"to\",\"type\":"
        "\"address\"},{\"internalType\":\"uint256\",\"name\":\"deadline\","
        "\"type\":\"uint256\"}],\"name\":\"swapExactETHForTokens\",\"outputs\":"
        "[{\"internalType\":\"uint256[]\",\"name\":\"amounts\",\"type\":"
        "\"uint256[]\"}],\"stateMutability\":\"payable\",\"type\":\"function\"}"
        ",{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"amountOutMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"address[]\",\"name\":"
        "\"path\",\"type\":\"address[]\"},{\"internalType\":\"address\","
        "\"name\":\"to\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapExactETHForTokensSupportingFeeOnTransferTokens\",\"outputs\":[],"
        "\"stateMutability\":\"payable\",\"type\":\"function\"},{\"inputs\":[{"
        "\"internalType\":\"uint256\",\"name\":\"amountIn\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountOutMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"address[]\",\"name\":"
        "\"path\",\"type\":\"address[]\"},{\"internalType\":\"address\","
        "\"name\":\"to\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapExactTokensForETH\",\"outputs\":[{\"internalType\":\"uint256[]"
        "\",\"name\":\"amounts\",\"type\":\"uint256[]\"}],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountIn\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountOutMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address[]\",\"name\":\"path\","
        "\"type\":\"address[]\"},{\"internalType\":\"address\",\"name\":\"to\","
        "\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":"
        "\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapExactTokensForETHSupportingFeeOnTransferTokens\",\"outputs\":[],"
        "\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":"
        "[{\"internalType\":\"uint256\",\"name\":\"amountIn\",\"type\":"
        "\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"amountOutMin\","
        "\"type\":\"uint256\"},{\"internalType\":\"address[]\",\"name\":"
        "\"path\",\"type\":\"address[]\"},{\"internalType\":\"address\","
        "\"name\":\"to\",\"type\":\"address\"},{\"internalType\":\"uint256\","
        "\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapExactTokensForTokens\",\"outputs\":[{\"internalType\":\"uint256["
        "]\",\"name\":\"amounts\",\"type\":\"uint256[]\"}],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountIn\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountOutMin\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address[]\",\"name\":\"path\","
        "\"type\":\"address[]\"},{\"internalType\":\"address\",\"name\":\"to\","
        "\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":"
        "\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapExactTokensForTokensSupportingFeeOnTransferTokens\",\"outputs\":"
        "[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{"
        "\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"amountOut\","
        "\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":"
        "\"amountInMax\",\"type\":\"uint256\"},{\"internalType\":\"address[]\","
        "\"name\":\"path\",\"type\":\"address[]\"},{\"internalType\":"
        "\"address\",\"name\":\"to\",\"type\":\"address\"},{\"internalType\":"
        "\"uint256\",\"name\":\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapTokensForExactETH\",\"outputs\":[{\"internalType\":\"uint256[]"
        "\",\"name\":\"amounts\",\"type\":\"uint256[]\"}],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":"
        "\"uint256\",\"name\":\"amountOut\",\"type\":\"uint256\"},{"
        "\"internalType\":\"uint256\",\"name\":\"amountInMax\",\"type\":"
        "\"uint256\"},{\"internalType\":\"address[]\",\"name\":\"path\","
        "\"type\":\"address[]\"},{\"internalType\":\"address\",\"name\":\"to\","
        "\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":"
        "\"deadline\",\"type\":\"uint256\"}],\"name\":"
        "\"swapTokensForExactTokens\",\"outputs\":[{\"internalType\":\"uint256["
        "]\",\"name\":\"amounts\",\"type\":\"uint256[]\"}],\"stateMutability\":"
        "\"nonpayable\",\"type\":\"function\"},{\"stateMutability\":"
        "\"payable\",\"type\":\"receive\"}]");
    // swapExactETHForTokens(uint256,address[],address,uint256)
    UserFunctionName = TEXT("swapExactETHForTokens");
    UserFunctionArgs = TEXT(
        "[    {        \"Uint\": {            \"data\": \"100\"        }    }, "
        "   {        \"Array\": {            \"data\": [                {      "
        "              \"Address\": {                        \"data\": "
        "\"0x112233445566778899aabbccddeeff0011223344\"                    }   "
        "             },                {                    \"Address\": {    "
        "                    \"data\": "
        "\"0x2233445566778899aabbccddeeff001122334455\"                    }   "
        "             },                {                    \"Address\": {    "
        "                    \"data\": "
        "\"0x33445566778899aabbccddeeff00112233445566\"                    }   "
        "             }            ]        }    },    {        \"Address\": { "
        "           \"data\": \"0x445566778899aabbccddeeff0011223344556677\"   "
        "     }    },    {        \"Uint\": {            \"data\": \"200\"     "
        "   }    }]");
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