# inter_thread_data_latency
A simple C++ program to test averaged write-to-read latency and bandwidth among threads.

# tested platforms

| CPU | latency between cores(μs) | bandwidth between clusters(GB/s) |
| --- | --- | --- | --- |
| spacemit-k1 1.6GHz inside cluster | 93 | 2.0 |
| spacemit-k1 1.6GHz cross clusters | 246 | 1.0 |
| i3-m380 2.5GHz in a physical core | 36 | 15 |
| i3-m380 2.5GHz cross physical cores | 89 | 7 |
| APQ8053 2.2GHz inside cluster | 69 | 6 |
| APQ8053 2.2GHz cross clusters | 111 | 2.0 |
| RK3588 A55x4 1.8GHz | 120 | 3.3 |
| RK3588 A76x4 2.26GHz | 117 | 7 |
| RV1109 1.51GHz | 87 | 2.1 |

The data above are tested with a modified program where the implementation of "all elements incremented by 1" in Kernel.cpp changes from std::transform to SIMD intrinsics(x64) or inline assembly(armv7a-neon and rvv 1.0).
