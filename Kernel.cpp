#include "Kernel.hpp"
#include <algorithm>

void Decrease(const std::atomic_size_t *task_left_recv,
  std::atomic_size_t *task_left_send, std::size_t comms, std::size_t comm_id,
  std::size_t *count_array, std::size_t count_array_len) noexcept {

  if (!task_left_recv || !task_left_send || comm_id >= comms) return;
  std::size_t prev = -1;
  std::size_t load;
  while ((load = task_left_recv->load(std::memory_order_acquire))) {
    if (load < prev && (load % comms) == comm_id) {
      std::transform(count_array, count_array + count_array_len, count_array,
        [](std::size_t in)->std::size_t { return in + 1u; });
      task_left_send->store(--load, std::memory_order_release);
      prev = load;
    }
  }
  task_left_send->store(0, std::memory_order_release);
}
