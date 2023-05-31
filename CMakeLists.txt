cmake_minimum_required(VERSION 3.25)

project(automat LANGUAGES CXX VERSION 0.1) 

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${BEXT_SML_INCLUDE_DIRS})

target_sources(${PROJECT_NAME} PRIVATE
    # common.h
    # console.cpp
    # console.h
    main.cpp
)

