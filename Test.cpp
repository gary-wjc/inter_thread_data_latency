#include <iostream>
#include <thread>
#include <cstdlib>
#include <vector>
#include <chrono>
#include "Kernel.hpp"

int main(int argc, char **argv) {
  if (argc < 5) {
    std::cout << "Usage: " << argv[0]
      << " <num_workers> <task_size> <message_size> <task_holder_stride>\n";
    return 0;
  }
  const std::size_t num_workers = std::atoi(argv[1]);
  if (num_workers < 2) {
    std::cout << "workers should be at least 2\n";
    return 0;
  }
  const std::size_t task_size = std::atol(argv[2]);
  if (task_size < num_workers * 1000) {
    std::cout << "task size too small\n";
    return 0;
  }
  const std::size_t message_size = std::atoi(argv[3]);
  const std::size_t task_holder_stride0 = std::atoi(argv[4]);
  const std::size_t task_holder_stride = task_holder_stride0 + !task_holder_stride0;
  std::vector<std::atomic_size_t> task_left(num_workers * task_holder_stride);
  std::vector<std::size_t> counters(message_size);
  std::vector<std::thread> rest_workers;
  for (std::size_t id = 0; id < num_workers; ++id) {
    task_left[id * task_holder_stride].store(task_size);
  }
  for (std::size_t id = 1; id < num_workers; ++id) {
    rest_workers.emplace_back(Decrease, &task_left[id * task_holder_stride],
      &task_left[(id - 1u) * task_holder_stride], num_workers, id,
      counters.data(), message_size);
  }
  auto start = std::chrono::steady_clock::now();
  Decrease(&task_left[0], &task_left[(num_workers - 1u) * task_holder_stride],
    num_workers, 0, counters.data(), message_size);
  double seconds = std::chrono::duration<double>(
    std::chrono::steady_clock::now() - start).count();
  for (auto &ct : counters) {
    if (ct != task_size) {
      std::cout << "unexpected counter value = " << ct << std::endl;
      break;
    }
  }
  for (auto &worker : rest_workers) worker.join();
  std::cout << "averaged latency = " << seconds / task_size << " seconds"
    " for passing " << message_size * sizeof(std::size_t) << " bytes"
    " of additional message between threads\n";
}
