# Windows developer machine build (manual)

1. Install **Visual Studio 2019** (Desktop C++ workload).
2. Install **Boost 1.77.0** (prebuilt or build from source).
3. Install **CUDA Toolkit 12.2** (for NVIDIA). OpenCL.lib is available via CUDA or vendor driver.
4. In your VS project (or CMake toolchain), add include paths:
   - `$(METHOD)/lib`
   - `$(METHOD)/OpenCL/inc`
   - `$(BOOST_ROOT)` and `$(BOOST_ROOT)/boost`
   - `$(CUDA_PATH)/include`
5. Add library paths:
   - `$(BOOST_ROOT)/stage/lib` (or where your Boost libs are)
   - `$(CUDA_PATH)/lib/x64`
6. Link **OpenCL.lib** and required Boost libs.
7. Preprocessor defines:
   - `NVIDIA_PLATFORM;OPENCL_3_0;WINDOWS`
   - (optional) `BUILD_KERNEL_FROM_SOURCE` to compile kernels on first run.
8. Ensure CRLF line endings on Windows sources where required.
