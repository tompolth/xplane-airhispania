SET VERSION=030_AHSr108_64b
SET ROOT=X-IvAp_%VERSION%_win

mkdir %ROOT%

REM  Core README
xcopy ..\doc\*.txt %ROOT%

REM  Introduction
mkdir %ROOT%\introduction
copy ..\doc\*.htm %ROOT%\introduction
copy ..\doc\*.gif %ROOT%\introduction

REM  Program
mkdir %ROOT%\for_plugins_folder
copy ..\src\IVAO\XIvAp_AHSx64.xpl %ROOT%\for_plugins_folder
copy ..\src\FMOD\FMODWindows\api\fmodex64.dll %ROOT%\for_plugins_folder
copy .\msvc_64\msvcp110.dll %ROOT%\for_plugins_folder
copy .\msvc_64\msvcr110.dll %ROOT%\for_plugins_folder
mkdir "%ROOT%\for_plugins_folder\X-IvAp Resources\"
xcopy /E "X-IvAp Resources" "%ROOT%\for_plugins_folder\X-IvAp Resources\"

REM Compress
del /s /q xivap_*_win.zip
7za.exe a xivap_%VERSION%_win.zip %ROOT%
del /s /q %ROOT%
