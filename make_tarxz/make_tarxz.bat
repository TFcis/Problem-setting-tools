@echo off
cd /D %1%
del ..\prob.tar /Q
del ..\prob.tar.xz /Q
if exist "C:\Program Files\7-Zip\7z.exe" (
	"C:\Program Files\7-Zip\7z.exe" a -ttar ..\prob.tar conf.json http res
	"C:\Program Files\7-Zip\7z.exe" a -txz  ..\prob.tar.xz ..\prob.tar
) else if exist "C:\Program Files (x86)\7-Zip\7z.exe" (
	"C:\Program Files (x86)\7-Zip\7z.exe" a -ttar ..\prob.tar conf.json http res
	"C:\Program Files (x86)\7-Zip\7z.exe" a -txz  ..\prob.tar.xz ..\prob.tar
) else (
	echo "7-Zip not found. Cannot make file."
)
del ..\prob.tar /Q
cd ..
pause
