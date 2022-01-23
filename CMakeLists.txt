cmake_minimum_required(VERSION 3.00)
project(pgfx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directory where exe,dll and static library saved
set(VGUI_BINARY_DIR ${CMAKE_BINARY_DIR}/bin-${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VGUI_BINARY_DIR})
set(3DPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3dparty)
set(IMGUI_DIR ${3DPARTY_DIR}/imgui)

#include(cmake/git-submodule-update.cmake)

include_directories(${3DPARTY_DIR})
include_directories(${3DPARTY_DIR}/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#Imgui
add_library(imgui ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx9.cpp ${IMGUI_DIR}/backends/imgui_impl_win32.cpp)

target_link_libraries(imgui d3d9 dwmapi)

#Examples
add_subdirectory(examples)
