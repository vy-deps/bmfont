cmake_minimum_required(VERSION 3.16.5 FATAL_ERROR)
project(bmfont CXX)

add_subdirectory(3rdparty/libsquish)
add_subdirectory(3rdparty/libjpeg)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp)

add_library(libbmfont ${sources})

target_include_directories(libbmfont
  PRIVATE 3rdparty/zlib 3rdparty/libpng
  PUBLIC source
)
target_link_directories(libbmfont PUBLIC
  3rdparty/libpng/x64
  3rdparty/zlib/x64
)
target_link_libraries(libbmfont PUBLIC
  Usp10
  comctl32
  libpng16
  zlibstat
  libjpeg
  squish
)
target_compile_definitions(libbmfont PUBLIC
  -DWIN32
  -D_WINDOWS
  -DUNICODE
  -D_UNICODE)
target_link_options(libbmfont PUBLIC /LTCG /IGNORE:4099)
# set_property(TARGET bmfont PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(bmfont main.cpp source/bmfont/resource.rc)
target_link_libraries(bmfont PRIVATE libbmfont)
