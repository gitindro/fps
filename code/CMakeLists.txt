cmake_minimum_required(VERSION 3.12)



project(shooter)

include(../CMakeCommon/CommonMacros.txt)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")


set(PHYSFS_ARCHIVE_WAD  OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_HOG  OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_MVL  OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_QPAK OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_SLB OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_VDF OFF CACHE BOOL "")
set(PHYSFS_ARCHIVE_SLB OFF CACHE BOOL "")
set(PHYSFS_BUILD_STATIC ON CACHE BOOL "")

set(PHYSFS_BUILD_SHARED OFF CACHE BOOL "")
set(PHYSFS_BUILD_TEST OFF CACHE BOOL "")
set(PHYSFS_BUILD_DOCS OFF CACHE BOOL "")

if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(dependencies/src/glfw)
add_subdirectory(dependencies/src/SOIL2)
add_subdirectory(dependencies/src/physfs)

set(GLAD_SOURCES dependencies/glad/src/gl.c)


if(WIN32)
	set(GLAD_SOURCES ${GLAD_SOURCES} dependencies/glad/src/wgl.c)
endif()
add_library(glad ${GLAD_SOURCES})


set( IMGUI_SOURCES
                    dependencies/src/imgui/imgui.h 
                    dependencies/src/imgui/imgui.cpp 
                    dependencies/src/imgui/imgui_draw.cpp 
                    dependencies/src/imgui/imgui_tables.cpp 
                    dependencies/src/imgui/imgui_widgets.cpp
                    dependencies/src/imgui/backends/imgui_impl_glfw.cpp
                    dependencies/src/imgui/backends/imgui_impl_opengl3.cpp
                    dependencies/src/imgui/backends/imgui_impl_glfw.h
                    dependencies/src/imgui/backends/imgui_impl_opengl3.h
                    )



add_library(imgui ${IMGUI_SOURCES})




include_directories(dependencies/src/glfw/include)
include_directories(dependencies/src/SOIL2/src/SOIL2)
include_directories(dependencies/glad/include)
include_directories(dependencies/src/glm)
include_directories(dependencies/src/imgui)
include_directories(dependencies/src/physfs/src)

set_property(TARGET glfw            PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glad            PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET imgui           PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET soil2           PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET physfs-static          PROPERTY FOLDER "ThirdPartyLibraries")

SETUP_APP(fps_cmake "shooter")


target_link_libraries(fps_cmake glad glfw imgui soil2 physfs-static)
add_subdirectory(src/CommandBuffer)
