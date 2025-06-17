cmake_minimum_required(VERSION 3.15)
project(SFML-App LANGUAGES CXX)

set(EXECUTABLE_NAME sfml-app)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Include headers
include_directories(include)

# Source files from multiple directories
file(GLOB_RECURSE SOURCES 
    "src/core/*.cpp"
    "src/ui/*.cpp"
    "src/games/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)

# Copy all assets recursively
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets
)

# Windows DLL handling
if(WIN32)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
    )
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()

# macOS bundle configuration
if(APPLE)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        MACOSX_BUNDLE ON
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist
    )
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/assets
            $<TARGET_BUNDLE_DIR:${EXECUTABLE_NAME}>/Contents/Resources
    )
endif()

# Optimize file globbing
set_source_files_properties(${SOURCES} PROPERTIES SKIP_UNITY_BUILD ON)

