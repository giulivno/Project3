cmake_minimum_required(VERSION 3.16.3)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/lib)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/lib)

add_executable(Project3 main.cpp)
target_link_libraries(Project3 libcurl.lib)
