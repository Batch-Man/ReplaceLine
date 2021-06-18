@echo off
SetLocal Enabledelayedexpansion
cls

REM Reading Name of file... for Title bar
For /f "tokens=1,2* delims=_" %%A in ("%~n0") do (Set "_Title=%%~B")

Title !_Title! Demo File - www.thebateam.org
Cd Files
Echo.
Echo ----Current Data in Demo_File.txt--------
Echo.
Type "Demo_File.txt"
Echo.
Echo -----------------------------------------

Set _Counter=0
REM Getting Current number of lines in the text file
For /f "tokens=*" %%A in ('Type "Demo_File.txt"') do (Set /A _Counter+=1)
:GetData
Set _Line=
Set /p "_Line=Enter New Line Content: "
If not Defined _Line (Goto :GetData)
:GetLoc
Set _Loc=
Set /p "_Loc=Enter the location from where to replace [Line Number]: "
If not Defined _Loc (Goto :GetLoc)

REM Checking if the entered value is number
Set _Copy_Loc=%_Loc%
For /L %%A in (0,1,9) do (Set "_Copy_Loc=!_Copy_Loc:%%~A=x!")

Set "_Copy_Loc=!_Copy_Loc:x=!"

IF /i "!_Copy_Loc!" NEQ "" (Goto :GetLoc)
IF !_Loc! GTR !_Counter! (Goto :GetLoc)

ReplaceLine "Demo_File.txt" "%_Loc%" "%_Line%"
Echo.
Echo ----Current Data in Demo_File.txt--------
Echo.
Type "Demo_File.txt"
Echo.
Echo -----------------------------------------
pause >nul