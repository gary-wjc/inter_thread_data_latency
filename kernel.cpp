#include "kernel.hpp"

void EvenDecToOdd(const volatile std::size_t *r, volatile std::size_t *s) noexcept {
  std::size_t prev = -1;
  std::size_t ld;
  while ((ld = *r) > 1u) {
    if (ld < prev && !(ld & 1u)) {
      *s = --ld;
      prev = ld;
    }
  }
}

void OddDecToEven(const volatile std::size_t *r, volatile std::size_t *s) noexcept {
  std::size_t prev = -1;
  std::size_t ld;
  while ((ld = *r) > 1u) {
    if (ld < prev && (ld & 1u)) {
      *s = --ld;
      prev = ld;
    } 
  } 
  if (ld == 1u) *s = 0;
}

