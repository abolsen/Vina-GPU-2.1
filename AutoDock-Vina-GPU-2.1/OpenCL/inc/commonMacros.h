#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

// Ensure OpenCL 3.0 headers default is explicit (silences warnings).
#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 300
#endif

// Platform includes
#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  // Windows doesn't have unistd.h; provide minimal shims if needed.
  #ifndef NOMINMAX
  #define NOMINMAX
  #endif
#else
  #include <unistd.h>
#endif

// Provide a portable sleep macro in milliseconds (used by some codebases)
inline void portable_sleep_ms(unsigned int ms) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

#endif // COMMON_MACROS_H
