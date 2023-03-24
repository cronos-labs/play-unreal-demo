& "C:\Program Files\Android\Android Studio\jre\bin\keytool.exe" `
-genkey -v -keystore key.keystore -alias Mykey -keyalg RSA -keysize 2048 -validity 10000 `
-dname "CN=TestGuy, OU=MyCompany, O=MyGame, L=MyCity, ST=NC, C=00" `
-storepass 123456 -keypass 123456

$path = "Build\Android"
If(!(Test-Path -PathType container $path))
{
      New-Item -ItemType Directory -Path $path
}


move key.keystore Build\Android
