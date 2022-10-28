// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CryptoFireTarget : TargetRules {
  public CryptoFireTarget(TargetInfo Target) : base(Target) {
    Type = TargetType.Game;
    DefaultBuildSettings = BuildSettingsVersion.V2;
    ExtraModuleNames.Add("CryptoFire");
  }
}
