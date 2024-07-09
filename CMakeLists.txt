cmake_minimum_required(VERSION 3.27)

project(fcitx5-webpanel VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Gettext REQUIRED)
find_package(Fcitx5Core 5.1.10 REQUIRED)

include("${FCITX_INSTALL_CMAKECONFIG_DIR}/Fcitx5Utils/Fcitx5CompilerSettings.cmake")

set(BUILD_PREVIEW OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(fcitx5-webview)
add_subdirectory(src)
