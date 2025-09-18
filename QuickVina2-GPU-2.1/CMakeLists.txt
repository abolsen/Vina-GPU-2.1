cmake_minimum_required(VERSION 3.20)
project(QuickVina2GPU21 CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCL REQUIRED)

if (MSVC)
  find_package(Boost CONFIG REQUIRED COMPONENTS
    headers program_options filesystem system serialization random timer math
  )
  set(BOOST_INCLUDES ${Boost_INCLUDE_DIRS})
  set(BOOST_LIBS
    Boost::headers Boost::program_options Boost::filesystem Boost::system
    Boost::serialization Boost::random Boost::timer Boost::math
  )
else()
  find_package(Boost REQUIRED COMPONENTS
    program_options filesystem system serialization random timer
  )
  set(BOOST_INCLUDES ${Boost_INCLUDE_DIRS})
  set(BOOST_LIBS ${Boost_LIBRARIES})
endif()

file(GLOB_RECURSE SRC
  "main/*.cpp"
  "src/*.cpp"
  "src/*/*.cpp"
  "lib/*.cpp"
  "lib/*/*.cpp"
  "OpenCL/src/*.cpp"
)

set(TGT QuickVina2-GPU-2.1)
add_executable(${TGT} ${SRC})

target_include_directories(${TGT} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/compat/include
  ${BOOST_INCLUDES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src
)

target_compile_definitions(${TGT} PRIVATE
  OPENCL_3_0
  CL_TARGET_OPENCL_VERSION=300
  NVIDIA_PLATFORM
  SMALL_BOX
  BUILD_KERNEL_FROM_SOURCE
  BOOST_TIMER_ENABLE_DEPRECATED
  $<$<BOOL:WIN32>:WINDOWS>
  $<$<CXX_COMPILER_ID:MSVC>:_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING>
)

if (NOT MSVC)
  target_compile_options(${TGT} PRIVATE -include unistd.h)
  target_compile_definitions(${TGT} PRIVATE GetCurrentProcessId=getpid)
endif()

target_link_libraries(${TGT} PRIVATE OpenCL::OpenCL ${BOOST_LIBS})
