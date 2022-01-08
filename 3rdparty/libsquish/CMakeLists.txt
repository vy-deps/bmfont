# cmake build file for squish
# by Stefan Roettger (stefan@stereofx.org)
# updated by Simon Brown (si@sjbrown.co.uk)

# features:
#   Xcode: builds universal binaries, uses SSE2 on i386 and Altivec on ppc
#   Unix and VS: SSE2 support is enabled by default
#   use BUILD_SQUISH_WITH_SSE2 and BUILD_SQUISH_WITH_ALTIVEC to override

cmake_minimum_required(VERSION 3.2)
project(squish)

option(BUILD_SQUISH_WITH_SSE2 "Build with SSE2." ON)
option(BUILD_SQUISH_WITH_ALTIVEC "Build with Altivec." OFF)
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

set(SQUISH_HDRS squish.h)

set(SQUISH_SRCS
    alpha.cpp
    alpha.h
    clusterfit.cpp
    clusterfit.h
    colourblock.cpp
    colourblock.h
    colourfit.cpp
    colourfit.h
    colourset.cpp
    colourset.h
    maths.cpp
    maths.h
    rangefit.cpp
    rangefit.h
    simd.h
    simd_float.h
    simd_sse.h
    simd_ve.h
    singlecolourfit.cpp
    singlecolourfit.h
    singlecolourlookup.inl
    squish.cpp)

add_library(squish ${SQUISH_SRCS} ${SQUISH_HDRS})

target_include_directories(squish PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(CMAKE_OSX_ARCHITECTURES "i386;ppc")
else()
    if(BUILD_SQUISH_WITH_SSE2 AND NOT WIN32)
        target_compile_options(squish PRIVATE -msse2)
        target_compile_definitions(squish PUBLIC -DSQUISH_USE_SSE=2)
    endif()
    if(BUILD_SQUISH_WITH_ALTIVEC AND NOT WIN32)
        target_compile_options(squish PRIVATE -maltivec)
        target_compile_definitions(squish PUBLIC -DSQUISH_USE_ALTIVEC=1)
    endif()
endif()

set_target_properties(squish PROPERTIES
    PUBLIC_HEADER "${SQUISH_HDRS}"
    VERSION 0.0
    SOVERSION 0.0
    DEBUG_POSTFIX "d"
    XCODE_ATTRIBUTE_GCC_PREPROCESSOR_DEFINITIONS "$(SQUISH_CPP_$(CURRENT_ARCH))"
    XCODE_ATTRIBUTE_OTHER_CFLAGS "$(SQUISH_CFLAGS_$(CURRENT_ARCH))"
    XCODE_ATTRIBUTE_SQUISH_CPP_i386 "SQUISH_USE_SSE=2"
    XCODE_ATTRIBUTE_SQUISH_CFLAGS_i386 ""
    XCODE_ATTRIBUTE_SQUISH_CPP_ppc "SQUISH_USE_ALTIVEC=1"
    XCODE_ATTRIBUTE_SQUISH_CFLAGS_ppc "-maltivec")
