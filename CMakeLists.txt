cmake_minimum_required(VERSION 3.20)

project(goo_format_analyzer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(goo_format_analyzer main.cpp parse_options.cpp print_file.cpp read_file.cpp unpack_file.cpp rgb565_decode.cpp rle_decode.cpp)

install(TARGETS goo_format_analyzer RUNTIME DESTINATION bin)