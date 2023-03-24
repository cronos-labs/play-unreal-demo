set PWD=%cd%
"C:\Program Files\Epic Games\UE_5.1\Engine\Build\BatchFiles\RunUAT.bat" ^
    BuildCookRun ^
    -utf8output ^
    -platform=Win64 ^
    -clientconfig=Development ^
    -serverconfig=Development ^
    -project="%PWD%\Metaverse.uproject" ^
    -noP4 -nodebuginfo -allmaps ^
    -cook -build -stage -prereqs -pak -archive ^
    -archivedirectory="%PWD%\archive"
