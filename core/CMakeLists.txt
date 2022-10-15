cmake_minimum_required(VERSION 3.16)

set(CORE_LIB Surf-core)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(PUBLIC_INCLUDES
    ${INC_DIR}/Application/Args.h
    ${INC_DIR}/types.h
    ${INC_DIR}/Fst.h
)

set(PRIVATE_INCLUDES
    ${SRC_DIR}/PrefixTree/Tree.h
    ${SRC_DIR}/Louds/Dense.h
)

set(PRIVATE_SOURCES
    ${SRC_DIR}/Application/Args.cpp
    ${SRC_DIR}/PrefixTree/Tree.cpp
    ${SRC_DIR}/Louds/Dense.cpp
    ${SRC_DIR}/Fst.cpp
)

set(SOURCES
    ${PUBLIC_INCLUDES}
    ${PRIVATE_INCLUDES}
    ${PRIVATE_SOURCES}
)

include_directories(
    ${SRC_DIR}
    ${INC_DIR}
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(ThreadLib
    Threads::Threads
)

set(AllLibs
    ${ThreadLib}
)

add_library(${CORE_LIB}
    STATIC
    ${SOURCES}
)

target_link_libraries(${CORE_LIB}
    ${AllLibs}
)
