cmake_minimum_required(VERSION 3.0)
set (CMAKE_PREFIX_PATH "/Users/nil/Qt/5.4/clang_64")

project(v3Server)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Sql Core Network)

# Tell CMake to create the helloworld executable
add_executable(v3Server WIN32 main.cpp src/service/ServerService.cpp src/service/ServerService.h src/controller/Server.cpp src/controller/Server.h src/model/Connection.h src/model/Connection.cpp src/model/User.h src/model/User.cpp src/model/Player.h src/model/Player.cpp src/model/Referee.h src/model/Referee.cpp src/model/Question.h src/model/Question.cpp  src/util/Console.h src/util/Console.cpp )

# Use the Widgets module from Qt 5.
target_link_libraries(v3Server Qt5::Widgets)
target_link_libraries(v3Server Qt5::Core)
target_link_libraries(v3Server Qt5::Sql)
target_link_libraries(v3Server Qt5::Network)
