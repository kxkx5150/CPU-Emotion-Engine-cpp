cmake_minimum_required(VERSION 3.0)

project(libzstdwapper C)

find_package(ZLIB)


set(ZSTD_BUILD_STATIC ON)
set(ZSTD_BUILD_SHARED  OFF)
set(ZSTD_BUILD_PROGRAMS OFF)
set(ZSTD_BUILD_TESTS_default  OFF)

find_package(PkgConfig QUIET)
pkg_check_modules(ZSTD REQUIRED libzstd)


file(GLOB zstd_zlibwrapperSource ${CMAKE_CURRENT_SOURCE_DIR}/../../zlibWrapper/*.c)
add_library(libzstd_zlibwrapper_static STATIC ${zstd_zlibwrapperSource})
target_link_libraries(libzstd_zlibwrapper_static PRIVATE ${ZSTD_LIBRARIES} PUBLIC ZLIB::ZLIB)
target_include_directories(libzstd_zlibwrapper_static PUBLIC ${PC_ZSTD_INCLUDEDIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../zlibWrapper/)
target_compile_definitions(libzstd_zlibwrapper_static PUBLIC ZWRAP_USE_ZSTD)