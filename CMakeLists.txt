cmake_minimum_required(VERSION 3.8)




################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME AutoGeoTrace)
# Output Variables
set(OUTPUT_DEBUG ./autotrace___Win32_Debug/)
set(OUTPUT_REL ./autotrace___Win32_Release/)
# Folders files
set(CPP_DIR_1 ./)
set(CPP_DIR_2 ./)
set(CPP_DIR_3 ./)
set(CPP_DIR_4 ./)
set(CPP_DIR_5 ./)
set(CPP_DIR_6 ./)
set(CPP_DIR_7 ./)
set(CPP_DIR_8 ./)
set(CPP_DIR_9 ./)
set(CPP_DIR_10 ./)
set(CPP_DIR_11 ./)
set(CPP_DIR_12 ./)
set(CPP_DIR_13 ./)
set(CPP_DIR_14 ./)
set(CPP_DIR_15 ./)
set(CPP_DIR_16 ./)
set(CPP_DIR_17 ./)
set(CPP_DIR_18 ./)
set(CPP_DIR_19 ./)
set(CPP_DIR_20 ./)
set(CPP_DIR_21 ./)
set(CPP_DIR_22 ./)
set(CPP_DIR_23 ./)
set(CPP_DIR_24 ./)
set(CPP_DIR_25 ./)
set(CPP_DIR_26 ./)
set(CPP_DIR_27 ./)
set(CPP_DIR_28 ./)
set(CPP_DIR_29 ./)
set(CPP_DIR_30 ./)
set(CPP_DIR_31 ./)
set(CPP_DIR_32 ./)
set(CPP_DIR_33 ./)
set(CPP_DIR_34 ./)
set(CPP_DIR_35 ./)
set(CPP_DIR_36 ./)
set(CPP_DIR_37 ./)
set(CPP_DIR_38 ./)
set(CPP_DIR_39 ./)
set(CPP_DIR_40 ./)
set(CPP_DIR_41 ./)
set(HEADER_DIR_1 )

############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} C)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

# Definition of Macros
add_definitions(
   -D_DEBUG 
   -D_WINDOWS 
   -D_VISUALC_ 
   -DNeedFunctionPrototypes
   -DAUTOTRACE_VERSION="0.31"
   -Dinline=__inline
   -DAUTOTRACE_WEB="http://autotrace.sourceforge.net"
)

############## Artefacts Output #################
# Defines outputs , depending Debug or Release. #
#################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
endif()

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if(MSVC)
   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /EHsc")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /EHsc")
endif(MSVC)
if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

################ Files ################
#   --   Add files to project.   --   #
#######################################

file(GLOB SRC_FILES
    ${CPP_DIR_1}/*.c
    ${CPP_DIR_2}/*.c
    ${CPP_DIR_3}/*.c
    ${CPP_DIR_4}/*.c
    ${CPP_DIR_5}/*.c
    ${CPP_DIR_6}/*.c
    ${CPP_DIR_7}/*.c
    ${CPP_DIR_8}/*.c
    ${CPP_DIR_9}/*.c
    ${CPP_DIR_10}/*.c
    ${CPP_DIR_11}/*.c
    ${CPP_DIR_12}/*.c
    ${CPP_DIR_13}/*.c
    ${CPP_DIR_14}/*.c
    ${CPP_DIR_15}/*.c
    ${CPP_DIR_16}/*.c
    ${CPP_DIR_17}/*.c
    ${CPP_DIR_18}/*.c
    ${CPP_DIR_19}/*.c
    ${CPP_DIR_20}/*.c
    ${CPP_DIR_21}/*.c
    ${CPP_DIR_22}/*.c
    ${CPP_DIR_23}/*.c
    ${CPP_DIR_24}/*.c
    ${CPP_DIR_25}/*.c
    ${CPP_DIR_26}/*.c
    ${CPP_DIR_27}/*.c
    ${CPP_DIR_28}/*.c
    ${CPP_DIR_29}/*.c
    ${CPP_DIR_30}/*.c
    ${CPP_DIR_31}/*.c
    ${CPP_DIR_32}/*.c
    ${CPP_DIR_33}/*.c
    ${CPP_DIR_34}/*.c
    ${CPP_DIR_35}/*.c
    ${CPP_DIR_36}/*.c
    ${CPP_DIR_37}/*.c
    ${CPP_DIR_38}/*.c
    ${CPP_DIR_39}/*.c
    ${CPP_DIR_40}/*.c
    ${CPP_DIR_41}/*.c
    ${HEADER_DIR_1}/*.h
)

# Add executable to build.
add_executable(${PROJECT_NAME} 
   ${SRC_FILES}
)

if(MSVC)
   target_link_libraries(${PROJECT_NAME} CORE_RL_magick_.lib libming.lib odbc32.lib odbccp32.lib )
endif(MSVC)

# Bibliotecas
target_link_libraries(AutoGeoTrace m)