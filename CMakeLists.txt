cmake_minimum_required(VERSION 3.15)
project(cpp_app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/exe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ffast-math -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mtune=native -march=native -mfpmath=both -ffast-math -DNDEBUG -s")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -ffast-math -DNDEBUG -s")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -ffast-math -DNDEBUG -g")


include(GNUInstallDirs)
set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/deps/Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)
include(Header)

set(PROJECT_LIBS)


include(PrecompiledHeader)
add_subdirectory(src/main/)

