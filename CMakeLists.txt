cmake_minimum_required(VERSION 3.14)

project(EventFlow VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard and required properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the library target
add_library(EventFlow INTERFACE)

# Specify include directories for the library
target_include_directories(EventFlow INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install the library target
install(TARGETS EventFlow
    EXPORT EventFlowTargets
    INCLUDES DESTINATION include
)

# Install the header files
install(DIRECTORY include/
    DESTINATION include
)

# Install the exported targets
install(EXPORT EventFlowTargets
    FILE EventFlowTargets.cmake
    NAMESPACE EventFlow::
    DESTINATION lib/cmake/EventFlow
)
