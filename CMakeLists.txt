cmake_minimum_required(VERSION 3.16)
project(SFMLApp LANGUAGES CXX)

# Set C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output binary name
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Add source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Include headers
include_directories(include)

# Add the executable
add_executable(sfml-app ${SOURCES})

# Platform-specific SFML linking
if (WIN32)
    # Use vcpkg or precompiled SFML
    find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
    target_link_libraries(sfml-app PRIVATE sfml-graphics sfml-window sfml-system)
elseif(UNIX)
    # Linux: use pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(sfml-app PRIVATE ${SFML_LIBRARIES})
endif()

