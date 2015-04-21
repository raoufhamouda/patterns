cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

#Project configuration
project(Tests)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# inclusion of observer librairy
include_directories(../include)
link_directories(../build/lib/${CMAKE_BUILD_TYPE})

#executable configuration
file(
  GLOB_RECURSE
  source_files
  src/*
)

add_executable(
  test.out
  ${source_files}
)

#link edition configuration
target_link_libraries(
  test.out
  patterns 
)

set(needed_features
    cxx_range_for
    cxx_strong_enums
    cxx_constexpr
    cxx_auto_type)
target_compile_features(test.out PRIVATE ${needed_features})

