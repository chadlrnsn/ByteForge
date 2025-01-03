cmake_minimum_required(VERSION 3.20)
project(ByteForge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories for all build artifacts
# Устанавливаем пути для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE})

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Add Windows resource file if on Windows
if(WIN32)
    list(APPEND SOURCES src/ByteForge.rc)
endif()

add_executable(ByteForge ${SOURCES})

file(GLOB_RECURSE HEADERS src/*.h)

target_include_directories(ByteForge PRIVATE src)
target_include_directories(ByteForge PRIVATE src/ProgressBar)

# Set Windows subsystem to console
if(MSVC)
    set_target_properties(ByteForge PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()
