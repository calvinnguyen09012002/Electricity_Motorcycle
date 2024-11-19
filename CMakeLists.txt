cmake_minimum_required(VERSION 2.8.9)
project (electricity_motorcycle_app)

include_directories(include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

set(SOURCES 
    main.cpp 
    src/electricity_motorcycle.cpp
)

add_executable(electricity_motorcycle_app ${SOURCES})

target_link_libraries(electricity_motorcycle_app pthread ${CURSES_LIBRARIES})