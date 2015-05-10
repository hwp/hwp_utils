# Author : Weipeng He <heweipeng@gmail.com>
# Copyright (c) 2015, All rights reserved.

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

project(hwp_utils)

set(PACKAGE "hwp_utils")
set(PACKAGE_NAME "HWP Utils")
set(PACKAGE_VERSION "1.0.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_URL "http://www.github.com/hwp/hwp_utils")

set(CMAKE_C_FLAGS "-Wall")
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

if(UNIX)
  configure_file(${CMAKE_SOURCE_DIR}/${PACKAGE}.pc.cmake.in
    ${CMAKE_BINARY_DIR}/${PACKAGE}.pc @ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/${PACKAGE}.pc
    DESTINATION lib/pkgconfig)
endif()

