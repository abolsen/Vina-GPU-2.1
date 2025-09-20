#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  static inline int my_pid() {
      return static_cast<int>(::GetCurrentProcessId());
  }
#else
  #include <unistd.h>
  static inline int my_pid() {
      return static_cast<int>(::getpid());
  }
#endif
