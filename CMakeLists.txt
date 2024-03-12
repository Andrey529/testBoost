cmake_minimum_required(VERSION 3.18)
project(DefaultCppProgram)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74 REQUIRED COMPONENTS filesystem iostreams)
find_package(ZLIB REQUIRED)
find_package(libzip REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS} ${libzip_INCLUDE_DIRS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/my_zip.h src/my_zip.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ZLIB::ZLIB libzip::zip)
