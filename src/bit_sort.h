#ifndef BIT_SORT_H
#define BIT_SORT_H

#include <limits>

namespace bit_sort {
  
  template<typename T, typename U, typename E>
  T* partition(T* first, T* last, U bitIdx) {
    E e;
    while (first <= last) {
      if ((e(*first) >> bitIdx) & 1) {
        std::swap(*first, *last);
        --last;
      } else {
        first++;
      }
    }
    return last;
  }

  template<typename T, typename U, typename E>
  void inner_sort(T* first, T* last, U bitIdx) {
    if (last > first) {
      T* pivot = partition<T,U,E>(first, last, bitIdx);

      if (bitIdx != U{0}) {
        U next_bit_idx = bitIdx - 1;
        inner_sort<T,U,E>(first, pivot, next_bit_idx);
        inner_sort<T, U, E>(pivot + 1, last, next_bit_idx);
      }
    }
  }

  template<typename T, typename U = T, typename E = unsigned_caster<T, U>>
  void sort(T* first, T* last) {
    inner_sort<T, U, E>(first, last, std::numeric_limits<U>::digits - 1);
  }

  template<typename T, typename U>
  struct unsigned_caster {
    U operator()(T const& t) {
      return t;
    }
  };

}

#endif