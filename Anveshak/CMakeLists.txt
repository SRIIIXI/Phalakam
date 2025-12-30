cmake_minimum_required(VERSION 3.16)
project(Anveshak VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    WebEngineQuick
)

# Enable automatic handling of Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt policy for QML module URI
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

# Source files
set(SOURCES
    src/main.cpp
)

set(RESOURCE_FILE ./resources/Anveshak.qrc)

qt_add_executable(${PROJECT_NAME}
    ${SOURCES} ${RESOURCE_FILE}
)

# Add QML module
qt_add_qml_module(${PROJECT_NAME}
    URI Anveshak
    VERSION 1.0
    QML_FILES ${QML_FILES}
)

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::WebEngineQuick
)

# Install target (optional)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
