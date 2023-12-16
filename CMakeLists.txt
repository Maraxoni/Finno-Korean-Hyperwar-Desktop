cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Add all source files to the SOURCES variable
set(SOURCES 
    Finno-Korean-Hyperwar.cpp
)

# Find wxWidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Include wxWidgets include directories
include_directories(${wxWidgets_INCLUDE_DIRS})

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Change the entry point to a console application
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

# Create an executable file based on the source files
add_executable(Finno-Korean-Hyperwar ${SOURCES})

# Link against all libraries in D:\Thingies\wxWidgets-3.2.4\lib\gcc_dll
file(GLOB wxWidgets_LIBRARIES_LIST "D:/Thingies/ExternalLibs/wxWidgets-3.2.4/lib/gcc_dll/*.a")
target_link_libraries(Finno-Korean-Hyperwar ${wxWidgets_LIBRARIES_LIST})