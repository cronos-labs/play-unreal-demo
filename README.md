# Cronos Play Unreal SDK Demo
This repository contains sample projects that uses the Cronos Play Unreal SDK plugin.
For more information, please see the [Cronos Play Unreal SDK plugin repository](https://github.com/crypto-com/play-unreal-plugin).

## basic flow
- inherit blueprint DefiWalletCoreActor
- restore wallet with mnemonics
- transfer amount
- most of apis are async, receive result with events

## examples
there are markdown files in each projects for details 
### simple
- basic demo 
- eth address generation with index
- get balance, transfer etc
- erc721 fetch, transfer 
- erc1155 fetch, transfer
- wallet-connect signing
- cronoscan, blockscout query


### play2earn
- basic erc721, erc1155 nft game example
- need to mint tokens beforehand

## Pre-requisites
Windows: Visual Studo 2019 or later
Mac: XCODE 13.2.1
Android: NDK 21.4.7075529
Unreal Engine: 4.27 or 5.x
Plugin: Cronos Play For Unreal Engine in Epic Marketplace

## Pre-built Release
Download the release zip file in [Release](https://github.com/cronos-labs/play-unreal-demo/releases) page.

### `CronosPlayDemo.zip`
- Assets: `./Content/CronosPlayUnreal/Blueprint`
- `CronosPlayUnreal` Plugin: `./Plugins/play-unreal-plugin`

### `CronosPlayAssetPack.zip`
- Assets: Blueprints, widgets etc

### Contribute
We welcome contributions of any kind!
- For bugs reports or feature requests, please post to [Github issues](https://github.com/cronos-labs/play-unreal-plugin/issues/new)
- We love pull requests (see the [CONTRIBUTING](CONTRIBUTING.md) Guidelines for more details)

### More information for Cronos Play
If you are a game developer, please visit [Cronos Play](https://cronos.org/play) or fill this [Contact Form](https://airtable.com/shrFiQnLrcpeBp2lS) for more information.
