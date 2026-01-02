@echo off
echo Compiling Project...

:: 1. Compiler Settings
set COMPILER=gcc
set OUTPUT=-o EUI_SIS.exe
set FLAGS=-Wall

:: 2. Include Paths
set INCLUDES=-I . ^
             -I DataBases ^
             -I Functions_Files ^
             -I Functions_Files\User_Functions ^
             -I Functions_Files\User_Functions\Student_Functions ^
             -I Functions_Files\User_Functions\Student_Functions\Headers ^
             -I Functions_Files\User_Functions\Student_Functions\src ^
             -I Functions_Files\User_Functions\Admin_Functions ^
             -I Functions_Files\User_Functions\Admin_Functions\Headers ^
             -I Functions_Files\User_Functions\Admin_Functions\src ^
             -I Functions_Files\Navigation_Functions\Headers

:: 3. Source Files
set SOURCES=main.c ^
            Functions_Files\User_Functions\Student_Functions\src\Student.c ^
            Functions_Files\User_Functions\Student_Functions\src\Student_Login.c ^
            Functions_Files\User_Functions\Admin_Functions\src\Admin.c ^
            Functions_Files\User_Functions\Admin_Functions\src\Admin_Login.c ^
            Functions_Files\User_Functions\Student_Functions\src\view_passed_courses.c ^
            Functions_Files\User_Functions\LinkedLists.c ^
            Functions_Files\User_Functions\Admin_Functions\src\Admin_Courses.c ^
            Functions_Files\User_Functions\Student_Functions\src\Student_Courses.c ^
            Functions_Files\Navigation_Functions\src\Login_Screen.c ^
            Functions_Files\Navigation_Functions\src\Student_Dashboard.c ^
            Functions_Files\Navigation_Functions\src\Admin_Dashboard.c ^
            Functions_Files\User_Functions\Student_Functions\src\view_registered_courses.c ^
            Functions_Files\Navigation_Functions\src\Press_Key_Back.c ^
            Functions_Files\User_Functions\Admin_Functions\src\Add_Passed_Manual.c ^
            Functions_Files\User_Functions\Admin_Functions\src\Student_Add.c

:: Compile the icon resource (Uses your path in DataBases)
windres resource.rc -O coff -o resource.res

:: 4. Run the Compilation (Including the compiled resource)
%COMPILER% %SOURCES% resource.res %INCLUDES% %OUTPUT% %FLAGS%

:: Cleanup temporary resource file
if exist resource.res del resource.res

:: 5. Check for Success
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Compilation Failed! Check the logs above.
    pause
    exit /b
)

echo.
echo [SUCCESS] Compilation finished. Running StudentApp...
echo ---------------------------------------------------
EUI_SIS.exe
echo.
echo ---------------------------------------------------
pause