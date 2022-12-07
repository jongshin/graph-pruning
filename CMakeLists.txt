cmake_minimum_required ( VERSION 3.13 )

# Definitions
set(PROJECT_NAME_STR MyStatPhys)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project ( ${PROJECT_NAME_STR} )

set ( PROJECT_VERSION_YEAR 22 )
set ( PROJECT_VERSION_MONTH 10 )
set ( PROJECT_VERSION_DATE 31 )

set ( OUTPUT_LIBRARY "${CMAKE_PROJECT_NAME}" )
set ( OUTPUT_ELF "ER_kq_core_Percolation.out" )

# Build configurations
if(NOT CMAKE_BUILD_TYPE)
    set ( CMAKE_BUILD_TYPE "Debug" )
endif()

set ( CMAKE_CXX_FLAGS_DEBUG "-g -D_GLIBCXX_DEBUG -Wall" )
set ( CMAKE_CXX_FLAGS_RELEASE "-O3" )

# set ( CMAKE_VERBOSE_MAKEFILE true )
set ( CMAKE_CXX_STANDARD 20 )


# BUILD OPTIONS
option ( MYLIB_NATIVE "Optimize for native architecture (often better performance)" OFF )
option ( MYLIB_BUILD_WARNINGS "Issue more warnings" OFF )
option ( MYLIB_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF )
set ( MYLIB_WITH_SANITIZERS "" CACHE STRING "Uses sanitizers during the compilation" )

set ( MYLIB_CXX_FLAGS "")

if ( MYLIB_NATIVE )
    set( MYLIB_CXX_FLAGS "${MYLIB_CXX_FLAGS} -march=native" )
endif()
if ( MYLIB_BUILD_WARNINGS )
    set( MYLIB_CXX_FLAGS "${MYLIB_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unknown-pragmas" )
endif()
if ( MYLIB_WARNINGS_AS_ERRORS )
    set( MYLIB_CXX_FLAGS "${MYLIB_CXX_FLAGS} -Werror" )
endif()


# Checking sanitizer options; in both cases we include 'undefined'
set( MYLIB_CXX_SANITIZERS "" )
if ( "${MYLIB_WITH_SANITIZERS}" STREQUAL "address" )
	set( MYLIB_CXX_SANITIZERS "address,undefined" )
elseif ( "${MYLIB_WITH_SANITIZERS}" STREQUAL "leak" )
	set( MYLIB_CXX_SANITIZERS "address,leak,undefined" )
elseif( NOT "${MYLIB_WITH_SANITIZERS}" STREQUAL "" )
	message(FATAL_ERROR "Unsupported option ${MYLIB_WITH_SANITIZERS}")
endif()


# List of directories of common header files (-I).
include_directories(
    # /opt/intel/mkl/include
    mylib/include
    mylib/include/mylib

    /usr/local
    /usr/local/include
)

# Common compile and link options
# add_compile_options( ${MYLIB_CXX_FLAGS} )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYLIB_CXX_FLAGS} ${MYLIB_CXX_SANITIZERS}")

# Common link libraries (-l)
# link_libraries ( boost_unit_test_framework )

add_library( ${OUTPUT_LIBRARY} STATIC )
add_subdirectory( mylib/cpp )
add_subdirectory( src )

# # BUILD OPTIONS
# option(PRUNING_DEBUG "Set debug mode as build type." OFF)
# option(PRUNING_NATIVE "Optimize for native architecture (often better performance)" OFF)
# option(PRUNING_BUILD_WARNINGS "Issue more warnings" OFF)
# option(PRUNING_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
# set(PRUNING_WITH_SANITIZERS "" CACHE STRING "Uses sanitizers during the compilation")
# set(PRUNING_CXX_STANDARD "20" CACHE STRING "CXX Version to compile with. Currently fixed to 20")

# if(NOT CMAKE_BUILD_TYPE)
#     message("Use Release Build Type as default")
#     set(CMAKE_BUILD_TYPE "Release")
#     message("Add full compiler optimization when in the release build type")
# endif()
    
# # Allow user to set installation paths relative to CMAKE_INSTALL_PREFIX
# set(PRUNING_BINARY_DIR "./bin"
# 	CACHE PATH "Installation directory for executables")

# # Compilation Flags
# set(PRUNING_CXX_FLAGS "")
# set(PRUNING_LINK_FLAGS "")

# if (PRUNING_DEBUG)
#     set(CMAKE_BUILD_TYPE "Debug")
#     message("Add debugging flag for tools such as gdb and valgrind.")
#     set(CMAKE_CXX_FLAGS_DEBUG "-g -D_GLIBCXX_DEBUG -Wall")
# endif()
# if (PRUNING_NATIVE)
#     set(PRUNING_CXX_FLAGS "${PRUNING_CXX_FLAGS} -march=native")
# endif()
# if (PRUNING_BUILD_WARNINGS)
#     set(PRUNING_CXX_FLAGS "${PRUNING_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unknown-pragmas")
# endif()
# if (PRUNING_WARNINGS_AS_ERRORS)
#     set(PRUNING_CXX_FLAGS "${PRUNING_CXX_FLAGS} -Werror")
# endif()

# if(CMAKE_BUILD_TYPE STREQUAL "Release")
#     message("Add full compiler optimization when in the release build type")
#     set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# endif()

# # Checking sanitizer options; in both cases we include 'undefined'
# set(PRUNING_CXX_SANITIZERS "")
# if ("${PRUNING_WITH_SANITIZERS}" STREQUAL "address")
# 	set(PRUNING_CXX_SANITIZERS "address,undefined")
# elseif ("${PRUNING_WITH_SANITIZERS}" STREQUAL "leak")
# 	set(PRUNING_CXX_SANITIZERS "address,leak,undefined")
# elseif(NOT "${PRUNING_WITH_SANITIZERS}" STREQUAL "")
# 	message(FATAL_ERROR "Unsupported option ${PRUNING_WITH_SANITIZERS}")
# endif()

# # finding or creating OpenMP target. This is likely to fail for CMake Version < 3.12.
# find_package(OpenMP)
# # if (OPENMP_FOUND)
# #     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# #     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# #     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# # endif()

# # Add directories containing header-files
# include_directories(
#     # /opt/intel/mkl/include
#     mylib/include
#     mylib/include/mylib

#     /usr/local
#     /usr/local/include
# )
# if (NOT PRUNING_DEBUG)
#     message("Compile flags:${PRUNING_CXX_FLAGS}")
#     add_compile_options( "${PRUNING_CXX_FLAGS}" )
# endif()
# # link_libraries ( boost_program_options )

# add_executable( ${OUTPUT_ELF} )

# add_subdirectory( src )
# add_subdirectory( mylib/cpp )

            