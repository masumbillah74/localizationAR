# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project("aoa_locator_cl" VERSION 0.1)

set(NRF_SUPPORTED_BUILD_TYPES
  ZDebug
  ZRelease
  )

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ZDebug)
endif()

zephyr_compile_definitions(
   ARM_MATH_CM4
)

zephyr_include_directories(
    .
 )

target_sources(app PRIVATE src/main.c
	src/if.c
	src/protocol.c
	src/ble.c
	src/dfe_local_config.c
)

target_include_directories(app PRIVATE $ENV{ZEPHYR_BASE}/samples/bluetooth)
target_include_directories(app PRIVATE $ENV{ZEPHYR_BASE}/subsys/bluetooth/controller)
