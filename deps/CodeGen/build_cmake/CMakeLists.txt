cmake_minimum_required(VERSION 3.0)
project(CodeGen)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release"
		FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../Framework/build_cmake/Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()

add_library(CodeGen 
	# ../src/AArch32Assembler.cpp
	# ../src/AArch64Assembler.cpp
	../src/CoffObjectFile.cpp
	# ../src/Jitter_CodeGen_AArch32.cpp
	# ../src/Jitter_CodeGen_AArch32_64.cpp
	# ../src/Jitter_CodeGen_AArch32_Div.h
	# ../src/Jitter_CodeGen_AArch32_Fpu.cpp
	# ../src/Jitter_CodeGen_AArch32_Md.cpp
	# ../src/Jitter_CodeGen_AArch64.cpp
	# ../src/Jitter_CodeGen_AArch64_64.cpp
	# ../src/Jitter_CodeGen_AArch64_Fpu.cpp
	# ../src/Jitter_CodeGen_AArch64_Md.cpp
	../src/Jitter_CodeGen_x86_32.cpp
	../src/Jitter_CodeGen_x86_64.cpp
	../src/Jitter_CodeGen_x86.cpp
	../src/Jitter_CodeGen_x86_Alu.h
	../src/Jitter_CodeGen_x86_Div.h
	../src/Jitter_CodeGen_x86_Fpu.cpp
	../src/Jitter_CodeGen_x86_Fpu_Avx.cpp
	../src/Jitter_CodeGen_x86_Fpu_Sse.cpp
	../src/Jitter_CodeGen_x86_Md.cpp
	../src/Jitter_CodeGen_x86_Md_Avx.cpp
	../src/Jitter_CodeGen_x86_Mul.h
	../src/Jitter_CodeGen_x86_Shift.h
	# ../src/Jitter_CodeGen_Wasm.cpp
	# ../src/Jitter_CodeGen_Wasm_64.cpp
	# ../src/Jitter_CodeGen_Wasm_Fpu.cpp
	# ../src/Jitter_CodeGen_Wasm_Md.cpp
	../src/Jitter_CodeGen.cpp
	../src/Jitter_CodeGenFactory.cpp
	../src/Jitter.cpp
	../src/Jitter_Optimize.cpp
	../src/Jitter_RegAlloc.cpp
	../src/Jitter_Statement.cpp
	../src/Jitter_SymbolTable.cpp
	../src/LiteralPool.cpp
	../src/MachoObjectFile.cpp
	../src/MemoryFunction.cpp
	../src/ObjectFile.cpp
	# ../src/WasmModuleBuilder.cpp
	../src/X86Assembler.cpp
	../src/X86Assembler_Avx.cpp
	../src/X86Assembler_Fpu.cpp
	../src/X86Assembler_Sse.cpp

	# ../include/AArch32Assembler.h
	# ../include/AArch64Assembler.h
	../include/ArrayStack.h
	../include/CoffDefs.h
	../include/CoffObjectFile.h
	# ../include/Jitter_CodeGen_AArch32.h
	# ../include/Jitter_CodeGen_AArch64.h
	# ../include/Jitter_CodeGen_Wasm.h
	../include/Jitter_CodeGen_x86_32.h
	../include/Jitter_CodeGen_x86_64.h
	../include/Jitter_CodeGen_x86.h
	../include/Jitter_CodeGen.h
	../include/Jitter_CodeGenFactory.h
	../include/Jitter_Statement.h
	../include/Jitter_Symbol.h
	../include/Jitter_SymbolRef.h
	../include/Jitter_SymbolTable.h
	../include/Jitter.h
	../include/Literal128.h
	../include/LiteralPool.h
	../include/MachoDefs.h
	../include/MachoObjectFile.h
	../include/MemoryFunction.h
	../include/ObjectFile.h
	# ../include/WasmDefs.h
	# ../include/WasmModuleBuilder.h
	../include/X86Assembler.h
)

target_link_libraries(CodeGen PUBLIC Framework ${PROJECT_LIBS})
target_include_directories(CodeGen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
enable_testing()
