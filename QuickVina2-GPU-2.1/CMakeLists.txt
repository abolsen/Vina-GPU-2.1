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

# --- Linux/macOS compatibility for Windows-only PID call ---
if (NOT MSVC)
  # Ensure getpid() is available and transparently substitute the Windows call.
  target_compile_options(${PROJECT_NAME} PRIVATE -include unistd.h)
  target_compile_definitions(${PROJECT_NAME} PRIVATE GetCurrentProcessId=getpid)
endif()


file(GLOB_RECURSE SRC
  "main/*.cpp"
  "src/*.cpp"
  "src/*/*.cpp"
  "lib/*.cpp"
  "lib/*/*.cpp"
  "OpenCL/src/*.cpp"
)

add_executable(QuickVina2-GPU-2.1 ${SRC})

target_include_directories(QuickVina2-GPU-2.1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/compat/include
  ${BOOST_INCLUDES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL/src
)

target_compile_definitions(QuickVina2-GPU-2.1 PRIVATE
  OPENCL_3_0
  CL_TARGET_OPENCL_VERSION=300
  NVIDIA_PLATFORM
  SMALL_BOX
  BUILD_KERNEL_FROM_SOURCE
  BOOST_TIMER_ENABLE_DEPRECATED
  $<$<BOOL:WIN32>:WINDOWS>
)

target_link_libraries(QuickVina2-GPU-2.1 PRIVATE
  OpenCL::OpenCL
  ${BOOST_LIBS}
)
