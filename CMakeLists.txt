cmake_minimum_required(VERSION 3.20)

project(double_stack LANGUAGES CXX)

add_library(double_stack INTERFACE)

target_compile_features(double_stack INTERFACE cxx_std_23)

set_target_properties(double_stack PROPERTIES
    INTERFACE_CXX_EXTENSIONS NO
)

target_include_directories(double_stack INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources(double_stack INTERFACE
    include/double_stack.hpp
    include/double_stack.tpp
)
