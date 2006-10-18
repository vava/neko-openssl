del openssl.zip
mkdir temp
cd ./temp
mkdir openssl
cd openssl
xcopy ..\..\haxe /S /-Y
xcopy ..\..\haxelib.xml
mkdir src
mkdir ndll
cd ndll
mkdir Windows
mkdir Linux
cd Windows
xcopy ..\..\..\..\debug\openssl.ndll
cd ..\Linux
xcopy ..\..\..\..\ndll_linux\openssl.ndll
cd ..\..\src
mkdir opensslndll
mkdir ndlltest
cd opensslndll
xcopy ..\..\..\..\opensslndll
cd ..\ndlltest
xcopy ..\..\..\..\ndlltest
cd ..\..\..\..
winrar a -r -ep1 -x*\.svn\* -x*.user openssl.zip ./temp/*.*