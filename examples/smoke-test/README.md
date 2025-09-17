# Smoke test

Use upstream example config to validate your build. From a method folder (e.g., `AutoDock-Vina-GPU-2.1`):
```
./AutoDock-Vina-GPU-2.1 --config ./input_file_example/2bm2_config.txt
```
Then rebuild without kernel compilation for faster startup:
```
make clean && make
```
Ensure `--opencl_binary_path` in the config points to where `Kernel1_Opt.bin` and `Kernel2_Opt.bin` will be written/read.
