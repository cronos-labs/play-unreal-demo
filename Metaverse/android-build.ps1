[System.Environment]::SetEnvironmentVariable('JAVA_HOME','C:\Program Files\Android\Android Studio\jre')
[System.Environment]::SetEnvironmentVariable('ANDROID_HOME',"$env:LOCALAPPDATA\Android\Sdk")
[System.Environment]::SetEnvironmentVariable('NDKROOT',"$env:LOCALAPPDATA\Android\Sdk\ndk\25.1.8937393")

$curDir = (Get-Item .).FullName
cmd.exe /c "C:\Program Files\Epic Games\UE_5.1\Engine\Build\BatchFiles\RunUAT.bat" `
    BuildCookRun `
    -utf8output `
    -platform=Android `
    -cookflavor=ASTC `
    -clientconfig=Development `
    -serverconfig=Development `
    -project="$curDir/Metaverse.uproject" `
    -noP4 -nodebuginfo -allmaps `
    -cook -build -stage -prereqs -pak -archive `
    -archivedirectory="$curDir\archive"
