cmake_minimum_required(VERSION 3.31)
project(Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(DataBases)
include_directories(Functions_Files)
include_directories(Functions_Files/User_Functions)
include_directories(Functions_Files/User_Functions/Student_Functions)
include_directories(Functions_Files/User_Functions/Student_Functions/Headers)
include_directories(Functions_Files/User_Functions/Student_Functions/src)
include_directories(Functions_Files/user_functions/Admin_Functions)
include_directories(Functions_Files/user_functions/Admin_Functions/Headers)
include_directories(Functions_Files/user_functions/Admin_Functions/src)
add_executable(Project
    DataBases/Student_DataBase.csv
    Functions_Files/User_Functions/Student_Functions/Headers/Student.h
    Functions_Files/User_Functions/Student_Functions/src/Student.c
    Functions_Files/User_Functions/Student_Functions/src/Student_Login.c
    Functions_Files/user_functions/Admin_Functions/Headers/Admin.h
    Functions_Files/user_functions/Admin_Functions/src/Admin.c
    Functions_Files/user_functions/Admin_Functions/src/Admin_Login.c
    Functions_Files/user_functions/student_functions/src/view_passed_courses.c
    main.c
        Functions_Files/User_Functions/LinkedLists.h
        Functions_Files/User_Functions/LinkedLists.c
        Functions_Files/User_Functions/Admin_Functions/src/Admin_Courses.c
        Functions_Files/User_Functions/Student_Functions/src/Student_Courses.c
        Functions_Files/User_Functions/Student_Functions/Headers/Student_Courses.h
        Functions_Files/User_Functions/Admin_Functions/Headers/Admin_Courses.h
        Functions_Files/Navigation_Functions/src/Login_Screen.c
        Functions_Files/Navigation_Functions/Headers/Login_Screen.h
        Functions_Files/Navigation_Functions/src/Student_Dashboard.c
        Functions_Files/Navigation_Functions/Headers/Student_Dashboard.h
        Functions_Files/Navigation_Functions/src/Admin_Dashboard.c
        Functions_Files/Navigation_Functions/Headers/Admin_Dashboard.h
        Functions_Files/User_Functions/User_Struct.h
        Functions_Files/User_Functions/Student_Functions/Headers/view_passed_courses.h
        Functions_Files/User_Functions/Student_Functions/src/view_registered_courses.c
        Functions_Files/User_Functions/Student_Functions/Headers/view_registered_courses.h
        Functions_Files/Navigation_Functions/src/Press_Key_Back.c
        Functions_Files/Navigation_Functions/Headers/Press_Key_Back.h
        Functions_Files/User_Functions/Admin_Functions/src/Add_Passed_Manual.c
        Functions_Files/User_Functions/Admin_Functions/src/Student_Add.c)
