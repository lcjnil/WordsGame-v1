cmake_minimum_required(VERSION 3.0)
set (CMAKE_PREFIX_PATH "/Users/nil/Qt/5.4/clang_64")

project(v3Client)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Sql Core Network)

# Tell CMake to create the helloworld executable
add_executable(v3Client WIN32 main.cpp src/service/ClientService.cpp src/service/ClientService.h src/controller/app.h src/controller/app.cpp src/model/User.cpp src/model/User.h src/model/Model.cpp src/model/Model.h src/model/Player.cpp src/model/Player.h src/model/Question.cpp src/model/Question.h src/controller/game.h src/controller/game.cpp src/controller/board.h src/controller/board.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(v3Client Qt5::Widgets)
target_link_libraries(v3Client Qt5::Core)
target_link_libraries(v3Client Qt5::Sql)
target_link_libraries(v3Client Qt5::Network)
