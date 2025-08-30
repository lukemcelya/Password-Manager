cmake_minimum_required(VERSION 3.20)
project(cpp_passman LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(passcore
    src/core/vault.cpp
    src/io/file_store.cpp
)

target_include_directories(passcore PUBLIC src)

add_library(appcli
    src/app/cli.cpp
)

target_include_directories(appcli PUBLIC src)
target_link_libraries(appcli PUBLIC passcore)

add_executable(pm src/main.cpp)
target_link_libraries(pm PRIVATE appcli)
