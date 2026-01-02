# EUI-SAIS
![WhatsApp_Image_2025-12-20_at_14 46 21_b6802370](https://github.com/user-attachments/assets/7332b045-af0b-49cf-ae78-b868af3c36a8)


EUI-SAIS is a command-line Student and Admin Information System (SAIS) built in C, specifically tailored for the Egypt University of Informatics. It provides separate interfaces for students and administrators to manage academic information, focusing on course registration and record-keeping.

## Features

### Dual User Roles
The system provides two distinct interfaces based on user authentication:

*   **Student Dashboard:** Allows students to manage their academic profile.
*   **Admin Dashboard:** Provides administrators with tools to manage student data and requests.

### Student Functionality
- **Secure Login:** Students authenticate using a unique Student ID and password stored in `DataBases/Student_DataBase.csv`.
- **Course Registration:** Students can request to register for new courses. The system automatically validates eligibility by checking prerequisites.
- **View Academic Records:** Students can view lists of their `Registered Courses` and `Passed Courses`.

### Admin Functionality
- **Secure Login:** Administrators authenticate using their email and password from `DataBases/Admin_DataBase.csv`.
- **Request Management:** Admins can review and either approve or deny pending course registration requests submitted by students.
- **Student Record Management:** Admins can manually add passed courses to a student's record or add new students to the system. The system features an automatic ID generator for new students based on the current year and the last assigned ID.

## Technical Details

-   **Data Storage:** User credentials and academic records are stored in simple CSV files (`Student_DataBase.csv`, `Admin_DataBase.csv`).
-   **Course Catalog & Prerequisites:** Course information, including prerequisites, is loaded from `DataBases/courses.txt` into an in-memory binary search tree. This allows for efficient validation of a student's eligibility for a course during registration.
-   **User Interface:** The application runs in the console and uses color-coded output to enhance readability and user experience.
-   **Build System:** The project can be compiled and run using either the provided `RUN.bat` script on Windows or with CMake for cross-platform compatibility.

## Getting Started

### Prerequisites
- A C compiler (e.g., GCC, or MinGW for Windows)
- (Optional) CMake

### Installation & Running (Windows)
The easiest way to run the project on Windows is using the provided batch script.

1.  Clone the repository:
    ```sh
    git clone https://github.com/1xastro/eui-sais.git
    cd eui-sais
    ```
2.  Ensure you have a GCC compiler (like MinGW) installed and added to your system's PATH.
3.  Double-click or run the `RUN.bat` script from your terminal:
    ```sh
    .\RUN.bat
    ```
    This script automatically compiles all source files, links the application icon, and runs the resulting `EUI_SIS.exe`.

### Installation & Running (CMake)
For a cross-platform build, you can use the `CMakeLists.txt` file.

1.  Clone the repository:
    ```sh
    git clone https://github.com/1xastro/eui-sais.git
    cd eui-sais
    ```
2.  Create and navigate to a build directory:
    ```sh
    mkdir build
    cd build
    ```
3.  Generate the build files:
    ```sh
    cmake ..
    ```
4.  Compile the project:
    ```sh
    cmake --build .
    ```
5.  Run the executable from the build directory.


## Team Members
* [Ahmed Samy (Astro1x)](https://github.com/1xAstro)   - Developer
* [Ibrahim Hikal](https://github.com/Ibrahim-hikal)          - Developer
* Mohamed Nadher (GR1M)  - Developer
* Norhan El Gamel        - Developer
* Karim Ahmed            - Developer
* Mohamed El Gebali      - Developer


## Project Structure
The repository is organized to separate data, core logic, and UI functions.

```
└── eui-sais/
    ├── DataBases/                  # Contains CSV databases and the course catalog txt file
    ├── Functions_Files/            # Main source code directory
    │   ├── Navigation_Functions/   # Handles UI screens (login, dashboards)
    │   └── User_Functions/         # Core business logic for users
    │       ├── Admin_Functions/    # Functions exclusive to administrators
    │       └── Student_Functions/  # Functions exclusive to students
    ├── main.c                      # Main entry point of the application
    ├── RUN.bat                     # Windows build and run script
    └── CMakeLists.txt              # CMake build configuration file

