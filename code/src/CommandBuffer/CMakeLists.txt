cmake_minimum_required(VERSION 3.12)

file(GLOB SRC_FILES    CONFIGURE_DEPENDS "*.h" "*.cpp")
target_sources(fps_cmake PRIVATE ${SRC_FILES})
