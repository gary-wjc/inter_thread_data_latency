# inter_thread_data_latency
A simple C++ program to test averaged write-to-read latency between 2 threads.

# tested platforms

| CPU | latency(us) |
| --- | --- |
| I9-10980xe default freq. | 0.09~0.10(between cores), 0.02(on the same core) |
| spacemit k1 1.6GHz | 0.13(inside a cluster), 0.24(between clusters) |
