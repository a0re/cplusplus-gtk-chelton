cmake_minimum_required(VERSION 3.1)

project(
    Chelton
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)


link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.cpp"
)

add_executable(Chelton ${SOURCES}
        src/CookieClicker.h
        src/CookieClicker.cpp
        src/Server.h
        src/Server.cpp
        src/Client.cpp
        src/Client.h
        src/StartView.cpp
        src/StartView.h



)

target_link_libraries(Chelton ${GTKMM_LIBRARIES})
