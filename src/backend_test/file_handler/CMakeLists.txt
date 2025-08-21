cmake_minimum_required(VERSION 3.31)
project(file_handler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)

if(EXISTS "${CMAKE_SOURCE_DIR}/deps.cmake")
  include("${CMAKE_SOURCE_DIR}/deps.cmake")
endif()

include_directories(${CMAKE_SOURCE_DIR})

find_package(absl CONFIG REQUIRED)

add_executable(file_handler
  src/file_handler.h
  src/file_handler.cc
)

target_link_libraries(file_handler PRIVATE
  absl::base
)
