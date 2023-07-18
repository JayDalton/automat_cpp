cmake_minimum_required(VERSION 3.25)

project(automat LANGUAGES CXX VERSION 0.1) 

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${BEXT_SML_INCLUDE_DIRS})

find_package(pugixml CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE pugixml::shared pugixml::pugixml)

target_sources(${PROJECT_NAME} PRIVATE
    common.hpp
    # console.cpp
    # console.h
    example01.hpp
    example02.hpp
    example03.hpp
    example04.hpp
    example05.hpp
    example06.hpp
    example07.hpp
    example08.hpp
    main.cpp
    scheduler.hpp
    scheduler2.hpp
)

