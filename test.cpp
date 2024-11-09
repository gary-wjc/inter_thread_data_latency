#include <chrono>
#include <thread>
#include <iostream>
#include "kernel.hpp"

int main() {
  const std::size_t count = 40000000;
  std::size_t v = count;
  std::thread partner(EvenDecToOdd, &v, &v);
  auto st = std::chrono::steady_clock::now();
  OddDecToEven(&v, &v);
  double ss = std::chrono::duration<double>(
    std::chrono::steady_clock::now() - st).count();
  std::cout << "latency = " << ss / count << " seconds\n";
  partner.join();
}
