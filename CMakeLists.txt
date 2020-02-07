cmake_minimum_required(VERSION 3.7)
project(test)

set(CMAKE_BUILD_TYPE Release)
find_package(cpprestsdk REQUIRED)

file(GLOB SOURCES src/*.cpp)
include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)