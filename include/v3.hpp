#pragma once

#include <chrono>
#include <iostream>
#include <ratio>

template <class Time = std::milli, class F>
double easy_bench(const char *name, F f, size_t num_tests = 5) {
  size_t r = f();
  std::chrono::duration<double, Time> t(0);
  for (size_t i = 0; i < num_tests; ++i) {
    auto start = std::chrono::steady_clock::now();
    r += f();
    auto end = std::chrono::steady_clock::now();
    t += end - start;
  }
  t /= num_tests;
  std::cout << "time (" << name << "): " << t.count() << "ms | result: " << r << std::endl;
  return t.count();
}
