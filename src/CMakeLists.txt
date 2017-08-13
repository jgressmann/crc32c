project(crc32c)
cmake_minimum_required(VERSION 2.8)

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.2)")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")


set(CPACK_PACKAGE_NAME "crc32c")
set(CPACK_PACKAGE_CONTACT "Jean Gressmann <jean@0x42.de>")
set(CPACK_PACKAGE_VENDOR "Jean Gressmann")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "High performance crc32c library with minimal dependencies")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_GENERATOR "DEB")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo" OR "${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    add_definitions(-DNDEBUG)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    execute_process(COMMAND uname -a OUTPUT_VARIABLE ARCH)
    message(STATUS "ARCH ${ARCH}")
endif()

add_definitions(-DPIC)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables")
    if("${ARCH}" MATCHES "x86_64" OR "${ARCH}" MATCHES "i686")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -mcrc32")
    endif()
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -nostdlib -lc")
endif()


add_library(crc32c SHARED
    crc32c.cc
    stdlib.cc
    interface.cc
    crc32c_sse4.cc
    multiword_128_64_gcc_amd64_sse2.cc
    multiword_64_64_cl_i386_mmx.cc
    multiword_64_64_gcc_amd64_asm.cc
    multiword_64_64_gcc_i386_mmx.cc
    multiword_64_64_intrinsic_i386_mmx.cc
)


install(TARGETS crc32c DESTINATION lib)
install(FILES crc32c.h DESTINATION include)


include(${CMAKE_ROOT}/Modules/CPack.cmake)



