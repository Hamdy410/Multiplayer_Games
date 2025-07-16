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

# Version-specific component names
# SFML 3.0+ uses capitalized names, 2.x uses lowercase
function(find_sfml_with_version_detection)
    # Try SFML 3.x first with capitalized component names
    find_package(SFML 3 COMPONENTS System Window Graphics QUIET)
    if(SFML_FOUND)
        message(STATUS "Found SFML 3.x with capitalized components")
        set(SFML_FOUND ${SFML_FOUND} PARENT_SCOPE)
        return()
    endif()
    
    # Try SFML 2.6+ with lowercase component names
    find_package(SFML 2.6 COMPONENTS system window graphics QUIET)
    if(SFML_FOUND)
        message(STATUS "Found SFML 2.6+ with lowercase components")
        set(SFML_FOUND ${SFML_FOUND} PARENT_SCOPE)
        return()
    endif()
    
    # Try SFML 2.5 with lowercase component names
    find_package(SFML 2.5 COMPONENTS system window graphics QUIET)
    if(SFML_FOUND)
        message(STATUS "Found SFML 2.5 with lowercase components")
        set(SFML_FOUND ${SFML_FOUND} PARENT_SCOPE)
        return()
    endif()
    
    # Final attempt without version specification
    find_package(SFML COMPONENTS system window graphics QUIET)
    if(SFML_FOUND)
        message(STATUS "Found SFML (version detection failed) with lowercase components")
        set(SFML_FOUND ${SFML_FOUND} PARENT_SCOPE)
        return()
    endif()
    
    # If all else fails, try capitalized components without version
    find_package(SFML COMPONENTS System Window Graphics REQUIRED)
    if(SFML_FOUND)
        message(STATUS "Found SFML (version detection failed) with capitalized components")
        set(SFML_FOUND ${SFML_FOUND} PARENT_SCOPE)
    endif()
endfunction()

# Find SFML with version detection
find_sfml_with_version_detection()

# Include headers
include_directories(include)

# Source files from multiple directories
file(GLOB_RECURSE SOURCES 
    "src/core/*.cpp"
    "src/ui/*.cpp"
    "src/games/*.cpp"
    "src/states/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Copy the entire assets directory to the build output
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets
    COMMENT "Copying assets to output directory"
)

# Version-specific linking
if(SFML_VERSION_MAJOR EQUAL 3)
    message(STATUS "Configuring for SFML 3.x")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
    )
    set(SFML_MODERN_TARGETS TRUE)
    
elseif(SFML_VERSION_MAJOR EQUAL 2 AND SFML_VERSION_MINOR GREATER_EQUAL 6)
    message(STATUS "Configuring for SFML 2.6+")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
    )
    set(SFML_MODERN_TARGETS TRUE)
    
elseif(SFML_VERSION_MAJOR EQUAL 2 AND SFML_VERSION_MINOR EQUAL 5)
    message(STATUS "Configuring for SFML 2.5")
    if(TARGET SFML::System)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            SFML::System
            SFML::Window
            SFML::Graphics
        )
        set(SFML_MODERN_TARGETS TRUE)
    else()
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            sfml-system
            sfml-window
            sfml-graphics
        )
        set(SFML_MODERN_TARGETS FALSE)
    endif()
    
else()
    message(WARNING "Unknown SFML version, attempting modern targets")
    if(TARGET SFML::System)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            SFML::System
            SFML::Window
            SFML::Graphics
        )
        set(SFML_MODERN_TARGETS TRUE)
    else()
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            sfml-system
            sfml-window
            sfml-graphics
        )
        set(SFML_MODERN_TARGETS FALSE)
    endif()
endif()

# Windows-specific configuration
if(WIN32)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )

    # Version-specific DLL handling
    if(SFML_MODERN_TARGETS)
        add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SFML::System> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SFML::Window> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SFML::Graphics> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        )
    else()
        add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        )
    endif()

    if(MINGW)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE -mwindows)
    endif()

    if(MSVC)
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
    endif()
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

# Debug information
message(STATUS "SFML Version: ${SFML_VERSION_MAJOR}.${SFML_VERSION_MINOR}.${SFML_VERSION_PATCH}")
message(STATUS "Using modern SFML targets: ${SFML_MODERN_TARGETS}")
