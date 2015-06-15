cmake_minimum_required(VERSION 3.0)
set (CMAKE_PREFIX_PATH "/Users/nil/Qt/5.4/clang_64")

project(v2)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Sql Core Network)

# Tell CMake to create the helloworld executable
add_executable(v2 WIN32 main.cpp lib/ src/controller/ src/model src/utils)
# Use the Widgets module from Qt 5.
target_link_libraries(v2 Qt5::Widgets)

# Use the Widgets module from Qt 5.
target_link_libraries(v2 Qt5::Widgets)
target_link_libraries(v2 Qt5::Core)
target_link_libraries(v2 Qt5::Sql)
