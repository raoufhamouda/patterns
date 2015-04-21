cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Project setting

project(Patterns)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# header inclusion
include_directories(include)
#include_directories(src)

#Librairy setting

file(
  GLOB_RECURSE
  source_files
  src/*
  include/*
)

add_library(
  patterns 
  SHARED
  ${source_files}
)

set(needed_features
    cxx_range_for
    cxx_strong_enums
    cxx_constexpr
    cxx_auto_type)
target_compile_features(patterns PRIVATE ${needed_features})

