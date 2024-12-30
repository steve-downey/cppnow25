# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required(VERSION 3.25)

project(
  streams-now # CMake Project Name, which is also the name of the top-level
  # targets (e.g., library, executable, etc.).
  LANGUAGES CXX
)

include(FetchContent)
include(GNUInstallDirs)

enable_testing()

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG
  b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
  EXCLUDE_FROM_ALL
)
block()
  set(INSTALL_GTEST OFF) # Disable GoogleTest installation
  FetchContent_MakeAvailable(googletest)
endblock()

add_subdirectory(src)
add_subdirectory(examples)
