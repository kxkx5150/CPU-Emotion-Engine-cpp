cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../deps/Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)
include(Header)
project(PlayUI)


if(NOT TARGET PlayCore)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../
		${CMAKE_CURRENT_BINARY_DIR}/Source
	)
endif()
list(APPEND PROJECT_LIBS PlayCore)

if(NOT TARGET gsh_opengl)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../gs/GSH_OpenGL
		${CMAKE_CURRENT_BINARY_DIR}/gs/GSH_OpenGL
	)
endif()
list(INSERT PROJECT_LIBS 0 gsh_opengl)


set(QT_SOURCES
	main.cpp
	GSH_OpenGLSDL.cpp
	GSH_OpenGLSDL.h
	Ps2VmSDL2.cpp
	Ps2VmSDL2.h
	InputProviderQtKey.cpp
	InputProviderQtKey.h
)		


add_executable(cpp_app ${QT_SOURCES})
find_package(OpenGL)
target_link_libraries(cpp_app ${PROJECT_LIBS} SDL2_image SDL2_ttf SDL2 SDL2main)
target_include_directories(cpp_app PRIVATE
	./
	../../
	${LIBEVDEV_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)


