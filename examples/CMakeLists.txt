cmake_minimum_required(VERSION 3.14)

project(EventFlowExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find and import the EventFlow library
find_package(EventFlow REQUIRED)

# Create an executable target for the example
add_executable(EventFlowExample example.cpp)

# Link the EventFlow library to the example target
target_link_libraries(EventFlowExample PRIVATE EventFlow::EventFlow)
