cmake_minimum_required(VERSION 3.20)
project(QuickVinaWGPU21 CXX)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DOPENCL_3_0 -DNVIDIA_PLATFORM)
if (WIN32)
  add_definitions(-DWINDOWS)
endif()

find_package(Boost REQUIRED COMPONENTS program_options filesystem system)
find_package(OpenCL REQUIRED)

file(GLOB_RECURSE SRC
  "src/*.cpp"
  "src/*/*.cpp"
  "lib/*.cpp"
  "lib/*/*.cpp"
  "OpenCL/src/*.cpp"
)

add_executable(QuickVina-W-GPU-2.1 ${SRC})
target_include_directories(QuickVina-W-GPU-2.1 PRIVATE
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src
)
target_link_libraries(QuickVina-W-GPU-2.1 PRIVATE ${Boost_LIBRARIES} OpenCL::OpenCL)
