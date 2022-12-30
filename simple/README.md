# simple example
This repository contains a sample project that uses the Cronos Play Unreal SDK plugin. For more
information, please see the [Cronos Play Unreal SDK plugin
repository](https://github.com/crypto-com/play-unreal-plugin).

## Pre-requisites
- Windows: Visual Studo 2019 or later
- Mac: XCODE 13.2.1
- Android: NDK 21.4.7075529
- IOS: Minimum IOS 14
- Unreal Engine: 4.27
- Plugin: Cronos Play For Unreal Engine

## Pre-built Release
Download the release zip file in [Release](https://github.com/cronos-labs/play-unreal-demo/releases) page.

## Setup Manually
If you prefer configuring the project manually,

### Windows
``` powershell
   git clone https://github.com/cronos-labs/play-unreal-plugin.git Plugins\play-unreal-plugin\
   cd Plugins\play-unreal-plugin\
   .\install-play-cpp-sdk.bat
   cd ..\..\
   .\windows-build.bat
```

### Mac or Linux
``` sh
   git clone https://github.com/cronos-labs/play-unreal-plugin.git Plugins/play-unreal-plugin/
   cd Plugins/play-unreal-plugin
   make
   cd ../../
   make
```

### Android
1. Install Android Studio, and download android sdk and ndk
- Customize > All Settings > Appearance & Behavior > System Settings > Android SDK
- SDK Platforms: Android 11.0 (R), API Level 30 (>= 28)
- SDK Tools
    - Android SDK Build-Tools: 30.0.3 (>= 28)
    - NDK (Side by side): 21.47075529

2-1. Build Android on Mac
- Setup the key for signing, check
    [here](https://docs.unrealengine.com/4.27/en-US/SharingAndReleasing/Mobile/Android/DistributionSigning/),
    or run `./android_key_gen.sh` to generate a test keystore
- Project Settings > Platforms > Android SDK ($HOME: replace with the location of your HOME
    directory)
    - Location of Android SDK: $HOME/Library/Android/sdk
    - Location of Android NDK: $HOME/Library/Android/sdk/ndk/21.4.7075529
    - Location of JAVA: /Applications/Android Studio.app/Contents/jre/Contents/Home
    - SDK API Level: latest
    - NDK API Level: android-21
    - Run:
    ```sh
    git clone https://github.com/cronos-labs/play-unreal-plugin.git Plugins/play-unreal-plugin/
    cd Plugins/play-unreal-plugin/ && make
    cd ../../ && make android
    ```

2-2. Build Android on Windows
- Setup the key for signing, check
    [here](https://docs.unrealengine.com/4.27/en-US/SharingAndReleasing/Mobile/Android/DistributionSigning/),
    or run `.\android_key_gen.ps1` to generate a test keystore
- Run
``` powershell
    git clone https://github.com/cronos-labs/play-unreal-plugin.git Plugins/play-unreal-plugin/
    cd Plugins\play-unreal-plugin\
    .\install-play-cpp-sdk.bat
    cd ..\..\
    .\android-build.ps1
```

### iOS
1. Specify a valid Provision and a valid Certificate in Project Settings > Platforms > iOS > Mobile Provision
2. DISABLE `Support bitcode in shipping` in Project Settings > Platforms > iOS > Build
3. Setup distribution type based on the iOS profile in Project Settings > Packaging > Project > For Distribution
```sh
    git clone https://github.com/cronos-labs/play-unreal-plugin.git Plugins/play-unreal-plugin/
    cd Plugins/play-unreal-plugin/ && make
    cd ../../ && make ios
```

## More information for Cronos Play
If you are a game developer, please visit [Cronos Play](https://cronos.org/play) or fill this
[Contact Form](https://airtable.com/shrFiQnLrcpeBp2lS) for more information.
