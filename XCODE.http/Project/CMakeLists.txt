cmake_minimum_required(VERSION 3.16)
project(XCODE_http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# If you installed Qt via Homebrew
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add source files
add_executable(XCODE_http
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
)

# Link against Qt6 Widgets
target_link_libraries(XCODE_http Qt6::Widgets)
