project(crc32c)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(src)

enable_testing()

add_executable(check
    test/main.cpp
    test/crc32c_sctp.c)
target_include_directories(check PUBLIC src)
target_link_libraries(check crc32c)

add_test(NAME "sanity check" COMMAND check)
