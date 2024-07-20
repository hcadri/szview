cmake_minimum_required(VERSION 3.5)

project(szview VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QTWEBENGINE_REMOTE_DEBUGGING, 9222)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        webengineviewmanager.cpp
        webengineviewmanager.h
        configloader.cpp
        HassioLoader.cpp
        HassioLoader.h
        SimpleHttpServer.cpp
        SampleHttpServer.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(szview
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET szview APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(szview SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(szview
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(szview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(szview PRIVATE Qt6::WebEngineWidgets)
target_link_libraries(szview PRIVATE Qt6::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.szview)
endif()
set_target_properties(szview PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS szview
    BUNDLE DESTINATION ..
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(szview)
endif()


configure_file(${CMAKE_SOURCE_DIR}/app/web/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/app/web/logo.png ${CMAKE_BINARY_DIR}/logo.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/app/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)


# Calculate the path to the MacOS directory inside the QTWB.app bundle
set(MACOS_BUNDLE_DIR "${CMAKE_BINARY_DIR}/app/szview.app/Contents/MacOS")

# Ensure the target directory exists before copying files
file(MAKE_DIRECTORY ${MACOS_BUNDLE_DIR})

# Copy files to the MacOS directory inside the szview.app bundle
configure_file(${CMAKE_SOURCE_DIR}/app/web/index.html ${MACOS_BUNDLE_DIR}/index.html COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/app/web/logo.png ${MACOS_BUNDLE_DIR}/logo.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/app/config.json ${MACOS_BUNDLE_DIR}/config.json COPYONLY)