#include <cstddef>
#include <atomic>

void Decrease(const std::atomic_size_t *task_left_recv, std::atomic_size_t *task_left_send,
  std::size_t comms, std::size_t comm_id,
  std::size_t *count_array, std::size_t count_array_len) noexcept;
