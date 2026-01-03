cmake_minimum_required(VERSION 3.16)
project(Navik)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable automatic handling of Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include ./include)

# Source files
set(SOURCES
    src/Main.cpp
    src/MainWindow.cpp
    src/DirectoryView.cpp
    src/FileManagerActions.cpp
)

# Header files
set(HEADERS
    include/MainWindow.hpp
    include/DirectoryView.hpp
    include/FileManagerActions.hpp
)

# Resource files
set(RESOURCES
    resources/Navik.qrc
)

# Create executable
add_executable(${PROJECT_NAME}.bin
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME}.bin
    Qt6::Core
    Qt6::Widgets
)
