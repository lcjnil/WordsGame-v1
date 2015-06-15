cmake_minimum_required(VERSION 3.0)
set (CMAKE_PREFIX_PATH "/Users/nil/Qt/5.4/clang_64")

project(WordsGame)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Sql Core Network)

# Tell CMake to create the helloworld executable
add_executable(WordsGame WIN32 main.cpp lib/ src/ src/model/Player.cpp src/model/Player.h src/model/Referee.cpp src/model/Referee.h src/model/Question.cpp src/model/Question.h src/controller/board.cpp src/controller/board.h)
# Use the Widgets module from Qt 5.
target_link_libraries(WordsGame Qt5::Widgets)

# Use the Widgets module from Qt 5.
target_link_libraries(WordsGame Qt5::Widgets)
target_link_libraries(WordsGame Qt5::Core)
target_link_libraries(WordsGame Qt5::Sql)
