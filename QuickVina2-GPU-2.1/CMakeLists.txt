cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0167 NEW)  # use BoostConfig.cmake instead of the removed module
project(QuickVina2GPU21 LANGUAGES CXX)

set(TGT "QuickVina2-GPU-2.1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCL REQUIRED)
# --- Boost discovery (vcpkg config-mode on Windows CI, module fallback elsewhere) ---
if(DEFINED CMAKE_TOOLCHAIN_FILE AND CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg")
  cmake_policy(SET CMP0167 NEW)  # prefer BoostConfig.cmake
  find_package(Boost 1.65 CONFIG REQUIRED
    COMPONENTS program_options filesystem system serialization random timer thread)
else()
  find_package(Boost 1.65 REQUIRED
    COMPONENTS program_options filesystem system serialization random timer thread)
endif()

# enable deprecated boost::progress header while we migrate
add_compile_definitions(BOOST_TIMER_ENABLE_DEPRECATED)


file(GLOB SRC_LIB     "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
file(GLOB SRC_OPENCL  "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src/*.cpp")
file(GLOB SRC_MAIN    "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp")
set(SRC_ALL ${SRC_LIB} ${SRC_OPENCL} ${SRC_MAIN})

add_executable(${TGT} ${SRC_ALL})

target_include_directories(${TGT} PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc"
)

target_compile_definitions(${TGT} PRIVATE
  BOOST_TIMER_ENABLE_DEPRECATED
  OPENCL_3_0
)

if (MSVC)
  target_compile_definitions(${TGT} PRIVATE
    _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
    WIN32_LEAN_AND_MEAN NOMINMAX
  )
endif()


find_package(Threads REQUIRED)

target_link_libraries(${TGT} PRIVATE
  OpenCL::OpenCL
  Boost::program_options Boost::filesystem Boost::system
  Boost::serialization Boost::random Boost::timer Boost::thread
  Threads::Threads
)

if (NOT MSVC)
  target_link_libraries(${TGT} PRIVATE stdc++fs)
  target_compile_options(${TGT} PRIVATE
    "-include" "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc/linux_fix.h")
  target_sources(${TGT} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src/linux_fix.cpp")
endif()
