cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(Luxaflex DESCRIPTION "Luxaflex client")

include(FetchContent)
FetchContent_Declare(
  cpp_yyjson 
  GIT_REPOSITORY https://github.com/yosh-matsuda/cpp-yyjson
  GIT_TAG       v0.4.0 
  OVERRIDE_FIND_PACKAGE
)

find_package(PkgConfig  REQUIRED)
find_package(Threads    REQUIRED)
find_package(cpp_yyjson REQUIRED)

pkg_check_modules(deps REQUIRED IMPORTED_TARGET asio )

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(luxaflex ${SOURCES})
target_include_directories(luxaflex SYSTEM PUBLIC src )
target_link_libraries(luxaflex
        PUBLIC
        PkgConfig::deps
        cpp_yyjson::cpp_yyjson)

