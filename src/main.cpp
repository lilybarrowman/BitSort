#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>

#include "BitSort.h"

void printVec(std::vector<uint8_t> const& vec) {
  for (auto i : vec) {
    std::cout << (int) i << " ";
  }
  std::cout << "\n";
}

int main() {
  auto before = std::chrono::system_clock::now();

  std::vector<uint8_t> vals(1'000'000);//{242, 205, 197, 5, 125, 92, 113, 159, 144, 1};
  
  std::random_device rnd_device;
  std::mt19937 mersenne_engine(rnd_device());
  std::uniform_int_distribution<int> dist(0, 255);
  auto gen = std::bind(dist, mersenne_engine);
  std::generate(begin(vals), end(vals), gen);

  auto after = std::chrono::system_clock::now();
  std::cout << "setup took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";
  //printVec(vals);

  before = std::chrono::system_clock::now();
  std::vector<uint8_t> bitSorted(vals);
  BitSort::sort(bitSorted);
  after = std::chrono::system_clock::now();
  std::cout << "BitSort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";
  //printVec(bitSorted);


  before = std::chrono::system_clock::now();
  std::vector<uint8_t> stdSorted(vals);
  std::sort(std::begin(stdSorted), std::end(stdSorted));
  after = std::chrono::system_clock::now();
  std::cout << "std::sort took " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms\n";

  std::cout << "Permutation Ok:" << std::is_permutation(begin(vals), end(vals), begin(bitSorted)) << "\n";
  std::cout << "Sort Ok:" << (bitSorted == stdSorted) << "\n";
  return 0;
}