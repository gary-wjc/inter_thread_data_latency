# inter_thread_data_latency
A simple C++ program to test averaged write-to-read latency between 2 threads.

# tested platforms

| CPU | latency on the same core(μs) | latency between cores on the same cluster(μs) | latency between clusters(μs) |
| --- | --- | --- | --- |
| i9-10980xe default freq. | 0.02 | 0.09~0.10 | N.A. |
| e5-2680 v4 default freq. | 0.03 | 0.09~0.12 | 0.17~0.26(numa nodes) |
| spacemit k1 1.6GHz | N.A. | 0.13 | 0.24 |
| RockChip RK3562 1.4GHz | N.A. | 0.035 | N.A. |
| Qualcomm APQ8053 2.2GHz DDR3-1866 | N.A. | 0.024 | 0.17 |
| RockChip RK3588 A55x4 1.8GHz | N.A. | 0.067 | 0.070 (to A76) |
| RockChip RK3588 A76x4 2.3GHz | N.A. | N.A. | 0.073 (to A76) |
