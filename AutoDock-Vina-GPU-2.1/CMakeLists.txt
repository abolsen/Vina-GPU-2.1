cmake_minimum_required(VERSION 3.16)
project(AutoDockVinaGPU21 LANGUAGES CXX)

# Executable name (keeps the original binary filename)
set(TGT "AutoDock-Vina-GPU-2.1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCL
find_package(OpenCL REQUIRED)

# Boost: add all the components the code actually uses
# (program_options, filesystem, system, serialization, random, timer, thread)
find_package(Boost 1.65 REQUIRED
  COMPONENTS program_options filesystem system serialization random timer thread)

# Sources
file(GLOB SRC_LIB            "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
file(GLOB SRC_OPENCL         "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src/*.cpp")
file(GLOB SRC_MAIN           "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp")
set(SRC_ALL ${SRC_LIB} ${SRC_OPENCL} ${SRC_MAIN})

add_executable(${TGT} ${SRC_ALL})

target_include_directories(${TGT} PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc"
)

# Prefer OpenCL 3.0 on Linux CI; keep other defines opt-in via CI if needed
target_compile_definitions(${TGT} PRIVATE OPENCL_3_0)

if (MSVC)
  target_compile_definitions(${TGT} PRIVATE _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
endif()

# Threads (for Boost.Thread)
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
endif()
