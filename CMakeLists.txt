cmake_minimum_required(VERSION 3.31)

project(1a2b LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler options based on platform and build type
if(MSVC)
  # Base options for MSVC
  add_compile_options(/W4)
  
  # Release-specific options for MSVC
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(/O2 /Ob2 /Oi /Ot /Oy /GL /GT)
    add_compile_definitions(NDEBUG)
    add_link_options(/LTCG)
  endif()
else()
  # Base options for GCC/Clang
  add_compile_options(-Wall -Wextra -Wpedantic)
  
  # Release-specific options for GCC/Clang
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -march=native -mtune=native -flto -ffast-math 
                        -funroll-loops -fomit-frame-pointer)
    add_compile_definitions(NDEBUG)
    add_link_options(-flto)
  endif()
endif()

# Create library (static on Windows, shared elsewhere)
if(WIN32)
    add_library(${PROJECT_NAME} STATIC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
else()
    add_library(${PROJECT_NAME} SHARED)
endif()

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Collect source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/utils UTILS_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/gameplay GAMEPLAY_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/interface INTERFACE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/solver SOLVER_SRC)

# Add sources to library target
target_sources(${PROJECT_NAME}
    PRIVATE
    ${UTILS_SRC}
    ${GAMEPLAY_SRC}
    ${INTERFACE_SRC}
    ${SOLVER_SRC}
)

# Create main executable
add_executable(1a2b_main main.cpp)

# Link with the library
target_link_libraries(1a2b_main ${PROJECT_NAME})

# Set executable name
set_target_properties(1a2b_main PROPERTIES
    OUTPUT_NAME "1a2b"
)
