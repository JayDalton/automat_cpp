cmake_minimum_required(VERSION 3.25)

project(features LANGUAGES CXX VERSION 0.1) 

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# set( BEXT_SML_INCLUDE_DIRS "x86-windows/include/opencv" )
find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${BEXT_SML_INCLUDE_DIRS})

# # find_package(boost_statechart CONFIG REQUIRED)
# # find_package(boost_statechart CONFIG REQUIRED)
# find_package(Boost REQUIRED COMPONENTS statechart)
# target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::statechart)

target_sources(${PROJECT_NAME} PRIVATE
    common.h
    concept01.h
    concept02.h
    concept03.h
    console.cpp
    console.h
    future01.h
    main.cpp
    repo.h
    values01.h
    variant01.h
    variant02.h
    variant03.h
)

