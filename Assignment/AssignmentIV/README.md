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
  gcc -std=c2x -Wall -Wextra -Wpedantic -g -o C/hash_function C/main.c C/hash_fn.c
  ```
- Command for C++:
  ```bash
  g++ -std=c++2x -Wall -Wextra -Wpedantic -g -o CXX/hash_function_cpp CXX/main.cpp CXX/hash_fn.cpp
  ```

### Clean Build Files
- Remove all compiled files:
  ```bash
  make clean
  ```

### Execution
- Run the compiled binary:
  ```bash
  ./hash_function
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
  23      3
  24      4
  25      5
  26      6
  27      7
  28      8
  29      9
  30      0
  51      1
  52      2
  53      3  
  54      4
  55      5
  56      6
  57      7
  58      8
  59      9
  60      0

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  23      1
  24      2
  25      3
  26      4
  27      5
  28      6
  29      7
  30      8
  51      7
  52      8
  53      9
  54      10
  55      0
  56      1
  57      2
  58      3
  59      4
  60      5

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  23      23
  24      24
  25      25
  26      26
  27      27
  28      28
  29      29
  30      30
  51      14
  52      15
  53      16
  54      17
  55      18
  56      19
  57      20
  58      21
  59      22
  60      23

  === Hash Function Observation (C++ Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      7
  22      0
  23      3
  24      2
  25      5
  26      8
  27      7
  28      0
  29      9
  30      2
  51      3
  52      6
  53      5
  54      8
  55      7
  56      0
  57      3
  58      2
  59      5
  60      8

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      0
  22      3
  23      6
  24      2
  25      5
  26      8
  27      4
  28      7
  29      3
  30      6
  51      2
  52      5
  53      1
  54      4
  55      0
  56      3
  57      6
  58      2
  59      5
  60      8

- Example output for strings:
  ```
  === String Hash (m = 10) ===
  Key     Index
  -----------------
  cat     5
  dog     3
  bat     6
  cow     0
  ant     6
  owl     1
  bee     3
  hen     6
  pig     3
  fox     8

  === String Hash (m = 11) ===
  Key     Index
  -----------------
  cat     6
  dog     4
  bat     6
  cow     9
  ant     6
  owl     9
  bee     2
  hen     0
  pig     4
  fox     10

  === String Hash (m = 37) ===
  Key     Index
  -----------------
  cat     29
  dog     13
  bat     13
  cow     13
  ant     19
  owl     14
  bee     19
  hen     13
  pig     7
  fox     25
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
-Prime vs non-prime m
在本次實驗中，我們比較了m=10(合數)和m=11(質數) 的雜湊結果。儘管在m=10和m=11兩種情況下，測試數據集21到30和51到60都發生了6組衝突，但兩者在衝突的分佈模式上仍存在顯著差異。
m=10 (合數)： 衝突主要發生在那些個位數相同或相近的鍵值之間。這種高度的依賴性顯示雜湊函數\text{Hash}(k)=k\pmod{10}未能有效利用鍵值的全部資訊。更嚴重的是，對於間隔為10的鍵值，如(27, 37, 57)，它們將必然碰撞，顯示出糟糕的散佈模式。
m=11 (質數)： 儘管衝突數量相同，但在m=11時，衝突的分佈看起來更隨機，不易從鍵值本身直接看出規律。質數m=11的選擇，讓雜湊函數k\pmod{11}能更充分地將鍵值的分佈打亂，提供了更好的Avalanche Effect，使得鍵值微小的變化能導致雜湊索引的大幅變化，這對減少特定模式的輸入導致的系統性衝突非常重要。

-Patterns or collisions
雜湊表大小(m)具體衝突模式10鍵值k和k+10產生碰撞的機率極高。例如：27,55碰撞於索引7。-28和56碰撞於索引0。這種模式表明雜湊函數在m=10時，輸出的隨機性較低。11衝突雖然存在，但沒有明顯的規律將鍵值k與k+10或其他固定間隔的鍵值聯繫起來。例如，雖然22和29都碰撞到索引3，但它們的間隔7並不是11的倍數，這顯示m=11有效地打破了輸入數據的規律性。

-Improvements
確保m為質數： 繼續使用 m=11或m=37這樣的質數作為雜湊表大小，以維持良好的分佈特性。優化雜湊函數： 對於m=10時產生的嚴重碰撞，考慮在 \text{Hash}(k)中引入乘法或位元操作（例如 \text{Hash}(k) = (k \times A + B) \pmod m），使得中間結果能更充分地混合鍵值的各個位元，而不僅僅依賴於k的末數位。
## Reflection
1. Designing hash functions requires balancing simplicity and effectiveness to minimize collisions.
2. Table size significantly impacts the uniformity of the hash distribution, with prime sizes performing better.
3. The design using a prime table size and a linear transformation formula produced the most uniform index sequence.
