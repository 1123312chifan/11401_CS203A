# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

This assignment focuses on the design and observation of hash functions using C/C++. 
Students are expected to implement and analyze the behavior of hash functions, 
evaluate their efficiency, and understand their applications in computer science.

Developer: 劉季帆  
Email: s1123312@mail.yzu.edu.tw  

使用Linux

## My Hash Function
### Integer Keys 
- Formula / pseudocode:
  ```text
  //c
  int myHashInt(int key, int m) {
    
        /* normalize to non-negative index in [0, m-1] */
        if (m <= 0) return 0; /* defensive: avoid division by zero */
        int idx = key % m;
        if (idx < 0) idx += m;
        return idx;  /* division method (normalized) */
  }
  //c++
  int myHashInt(int key, int m) {
      if (m <= 0) return 0;
      unsigned int x = static_cast<unsigned int>(key);
      // Multiplicative hashing (Knuth) using a large odd constant
      const unsigned int A = 2654435769u; // 2^32 * (sqrt(5)-1)/2
      unsigned int mixed = x * A;
      return static_cast<int>(mixed % static_cast<unsigned int>(m));
  }

  ```
- Rationale: [Explain your design choices and how they minimize collisions.]

### Non-integer Keys
- Formula / pseudocode:
  ```text
  //c
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
  //c++
  int myHashString(const std::string& str, int m) {
    if (m <= 0) return 0;
    // DJB2 hash: simple, fast, good distribution for short strings
    unsigned long hash = 5381ul;
    for (unsigned char c : str) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return static_cast<int>(hash % static_cast<unsigned long>(m));
  }

  ```
- Rationale: [Explain your approach and its effectiveness for non-integer keys.]

## Experimental Setup
- Table sizes tested (m): 10, 11, 37
- Test dataset:
  - Integers: 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
  - Strings: "cat", "dog", "bat", "cow", "ant", "owl", "bee", "hen", "pig", "fox"
- Compiler: GCC and G++
- Standard: C23 and C++23

## Results
| Table Size (m) | Index Sequence         | Observation              |
|----------------|------------------------|--------------------------|
| 10             | 1, 2, 3, 4, ...        | Pattern repeats every 10 |
| 11             | 10, 0, 1, 2, ...       | More uniform             |
| 37             | 20, 21, 22, 23, ...    | Near-uniform             |

## Compilation, Build, Execution, and Output

### Compilation
- The project uses a comprehensive Makefile that builds both C and C++ versions with proper flags:
  ```bash
  # Build both C and C++ versions
  make all
  
  # Build only C version
  make c
  
  # Build only C++ version
  make cxx
  ```

### Manual Compilation (if needed)
- Command for C:
  ```bash
  g++ -std=c++17 -O2 -Wall -Wextra -o main_c.exe main.c hash_fn.c
  ```
- Command for C++:
  ```bash
  g++ -std=c++17 -O2 -Wall -Wextra -o main.exe main.cpp hash_fn.cpp
  ```

### Clean Build Files
- Remove all compiled files:
  ```bash
  make clean
  ```

### Execution
- Run the compiled binary:
  ```bash
  ./main_c.exe
  ```
  or
  ```bash
  ./hash_function_cpp
  ```

### Result Snapshot
- Example output for integers:
  ```
  === Hash Function Observation (C Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...

  === Hash Function Observation (C++ Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...
  ```

- Example output for strings:
  ```
  === String Hash (m = 10) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 11) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 37) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...
  ```

- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.
- Example output for integers:
  ```
  Hash table (m=10): [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
  Hash table (m=11): [10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  Hash table (m=37): [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, ...]
  ```
- Example output for strings:
  ```
  Hash table (m=10): ["cat", "dog", "bat", "cow", "ant", ...]
  Hash table (m=11): ["fox", "cat", "dog", "bat", "cow", ...]
  Hash table (m=37): ["bee", "hen", "pig", "fox", "cat", ...]
  ```
- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.

## Analysis
- Prime vs non-prime `m`: Prime table sizes generally result in better distribution and fewer collisions.
- Patterns or collisions: Non-prime table sizes tend to produce repetitive patterns, leading to more collisions.
- Improvements: Use a prime table size and a well-designed hash function to enhance distribution.

## Reflection
1. Designing hash functions requires balancing simplicity and effectiveness to minimize collisions.
2. Table size significantly impacts the uniformity of the hash distribution, with prime sizes performing better.
3. The design using a prime table size and a linear transformation formula produced the most uniform index sequence.
