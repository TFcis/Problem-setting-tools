@echo off
cd /D %1%
rem cd prob
del ..\prob.tar /Q
del ..\prob.tar.xz /Q 
"C:\Program Files\7-Zip\7z.exe" a -ttar ..\prob.tar conf.json http res
"C:\Program Files\7-Zip\7z.exe" a -txz  ..\prob.tar.xz ..\prob.tar
del ..\prob.tar /Q
cd ..
pause
