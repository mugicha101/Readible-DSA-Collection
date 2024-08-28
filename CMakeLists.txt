cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE src CONFIGURE_DEPENDS "src/*.cpp")
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
add_executable(app ${src})
target_link_libraries( app ${CURSES_LIBRARIES} )
target_compile_features(app PRIVATE cxx_std_20)
target_compile_options(app PRIVATE -lncurses -DNCURSES_STATIC)
add_compile_definitions(_USE_MATH_DEFINES)

install(TARGETS app)