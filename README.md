# University Timetable & Classroom Allocation Engine

### A Design and Analysis of Algorithms (DAA) Project

A C++17-based university scheduling system that automatically generates timetables, allocates classrooms, detects scheduling conflicts, searches academic records and compares algorithmic approaches for efficient resource allocation.

The project demonstrates how **Greedy Algorithms, Backtracking, Divide and Conquer, Dynamic Programming, Graph Algorithms, Branch and Bound, and String Matching** can be applied to educational scheduling and related optimization problems.

---

## 1. Project Overview

Creating university timetables manually can be difficult when multiple courses, faculty members, student batches, classrooms and time slots must be considered simultaneously.

Common problems include:

- Faculty assigned to multiple classes at the same time.
- Two batches or classes competing for the same classroom.
- Insufficient classroom seating capacity.
- Laboratory courses assigned to unsuitable rooms.
- Uneven distribution of lectures throughout the week.
- Difficulty searching and modifying schedules.

Our project addresses these problems by generating schedules automatically while checking defined constraints.

The application also provides algorithm comparisons, performance measurements, correctness testing and CSV export.

## 2. Key Features

**Automated Timetable Generation**

Generates weekly timetables using a Greedy allocation strategy.

**Backtracking-Based Scheduling**

Provides an alternative scheduling method that can reconsider previous assignments when necessary.

**Constraint Validation**

Checks faculty clashes, batch clashes, room clashes, classroom capacity, laboratory requirements and weekly lecture counts.

**Timetable Search Engine**

Supports searching by course ID, faculty name and batch. An additional analysis module compares four string-matching algorithms on university records.

**Algorithm Performance Analysis**

Compares Greedy and Backtracking based on candidate checks, execution time, scheduling completeness and correctness.

**CSV Data Management**

Loads academic records from CSV files and exports generated timetables.

**Stress Testing**

Evaluates scheduling performance on increasingly large synthetic university datasets.

## 3. Technologies Used

| Technology | Purpose |
|---|---|
| C++17 | Core application and algorithm implementation |
| CMake | Build configuration |
| CTest | Automated testing |
| CSV | Input datasets and exported timetables |
| Git | Version control |
| GitHub | Repository hosting |
| C++ Standard Library | Containers, strings, file handling and timing |

The assessed algorithms are implemented manually rather than using built-in sorting, searching or graph-algorithm functions.

## 4. System Architecture

```text
University CSV Datasets
          |
          v
     DataLoader
          |
          v
     DataValidator
          |
          v
  Timetable Allocation
       /       \
      /         \
   Greedy    Backtracking
      \         /
       \       /
          v
  Timetable Validator
          |
          v
  Generated Timetable
          |
    +-----+------+
    |     |      |
    v     v      v
  Search  CSV  Statistics
         Export
```

The system separates university data models, algorithm implementations, validation, scheduling, testing and benchmarking.

## 5. Project Structure

```text
university-timetable-daa/
|
|-- include/
|   |-- models/
|   |-- data/
|   |-- validation/
|   |-- timetable/
|   |-- analysis/
|   `-- algorithms/
|
|-- src/
|   |-- main.cpp
|   |-- data/
|   |-- validation/
|   |-- timetable/
|   `-- algorithms/
|
|-- data/
|   |-- courses.csv
|   |-- faculty.csv
|   |-- rooms.csv
|   |-- sections.csv
|   |-- timeslots.csv
|   `-- generated_timetable.csv
|
|-- tests/
|   |-- TimetableTests.cpp
|   `-- exact_algorithms_test.cpp
|
|-- benchmarks/
|   |-- StressTest.cpp
|   |-- FinalBenchmark.cpp
|   |-- BenchmarkSummary.cpp
|   |-- final_results.csv
|   `-- summary.csv
|
|-- docs/
|   `-- complexity_report.md
|
|-- CMakeLists.txt
|-- README.md
`-- .gitignore
```

## 6. DAA Algorithms Implemented

### Divide and Conquer

- Iterative Binary Search
- Recursive Binary Search
- Merge Sort
- Quick Sort
- Maximum Subarray
- Fast Exponentiation
- Celebrity Identification
- Classical Matrix Multiplication
- Strassen Matrix Multiplication

### Greedy Algorithms

- Activity Selection
- Interval Partitioning
- Fractional Knapsack
- Huffman Coding
- Dijkstra's Shortest Path
- Prim's Minimum Spanning Tree
- Kruskal's Minimum Spanning Tree

### Dynamic Programming

- 0/1 Knapsack
- Matrix Chain Multiplication
- Longest Common Subsequence
- Optimal Binary Search Tree
- Bellman-Ford
- Floyd-Warshall
- Travelling Salesperson using Bitmask DP

### Backtracking

- N-Queens
- Sum of Subsets
- 0/1 Knapsack using Backtracking
- Timetable Generation using Backtracking

### Branch and Bound

- FIFO Branch and Bound
- LIFO Branch and Bound
- Best-Bound Branch and Bound

### Flow and Matching

- Ford-Fulkerson Maximum Flow
- Maximum Bipartite Matching

### Number Theory

- Chinese Remainder Theorem

### String Matching

- Naive String Matching
- Rabin-Karp
- Finite Automaton Matching
- Knuth-Morris-Pratt (KMP)

Some algorithms directly support timetable scheduling and searching. Others are implemented as reusable DAA modules for related resource-allocation, routing, optimization and analytical problems.

## 7. Timetable Allocation Constraints

Before scheduling a lecture, the system checks:

1. The classroom has sufficient seating capacity.
2. Laboratory courses are assigned to suitable laboratories.
3. A faculty member is not assigned to overlapping lectures.
4. A student batch does not have overlapping lectures.
5. A classroom is not allocated to overlapping lectures.
6. A course offering has at most one lecture per day under the current scheduling policy.

The final timetable validator also checks that the required weekly lecture counts are satisfied.

## 8. Installation and Setup

### Requirements

- A C++17-compatible compiler
- CMake 3.16 or later
- Git (optional, for cloning)

The project has been developed and tested on macOS using Apple Clang and CMake.

### Clone the Repository

```bash
git clone https://github.com/ajain347/university-timetable-daa.git

cd university-timetable-daa
```

### Build the Project

```bash
cmake -S . -B build
cmake --build build
```

### Run the Application

The current CSV paths are relative to the build directory.

```bash
cd build
./timetable
```

On Windows, the executable location may differ depending on the CMake generator.

## 9. Application Menu

```text
========================================
 UNIVERSITY TIMETABLE ALLOCATION ENGINE
========================================

1. Load University Data
2. Generate Timetable
3. View Timetable
4. Search Timetable
5. Constraint Diagnostics
6. Algorithm Analysis
7. Allocation Statistics
0. Exit
```

### Recommended Demonstration

Start the application and use the following sequence:

**Option 1:** Load and validate the university dataset.

**Option 2:** Generate the weekly timetable.

**Option 3:** View the generated timetable.

**Option 4:** Search for a course, faculty member or batch.

**Option 5:** Run timetable constraint diagnostics.

**Option 6:** Compare Naive, Rabin-Karp, Finite Automaton and KMP string matching.

**Option 7:** Compare Greedy and Backtracking timetable generation, including the reduced-room scenario.

## 10. Sample Timetable Results

The sample university dataset contains:

| Entity | Count |
|---|---:|
| Courses | 8 |
| Faculty members | 4 |
| Classrooms | 4 |
| Student batches | 2 |
| Available time slots | 20 |

### Generated Timetable Summary

```text
Required lectures: 24
Scheduled lectures: 24
Unscheduled lectures: 0

Timetable Validation: PASS
CSV Export: SUCCESS
```

Example timetable entry:

```text
Monday | 9:00-10:00
Subject: Design and Analysis of Algorithms
Faculty: Dr Sharma
Batch: CSE-A
Room: Room-201
```

The timetable is exported to:

`data/generated_timetable.csv`

## 11. Greedy vs Backtracking Comparison

Both algorithms were evaluated using identical university datasets.

Each algorithm was executed 20 times per scenario.

### Normal University Scenario

| Metric | Greedy | Backtracking |
|---|---:|---:|
| Required lectures | 24 | 24 |
| Scheduled lectures | 24 | 24 |
| Average execution time | 0.185250 ms | 0.413217 ms |
| Minimum execution time | 0.153792 ms | 0.348625 ms |
| Maximum execution time | 0.231291 ms | 0.496625 ms |
| Candidate checks | 594 | 594 |
| Valid runs | 20/20 | 20/20 |

Greedy was approximately **2.23 times faster** on average.

### Reduced Classroom Availability

| Metric | Greedy | Backtracking |
|---|---:|---:|
| Required lectures | 24 | 24 |
| Scheduled lectures | 24 | 24 |
| Average execution time | 0.111773 ms | 0.240863 ms |
| Candidate checks | 300 | 300 |
| Valid runs | 20/20 | 20/20 |

Greedy was approximately **2.15 times faster** on average.

### Interpretation

Both algorithms generated complete and valid timetables in the tested scenarios.

Greedy performed better in execution time because it selected valid assignments directly, while Backtracking introduced additional recursive overhead.

Backtracking remains useful for more difficult scheduling instances where earlier assignments must be reconsidered.

These measurements do not imply that Greedy is universally faster or always produces a complete schedule.

## 12. Large-Data Stress Testing

Synthetic datasets were generated to evaluate scalability.

| Courses | Rooms | Required Lectures | Scheduled | Candidate Checks | Time |
|---:|---:|---:|---:|---:|---:|
| 30 | 10 | 90 | 90 | 8,595 | 8.85 ms |
| 150 | 30 | 450 | 450 | 141,975 | 209.49 ms |
| 300 | 60 | 900 | 900 | 567,450 | 1,437.55 ms |

The allocator successfully assigned all requested lectures in the three benchmark scenarios.

Full independent timetable validation was performed for the smallest stress-test dataset. The medium and large datasets were checked for allocation counts but were not independently validated in that benchmark run.

These results demonstrate increasing computational cost as the dataset grows.

## 13. Automated Testing

The project uses CTest and dedicated test executables.

### Build and Run Registered Tests

From the project root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Observed Test Results

```text
Test #1: exact_algorithms .......... Passed
Test #2: timetable_regression ...... Passed

100% tests passed out of 2
```

The regression tests cover:

- Merge Sort and Quick Sort
- Iterative and Recursive Binary Search
- Four String Matching algorithms
- Greedy timetable allocation
- Backtracking timetable allocation
- Insufficient classroom capacity

The exact-algorithm tests cover:

- N-Queens
- Sum of Subsets
- Backtracking Knapsack
- FIFO Branch and Bound
- LIFO Branch and Bound
- Best-Bound Branch and Bound

Passing these tests provides correctness evidence for the tested cases, not exhaustive verification of every possible input.

## 14. Benchmarking

### Run the Stress Test

```bash
./build/stress_test
```

### Run the Repeated Benchmark

```bash
./build/final_benchmark
```

### Generate the Benchmark Summary

```bash
./build/benchmark_summary
```

The benchmark programs should be executed from the project root.

Generated results:

```text
benchmarks/final_results.csv
benchmarks/summary.csv
```

The repeated benchmark contains 80 measurements:

- 20 Greedy runs on the normal dataset.
- 20 Backtracking runs on the normal dataset.
- 20 Greedy runs on the reduced-room dataset.
- 20 Backtracking runs on the reduced-room dataset.

## 15. Complexity Analysis

| Algorithm | Typical / Worst-Case Complexity |
|---|---|
| Binary Search | O(log n) |
| Merge Sort | Θ(n log n) |
| Quick Sort | Θ(n log n) average, O(n²) worst |
| Greedy Timetable Allocation | Depends on lectures, slots, rooms and conflict checks |
| Backtracking Timetable Allocation | Exponential worst-case search |
| Dijkstra (adjacency matrix) | O(V²) |
| Prim (adjacency matrix) | O(V²) |
| Floyd-Warshall | O(V³) |
| Bellman-Ford | O(VE) |
| KMP | O(n + m) |
| TSP Bitmask DP | O(n² × 2^n) |

For detailed recurrence relations, best/average/worst-case analysis, algorithm selection and complexity-class discussion, see:

`docs/complexity_report.md`

## 16. Limitations

The current implementation has several limitations:

- Greedy scheduling does not guarantee an optimal timetable.
- Backtracking can become computationally expensive for large instances.
- The current scheduling policy allows at most one lecture per course offering per day.
- Faculty preferences and individual availability are not fully modeled.
- Room utilization and timetable gaps are not yet globally optimized.
- Search matching is case-sensitive.
- Some DAA modules use analytical test data rather than direct timetable records.
- Peak memory usage is not consistently measured across every algorithm.
- The current CSV exporter assumes simple field values without embedded commas or quotation marks.
- Larger stress-test outputs require additional independent correctness checks.

## 17. Future Improvements

Potential extensions include:

- Faculty availability and preference management.
- Better room utilization and workload balancing.
- Automatic timetable rescheduling.
- Graphical or web-based user interface.
- Faster conflict checking using indexed data structures.
- Case-insensitive and fuzzy timetable search.
- More advanced optimization strategies.
- Larger real-world university datasets.
- Additional benchmark visualizations.

## 18. Conclusion

The University Timetable and Classroom Allocation Engine demonstrates how DAA concepts can be applied to academic scheduling.

The project successfully generates clash-free timetables on the tested sample data, allocates classrooms according to defined constraints, supports timetable searching and compares different algorithmic strategies.

The experiments show that Greedy allocation provides an efficient baseline for the tested datasets, while Backtracking offers a more flexible approach when scheduling decisions must be reconsidered.

The project also includes reusable implementations of mandatory DAA algorithms, automated tests, benchmarking utilities and theoretical complexity analysis.

---

**Project Repository:** https://github.com/ajain347/university-timetable-daa

**Implementation:** C++17

**Subject:** Design and Analysis of Algorithms