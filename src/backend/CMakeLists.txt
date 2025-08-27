cmake_minimum_required(VERSION 3.28)
project(pointer LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)

if(EXISTS "${CMAKE_SOURCE_DIR}/deps.cmake")
  include("${CMAKE_SOURCE_DIR}/deps.cmake")
endif()

include_directories(${CMAKE_SOURCE_DIR})

find_package(absl CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_library(pointer STATIC
  src/file_handler/file_handler.h
  src/file_handler/file_handler.cc
  src/path_handler/path_handler.h
  src/path_handler/path_handler.cc
  src/utils/utils.h
  src/utils/utils.cc
)

target_link_libraries(pointer PRIVATE
  absl::base
  absl::log
)

include(CTest)
if(BUILD_TESTING)
  add_executable(file_handler_test
    src/file_handler/file_handler_test.cc
  )
  target_link_libraries(file_handler_test PRIVATE
    pointer
    absl::base
    absl::log
    GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(file_handler_test)
endif()
