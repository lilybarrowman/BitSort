#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>

#include "bit_sort.h"


struct flags {
  bool high;
  bool medium;
  bool low;

  flags() {}
  flags(bool h, bool m, bool l) : high(h), medium(m), low(l) {}
  flags(uint8_t val) : high(val & 0x4), medium(val & 0x2), low(val & 0x1) {}

  bool operator==(flags const& other) const {
    return (high == other.high) && (medium == other.medium) && (low == other.low);
  }

  bool operator<(flags const& other) const {
    if (high < other.high) {
      return true;
    } else if (high == other.high) {
      if (medium < other.medium) {
        return true;
      } else if (medium == other.medium) {
        if (low < other.low) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

};

struct flag_to_uint8_t {
  uint8_t operator()(flags const& f) {
    return (static_cast<uint8_t>(f.high) << 2) | (static_cast<uint8_t>(f.medium) << 1) | static_cast<uint8_t>(f.low);
  }
};

void print_vec(std::vector<uint8_t> const& vec) {
  for (auto i : vec) {
    std::cout << (int) i << " ";
  }
  std::cout << "\n";
}

int main() {
  auto before = std::chrono::system_clock::now();
  std::vector<uint8_t> vals(1'000'000);
  
  std::random_device rnd_device;
  std::mt19937 mersenne_engine(rnd_device());
  std::uniform_int_distribution<int> dist(0, 255);
  auto gen = std::bind(dist, mersenne_engine);
  std::generate(begin(vals), end(vals), gen);

  auto after = std::chrono::system_clock::now();
  std::cout << "uint8_t setup took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";
  //print_vec(vals);

  before = std::chrono::system_clock::now();
  std::vector<uint8_t> bit_sorted(vals);
  bit_sort::sort(&bit_sorted.front(), &bit_sorted.back());
  after = std::chrono::system_clock::now();
  std::cout << "uint8_t bit_sort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";
  //print_vec(bit_sorted);

  before = std::chrono::system_clock::now();
  std::vector<uint8_t> std_sorted(vals);
  std::sort(std::begin(std_sorted), std::end(std_sorted));
  after = std::chrono::system_clock::now();
  std::cout << "uint8_t std::sort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";

  std::cout << "uin8_t permutation Ok:" << std::is_permutation(begin(vals), end(vals), begin(bit_sorted)) << "\n";
  std::cout << "uin8_t sort Ok:" << (bit_sorted == std_sorted) << "\n";

  before = std::chrono::system_clock::now();
  std::vector<flags> flag_vals(1'000'000);
  std::generate(begin(flag_vals), end(flag_vals), gen);
  after = std::chrono::system_clock::now();
  std::cout << "flags setup took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";

  before = std::chrono::system_clock::now();
  std::vector<flags> flags_bit_sorted(flag_vals);
  bit_sort::inner_sort<flags, uint8_t, flag_to_uint8_t>(&flags_bit_sorted.front(), &flags_bit_sorted.back(), 3);
  after = std::chrono::system_clock::now();
  std::cout << "flags bit_sort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";
  //print_vec(bit_sorted);

  before = std::chrono::system_clock::now();
  std::vector<flags> flags_std_sorted(flag_vals);
  std::sort(std::begin(flags_std_sorted), std::end(flags_std_sorted));
  after = std::chrono::system_clock::now();
  std::cout << "flags std::sort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";

  std::cout << "flags permutation Ok:" << std::is_permutation(begin(flag_vals), end(flag_vals), begin(flags_bit_sorted)) << "\n";
  std::cout << "flags sort Ok:" << (flags_bit_sorted == flags_std_sorted) << "\n";

  return 0;
}