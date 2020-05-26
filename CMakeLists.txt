cmake_minimum_required(VERSION 2.8.12)
project(ys_runtime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH 1)

# Enable multithreaded compilation in MSVC
if (MSVC)
  add_definitions(/MP)
endif()

# Configure output paths
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

# Include Paths
# include_directories("${PROJECT_SOURCE_DIR}/include/tclap-1.2.2/include")

# Source Files
file(GLOB ys_runtime_src 
    "${PROJECT_SOURCE_DIR}/src/yaoosl/runtime/*.h"
	"${PROJECT_SOURCE_DIR}/src/yaoosl/runtime/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/yaoosl/runtime/*.c"
    "${CMAKE_CURRENT_BINARY_DIR}/src/git_sha1.cpp"
)

# Get the local git revision hash and put it into a header we can use
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
configure_file("${PROJECT_SOURCE_DIR}/cmake/git_sha1.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/src/git_sha1.cpp" @ONLY)
list(APPEND ys_runtime_src "${CMAKE_CURRENT_BINARY_DIR}/src/git_sha1.cpp")


# Add packages to project
# find_package(Threads)


option(YS_BUILD_RUNTIME "BUILD RUNTIME" ON)


if (YS_BUILD_RUNTIME)
    add_compile_definitions(YAOOSL_RUNTIME)
    add_library(ys_runtime STATIC ${ys_runtime_src})
    target_include_directories(ys_runtime PUBLIC ${PROJECT_SOURCE_DIR}/src)
    target_compile_options(ys_runtime PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
    SET_TARGET_PROPERTIES(ys_runtime PROPERTIES PREFIX "")
    target_include_directories(ys_runtime PUBLIC ${PROJECT_SOURCE_DIR}/src)
endif ()