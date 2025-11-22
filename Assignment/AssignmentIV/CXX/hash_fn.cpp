/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.hpp

   Developer: Yu-Feng Huang <yfhuang@saturn.yzu.edu.tw>
 */
#include "hash_fn.hpp"

int myHashInt(int key, int m) {
    if (m <= 0) return 0;
    unsigned int x = static_cast<unsigned int>(key);
    // Multiplicative hashing (Knuth) using a large odd constant
    const unsigned int A = 2654435769u; // 2^32 * (sqrt(5)-1)/2
    unsigned int mixed = x * A;
    return static_cast<int>(mixed % static_cast<unsigned int>(m));
}

int myHashString(const std::string& str, int m) {
    if (m <= 0) return 0;
    // DJB2 hash: simple, fast, good distribution for short strings
    unsigned long hash = 5381ul;
    for (unsigned char c : str) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return static_cast<int>(hash % static_cast<unsigned long>(m));
}
