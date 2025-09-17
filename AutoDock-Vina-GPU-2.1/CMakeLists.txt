cmake_minimum_required(VERSION 3.20)
project(AutoDockVinaGPU21 CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS program_options filesystem system)
find_package(OpenCL REQUIRED)

file(GLOB_RECURSE SRC
  "src/*.cpp"
  "src/*/*.cpp"
  "lib/*.cpp"
  "lib/*/*.cpp"
  "OpenCL/src/*.cpp"
)

add_executable(AutoDock-Vina-GPU-2.1 ${SRC})

# Include dirs (project + deps)
target_include_directories(AutoDock-Vina-GPU-2.1 PRIVATE
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src
)

# Preprocessor defines mirroring upstream Makefile
target_compile_definitions(<TARGET> PRIVATE
  OPENCL_3_0
  CL_TARGET_OPENCL_VERSION=300
  NVIDIA_PLATFORM
  SMALL_BOX
  BUILD_KERNEL_FROM_SOURCE
  BOOST_TIMER_ENABLE_DEPRECATED
  $<$<BOOL:WIN32>:WINDOWS>
)

target_link_libraries(AutoDock-Vina-GPU-2.1 PRIVATE ${Boost_LIBRARIES} OpenCL::OpenCL)
