#include <cstdint>
#include <iostream>
#include <vector>

#ifndef BITSORT_H
#define BITSORT_H

namespace BitSort {
  template<typename T>
  size_t bitIdxLessThan(T a, T b, T bitIdx) {
    T aBit = (a >> bitIdx) & 1;
    T bBit = (b >> bitIdx) & 1;
    return aBit < bBit;
  }
  
  template<typename T>
  size_t partition(std::vector<T>& src, size_t start, size_t end, T bitIdx) {
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

  template<typename T>
  void sortInternal(std::vector<T>& src, size_t start, size_t end, T bitIdx) {
    if (start < end) {
      size_t switchIdx = partition(src, start, end, bitIdx);
      if (bitIdx != 0) {
        T nextBitIdx = bitIdx - 1;
        sortInternal(src, start, switchIdx, nextBitIdx);
        sortInternal(src, switchIdx + 1, end, nextBitIdx);
      }
    }
  }
  
  // Specialize this function as needed
  template<typename T>
  T mostSignificantBitIndex() {
    static_assert(false, "mostSignificantBitIndex() is undefined for this type");
  }
  
  template<typename T>
  void sort(std::vector<T>& src) {
    sortInternal(src, 0, src.size() - 1, mostSignificantBitIndex<T>());
  }
}

#endif