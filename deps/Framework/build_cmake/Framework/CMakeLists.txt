cmake_minimum_required(VERSION 3.1)
project(Framework)

include(../Framework_Common.cmake)


if(NOT TARGET libzstd_zlibwrapper_static)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/build_cmake/zstd_zlibwrapper
		${CMAKE_CURRENT_BINARY_DIR}/zstd_zlibwrapper
	)
endif()
LIST(APPEND PROJECT_LIBS libzstd_zlibwrapper_static)

set(COMMON_SRC_FILES
	../../src/Base64.cpp
	../../src/bitmap/Bitmap.cpp
	../../src/bitmap/BMP.cpp
	../../src/bitmap/JPEG.cpp
	../../src/bitmap/PNG.cpp
	../../src/bitmap/TGA.cpp
	../../src/BitStream.cpp
	../../src/Config.cpp
	../../src/Csv.cpp
	../../src/FilesystemUtils.cpp
	../../src/HashUtils.cpp
	../../src/idct/IEEE1180.cpp
	../../src/layout/FlatLayout.cpp
	../../src/layout/GridLayout.cpp
	../../src/layout/HorizontalLayout.cpp
	../../src/layout/LayoutBase.cpp
	../../src/layout/LayoutBaseItem.cpp
	../../src/layout/LayoutObject.cpp
	../../src/layout/LayoutStretch.cpp
	../../src/layout/VerticalLayout.cpp
	../../src/LzAri.cpp
	../../src/math/MathStringUtils.cpp
	../../src/MemStream.cpp
	../../src/mpeg2/CodedBlockPatternTable.cpp
	../../src/mpeg2/DcSizeChrominanceTable.cpp
	../../src/mpeg2/DcSizeLuminanceTable.cpp
	../../src/mpeg2/DctCoefficientTable.cpp
	../../src/mpeg2/DctCoefficientTable0.cpp
	../../src/mpeg2/DctCoefficientTable1.cpp
	../../src/mpeg2/InverseScanTable.cpp
	../../src/mpeg2/MacroblockAddressIncrementTable.cpp
	../../src/mpeg2/MacroblockTypeBTable.cpp
	../../src/mpeg2/MacroblockTypeITable.cpp
	../../src/mpeg2/MacroblockTypePTable.cpp
	../../src/mpeg2/MotionCodeTable.cpp
	../../src/mpeg2/QuantiserScaleTable.cpp
	../../src/mpeg2/VLCTable.cpp
	../../src/PathUtils.cpp
	../../src/PtrStream.cpp
	../../src/Stream.cpp
	../../src/StreamBitStream.cpp
	../../src/StringUtils.cpp
	../../src/string_cast.cpp
	../../src/string_cast_sjis.cpp
	../../src/string_cast_win1252.cpp
	../../src/StdStream.cpp
	../../src/StdStreamUtils.cpp
	../../src/ThreadPool.cpp
	../../src/Url.cpp
	../../src/Utf8.cpp
	../../src/xml/FilteringNodeIterator.cpp
	../../src/xml/Node.cpp
	../../src/xml/Parser.cpp
	../../src/xml/Utils.cpp
	../../src/xml/Writer.cpp
	../../src/zip/ZipArchiveReader.cpp
	../../src/zip/ZipArchiveWriter.cpp
	../../src/zip/ZipDeflateStream.cpp
	../../src/zip/ZipFile.cpp
	../../src/zip/ZipInflateStream.cpp
	../../src/zip/ZipStoreStream.cpp

	../../include/BitManip.h
	../../include/Csv.h
	../../include/EndianUtils.h
	../../include/filesystem_def.h
	../../include/FilesystemUtils.h
	../../include/HashUtils.h
	../../include/layout/FlatLayout.h
	../../include/layout/GridLayout.h
	../../include/layout/HorizontalLayout.h
	../../include/layout/LayoutBase.h
	../../include/layout/LayoutBaseItem.h
	../../include/layout/LayoutObject.h
	../../include/layout/LayoutStretch.h
	../../include/layout/VerticalLayout.h
	../../include/maybe_unused.h
	../../include/nodiscard.h
	../../include/signal/Signal.h
	../../include/Singleton.h
	../../include/StringUtils.h
	../../include/std_experimental_map.h
	../../include/std_experimental_set.h
	../../include/ThreadPool.h
	../../include/Url.h
	../../include/Utf8.h
	../../include/zip/ZipArchiveReader.h
	../../include/zip/ZipArchiveWriter.h
	../../include/zip/ZipDeflateStream.h
	../../include/zip/ZipFile.h
	../../include/zip/ZipInflateStream.h
	../../include/zip/ZipStoreStream.h
)

add_library(Framework ${COMMON_SRC_FILES} ${PLATFORM_SRC_FILES})
target_link_libraries(Framework PUBLIC ${PROJECT_LIBS} PRIVATE ${PRIVATE_PROJECT_LIBS})
target_include_directories(Framework PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${PROJECT_INCLUDES})
