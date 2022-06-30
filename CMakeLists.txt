# CMakeList.txt : CMake project for test_task_saber, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("test_task_saber")

# Add source to this project's executable.
add_executable (test_task_saber "test_task_saber.cpp" "test_task_saber.hpp" "remove_dups.hpp" "list.cpp" "dec_to_bin.hpp" "list.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_task_saber PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
