#include <cstdint>
#include <iostream>
#include <vector>

#ifndef BITSORT_H
#define BITSORT_H

namespace BitSort {
  size_t bitIdxLessThan(uint8_t a, uint8_t b, uint8_t bitIdx) {
    uint8_t aBit = (a >> bitIdx) & 1;
    uint8_t bBit = (b >> bitIdx) & 1;
    return aBit < bBit;
  }

  size_t partition(std::vector<uint8_t>& src, size_t start, size_t end, uint8_t bitIdx) {
    size_t last = end;
    size_t j = start;
    while (j <= last) {
      if ((src[j] >> bitIdx) & 1) {
        std::swap(src[j], src[last--]);
      } else {
        j++;
      }
    }
    return last;
  }

  void sortInternal(std::vector<uint8_t>& src, size_t start, size_t end, uint8_t bitIdx) {
    if (start < end) {
      size_t switchIdx = partition(src, start, end, bitIdx);
      if (bitIdx != 0) {
        uint8_t nextBitIdx = bitIdx - 1;
        sortInternal(src, start, switchIdx, nextBitIdx);
        sortInternal(src, switchIdx + 1, end, nextBitIdx);
      }
    }
  }

  void sort(std::vector<uint8_t>& src) {
    sortInternal(src, 0, src.size() - 1, 8 - 1);
  }
}

#endif