cmake_minimum_required(VERSION 3.16)
project(AutoDockVinaGPU21 LANGUAGES CXX)
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/shims)
set(TGT "AutoDock-Vina-GPU-2.1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCL REQUIRED)
find_package(Boost 1.65 REQUIRED
  COMPONENTS program_options filesystem system serialization random timer thread)

file(GLOB SRC_LIB     "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
file(GLOB SRC_OPENCL  "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src/*.cpp")
file(GLOB SRC_MAIN    "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp")
set(SRC_ALL ${SRC_LIB} ${SRC_OPENCL} ${SRC_MAIN})

add_executable(${TGT} ${SRC_ALL})

target_include_directories(${TGT} PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc"
)

# Prefer OpenCL 3.0; keep others opt-in if you need
target_compile_definitions(${TGT} PRIVATE OPENCL_3_0)

if (MSVC)
  target_compile_definitions(${TGT} PRIVATE _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
endif()

find_package(Threads REQUIRED)

target_link_libraries(${TGT} PRIVATE
  OpenCL::OpenCL
  Boost::program_options Boost::filesystem Boost::system
  Boost::serialization Boost::random Boost::timer Boost::thread
  Threads::Threads
)

# GCC/Clang need the old experimental filesystem shim
if (NOT MSVC)
  target_link_libraries(${TGT} PRIVATE stdc++fs)

  # Force-include our Linux compatibility header everywhere
  target_compile_options(${TGT} PRIVATE
    "-include" "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc/linux_fix.h")

  # Provide definition of the global options string
  target_sources(${TGT} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src/linux_fix.cpp")
endif()
