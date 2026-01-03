cmake_minimum_required(VERSION 3.16)
project(Lekhak)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable automatic handling of Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_SOURCE_DIR}/include ./include)

# Source files
set(SOURCES
    src/Main.cpp
    src/MainWindow.cpp
    src/FindAndReplaceDialog.cpp
)

# Header files
set(HEADERS
    include/MainWindow.hpp
    include/FindAndReplaceDialog.hpp
)

# Resource files
set(RESOURCES
    resources/Lekhak.qrc
)

# Create executable
add_executable(${PROJECT_NAME}.bin
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}.bin
    Qt6::Core
    Qt6::Widgets
)
