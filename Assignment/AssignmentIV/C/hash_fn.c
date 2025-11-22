/*
   ========================================
   hash_fn.c — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.h

   Developer: Yu-Feng Huang <yfhuang@saturn.yzu.edu.tw>
 */

#include "hash_fn.h"

int myHashInt(int key, int m) {
    
        /* normalize to non-negative index in [0, m-1] */
        if (m <= 0) return 0; /* defensive: avoid division by zero */
        int idx = key % m;
        if (idx < 0) idx += m;
        return idx;  /* division method (normalized) */
}

int myHashString(const char* str, int m) {
    if (m <= 0) return 0; /* defensive: avoid modulo by zero */

        /*
         * djb2 string hash
         * Reference: http://www.cse.yorku.ca/~oz/hash.html
         */
        unsigned long hash = 5381UL;
        unsigned char c;
        while ((c = (unsigned char)*str++) != 0) {
            /* hash * 33 + c */
            hash = ((hash << 5) + hash) + c;
        }

        return (int)(hash % (unsigned long)m);
}
