cmake_minimum_required(VERSION 3.16)
# CMP0000: Call the cmake_minimum_required() command at the beginning of the top-level
# CMakeLists.txt file even before calling the project() command.
# The cmake_minimum_required(VERSION) command implicitly invokes the cmake_policy(VERSION)
# command to specify that the current project code is written for the given range of CMake
# versions.
project(TreOnzTerminal)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(CheckFunctionExists)
include(CheckIncludeFile)

option(BUILD_EXAMPLE "Build example application. Default OFF." OFF)
option(QTERMWIDGET_USE_UTEMPTER "Uses the libutempter library. Mainly for FreeBSD" OFF)
option(USE_UTF8PROC "Use libutf8proc for better Unicode support. Default OFF" OFF)

# just change version for releases
set(QTERMWIDGET_VERSION_MAJOR "0")
set(QTERMWIDGET_VERSION_MINOR "14")
set(QTERMWIDGET_VERSION_PATCH "1")

set(QTERMWIDGET_VERSION "${QTERMWIDGET_VERSION_MAJOR}.${QTERMWIDGET_VERSION_MINOR}.${QTERMWIDGET_VERSION_PATCH}")

# additional cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Minimum Versions
set(QT_MINIMUM_VERSION "6.9.0")

find_package(Qt6Widgets "${QT_MINIMUM_VERSION}" REQUIRED)
find_package(Qt6LinguistTools "${QT_MINIMUM_VERSION}" REQUIRED)

if(USE_UTF8PROC)
    find_package(Utf8Proc REQUIRED)
endif()

if(APPLE)
    if(CMAKE_VERSION VERSION_GREATER 3.9)
        cmake_policy(SET CMP0068 NEW)
        set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
    endif()
endif()

set(QTERMWIDGET_LIBRARY_NAME TreOnzTerminal)
include_directories(${PROJECT_HEADER_DIR} ./lib)

# main library

set(SRCS
    lib/BlockArray.cpp
    lib/ColorScheme.cpp
    lib/Emulation.cpp
    lib/Filter.cpp
    lib/History.cpp
    lib/HistorySearch.cpp
    lib/KeyboardTranslator.cpp
    lib/konsole_wcwidth.cpp
    lib/kprocess.cpp
    lib/kpty.cpp
    lib/kptydevice.cpp
    lib/kptyprocess.cpp
    lib/Pty.cpp
    lib/qtermwidget.cpp
    lib/Screen.cpp
    lib/ScreenWindow.cpp
    lib/SearchBar.cpp
    lib/Session.cpp
    lib/ShellCommand.cpp
    lib/TerminalCharacterDecoder.cpp
    lib/TerminalDisplay.cpp
    lib/tools.cpp
    lib/Vt102Emulation.cpp
)

# Only the Headers that need to be moc'd go here
set(HDRS
    lib/Emulation.h
    lib/Filter.h
    lib/HistorySearch.h
    lib/kprocess.h
    lib/kptydevice.h
    lib/kptyprocess.h
    lib/Pty.h
    lib/qtermwidget.h
    lib/ScreenWindow.h
    lib/SearchBar.h
    lib/Session.h
    lib/TerminalDisplay.h
    lib/Vt102Emulation.h
)

set(UI
    lib/SearchBar.ui
)

# for distribution
set(HDRS_DISTRIB
    lib/qtermwidget.h
    lib/Emulation.h
    lib/Filter.h
)

# dirs
set(KB_LAYOUT_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${QTERMWIDGET_LIBRARY_NAME}/kb-layouts")
message(STATUS "Keyboard layouts will be installed in: ${KB_LAYOUT_DIR}")

set(COLORSCHEMES_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${QTERMWIDGET_LIBRARY_NAME}/color-schemes")
message(STATUS "Color schemes will be installed in: ${COLORSCHEMES_DIR}" )

set(QTERMWIDGET_INCLUDE_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${QTERMWIDGET_LIBRARY_NAME}")

CHECK_FUNCTION_EXISTS(updwtmpx HAVE_UPDWTMPX)

qt6_wrap_cpp(MOCS ${HDRS})
qt6_wrap_ui(UI_SRCS ${UI})
set(PKG_CONFIG_REQ "Qt6Widgets")

add_library(${QTERMWIDGET_LIBRARY_NAME} SHARED ${SRCS} ${MOCS} ${UI_SRCS} ${QTERMWIDGET_QM})
target_link_libraries(${QTERMWIDGET_LIBRARY_NAME} Qt6::Widgets)
set_target_properties( ${QTERMWIDGET_LIBRARY_NAME} PROPERTIES
                       SOVERSION ${QTERMWIDGET_VERSION_MAJOR}
                       VERSION ${QTERMWIDGET_VERSION}
                     )

if (QTERMWIDGET_USE_UTEMPTER)
    CHECK_INCLUDE_FILE(utempter.h HAVE_UTEMPTER)
    if (HAVE_UTEMPTER)
        target_compile_definitions(${QTERMWIDGET_LIBRARY_NAME} PRIVATE
                "HAVE_UTEMPTER"
        )
        target_link_libraries(${QTERMWIDGET_LIBRARY_NAME} ulog)
    endif()
endif()

if (UTF8PROC_FOUND)
    target_compile_definitions(${QTERMWIDGET_LIBRARY_NAME}
        PRIVATE
            "HAVE_UTF8PROC"
    )
    target_include_directories(${QTERMWIDGET_LIBRARY_NAME}
        INTERFACE
            ${UTF8PROC_INCLUDE_DIRS}
    )
    target_link_libraries(${QTERMWIDGET_LIBRARY_NAME}
        ${UTF8PROC_LIBRARIES}
    )
    string(APPEND PKG_CONFIG_REQ ", libutf8proc")
endif()

target_compile_definitions(${QTERMWIDGET_LIBRARY_NAME}
    PRIVATE
        "KB_LAYOUT_DIR=\"${KB_LAYOUT_DIR}\""
        "COLORSCHEMES_DIR=\"${COLORSCHEMES_DIR}\""
        "HAVE_POSIX_OPENPT"
        "HAVE_SYS_TIME_H"
        "QT_USE_QSTRINGBUILDER"
        "QT_NO_CAST_FROM_ASCII"
        "QT_NO_CAST_TO_ASCII"
        "QT_NO_URL_CAST_FROM_STRING"
        "QT_NO_CAST_FROM_BYTEARRAY"
)


install(TARGETS ${QTERMWIDGET_LIBRARY_NAME}
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    EXPORT "${QTERMWIDGET_LIBRARY_NAME}-targets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER
    COMPONENT Runtime
)

export(TARGETS ${QTERMWIDGET_LIBRARY_NAME}
    FILE "${CMAKE_BINARY_DIR}/${QTERMWIDGET_LIBRARY_NAME}-targets.cmake"
    EXPORT_LINK_INTERFACE_LIBRARIES
)
# end of main library


# example application
#if(BUILD_EXAMPLE)
#    set(EXAMPLE_SRC example/main.cpp)
#    add_executable(example ${EXAMPLE_SRC})
#    target_link_libraries(example ${QTERMWIDGET_LIBRARY_NAME})
#endif()
# end of example application


