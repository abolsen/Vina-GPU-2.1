#pragma once

// Force OpenCL 3.0 headers behavior (silences pragma + consistent API)
#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 300
#endif

// Reasonable defaults; adjust if your datasets need larger buffers.
// 128^3 * 8 floats ~= 64 MB total per grid.
#ifndef MAX_NUM_OF_GRID_MI
#define MAX_NUM_OF_GRID_MI 128
#endif
#ifndef MAX_NUM_OF_GRID_MJ
#define MAX_NUM_OF_GRID_MJ 128
#endif
#ifndef MAX_NUM_OF_GRID_MK
#define MAX_NUM_OF_GRID_MK 128
#endif

// Relation table upper bound (rows/cols). Tune if needed.
#ifndef MAX_NUM_OF_ATOM_RELATION_COUNT
#define MAX_NUM_OF_ATOM_RELATION_COUNT 4096
#endif

// Some code uses a variable named `option` for OpenCL build options on Linux,
// but it's not declared under GCC/Clang. Provide a single global string and
// make `option` refer to it without touching original sources.
#ifdef __linux__
  #include <string>
  extern std::string g_opencl_build_option;
  #define option g_opencl_build_option
#endif
