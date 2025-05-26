cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(1a2b LANGUAGES CXX)

if(MSVC)
  add_compile_options(/W4 /O2 /Ob2 /Ot /Oy /GL)
  add_link_options(/LTCG)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -O3
                      -march=native -mtune=native -flto)
  add_link_options(-flto)
endif()

# Set build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  if(MSVC)
    add_compile_definitions(NDEBUG)
    add_compile_options(/Ox /Ob2 /Oi /Ot /Oy /GT)
  else()
    add_compile_definitions(NDEBUG)
    add_compile_options(-O3 -DNDEBUG -ffast-math
                        -funroll-loops -fomit-frame-pointer)
  endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/utils UTILS_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/gameplay GAMEPLAY_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/interface INTERFACE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/solver SOLVER_SRC)

target_sources(${PROJECT_NAME}
        PRIVATE
        ${UTILS_SRC}
        ${GAMEPLAY_SRC}
        ${INTERFACE_SRC}
        ${SOLVER_SRC})

# Create main executable
add_executable(1a2b_main main.cpp)

# Link with the shared library
target_link_libraries(1a2b_main ${PROJECT_NAME})

# Set target properties
set_target_properties(1a2b_main PROPERTIES
    OUTPUT_NAME "1a2b"
)
