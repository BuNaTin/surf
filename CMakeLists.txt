cmake_minimum_required(VERSION 3.16)

project(exe)
set(Project exe)

OPTION(STATIC_ANALYS "Use clang-tidy" OFF)
IF(STATIC_ANALYS)
    message("Use clang-tidy enabled")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
ELSE()
    message("Default build")
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (WIN32)
  # set stuff for windows
ELSE()
# compilers flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-function -Wno-error=unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-terminate -Wno-error=maybe-uninitialized -Wno-error=literal-suffix -O3")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static -Wall -Wextra -pedantic -Wnull-dereference")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wduplicated-cond -Wduplicated-branches")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wlogical-op -Wnon-virtual-dtor -O3")
ENDIF()

include_directories(
    ${CMAKE_SOURCE_DIR}/core/includes
)

add_subdirectory(core)

add_subdirectory(console)
