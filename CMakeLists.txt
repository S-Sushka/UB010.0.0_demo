# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(UB010.0.1_demo)

target_include_directories(app PRIVATE inc)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE 
    ${ZEPHYR_BASE}/../modules/debug/segger/SEGGER/SEGGER_RTT_printf.c
    ${app_sources}
)
