Cmake_minimum_required(VERSION 3.8)
project(WriteReadToSharedResource VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Control)

add_executable(WriteReadToSharedResource  main.cpp)
target_link_libraries(WriteReadToSharedResource PUBLIC Control)
target_include_directories(WriteReadToSharedResource PUBLIC
                       	  "${PROJECT_BINARY_DIR}"
			  "${PROJECT_SOURCE_DIR}/Control"
                          )