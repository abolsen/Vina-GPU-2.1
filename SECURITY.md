# Security & Trust

- Release artifacts include `SHA256SUMS.txt`. Verify after download.
- Binaries are built by GitHub Actions from a clean runner on tagged commits.
- No NVIDIA runtime libraries are bundled; your system/driver provides CUDA/OpenCL.
- Optionally, sign releases with `cosign` (not configured by default).
