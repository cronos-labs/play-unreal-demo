# Cronos Play Unreal SDK Demo
This repository contains a sample project that uses the Cronos Play Unreal SDK plugin.
For more information, please see the [Cronos Play Unreal SDK plugin repository](https://github.com/crypto-com/play-unreal-plugin).


## Pre-requisites
Visual Studo 2019 or later (2022) or XCODE 13.2.1
Unreal Engine 4.27 and 5.0 are supported, i.e. one of them should be installed via the Epic Games Launcher.


## Installation Mac
1. in mac, just `make`
2. cd CronosPlayUnrealDemo
3. open `CronosPlayUnrealDeemo.project`
4. run

## Installation Windows
1. in windows, just `git submodule update --init --recursive`
2. cd CronosPlayUnrealDemo
3. run copydll.bat
4. open `CronosPlayUnrealDemo.project`
5. run

## To use dynamic libraries
if visual studio is used, add these lines to top of cpp source
```C++
#pragma warning(disable : 4583)
#pragma warning(disable : 4582)
```

## How to Run
1. cd CronosPlayUnrealDemo
2. click `CronosPlayUnrealDemo.project`
3. or run unreal engine 4.27 , and open project `CronosPlayUnrealDemo.uproject`

### More information for Cronos Play
If you are a game developer, please visit [Cronos Play](https://cronos.org/play) or fill this [Contact Form](https://airtable.com/shrFiQnLrcpeBp2lS) for more information.
