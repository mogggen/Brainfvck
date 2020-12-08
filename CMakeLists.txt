cmake_minimum_required(VERSION 3.6)
project(BF-compiler)
add_executable(app "BF-compiler.cpp")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app)