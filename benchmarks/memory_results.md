
# Memory Usage Analysis

## University Timetable and Classroom Allocation Engine

### Measurement Environment

- Platform: macOS
- Language: C++17
- Build system: CMake
- Measurement tool: `/usr/bin/time -l`

### Experimental Results

| Executable | Maximum Resident Set Size | Memory (MiB) |
|---|---:|---:|
| stress_test | 2,031,616 bytes | 1.94 |
| timetable | 2,015,232 bytes | 1.92 |

### Stress Test Details

| Courses | Required Lectures | Scheduled | Execution Time |
|---:|---:|---:|---:|
| 30 | 90 | 90 | 5.18108 ms |
| 150 | 450 | 450 | 208.194 ms |
| 300 | 900 | 900 | 1456.92 ms |

All requested lectures were scheduled in these runs.

Independent timetable validation was performed only for
the 30-course stress-test dataset.

### Interpretation

The maximum resident set size measures peak physical memory
resident for the entire application process.

It includes program runtime overhead, input data structures,
algorithm allocations and other process memory.

The stress-test executable runs three scenarios sequentially,
so its peak memory cannot be attributed to a particular
dataset size.

The results do not directly measure the auxiliary memory
complexity of an individual algorithm.

### Theoretical Auxiliary Space

| Algorithm | Space Complexity |
|---|---|
| Iterative Binary Search | O(1) |
| Recursive Binary Search | O(log n) |
| Merge Sort | O(n) |
| Quick Sort | O(log n) average, O(n) worst |
| Greedy Timetable Allocation | O(L) including returned timetable |
| Backtracking Allocation | O(L) for recursion and partial schedule |
| KMP | O(m) |
| Floyd-Warshall | O(V²) |
| TSP Bitmask DP | O(n × 2^n) |

L = number of lecture requests.
m = search-pattern length.
V = number of graph vertices.

### Limitations

- These are process-level memory measurements.
- Memory usage may vary across operating systems and compilers.
- The stress-test memory result includes all three scenarios.
- Algorithm-specific peak memory was not measured separately.
```

## 3. Our remaining submission tasks

| Requirement | Status |
|---|---|
| Core timetable engine | <icon name="check" color="success" inline /> Done |
| Mandatory algorithm implementations | <icon name="check" color="success" inline /> Initial coverage |
| Automated tests | <icon name="check" color="success" inline /> Passed |
| Normal and reduced-room benchmarks | <icon name="check" color="success" inline /> Done |
| Stress testing | <icon name="check" color="success" inline /> Done |
| Memory measurement | <icon name="check" color="success" inline /> Process-level done |
| Complexity and recurrence report | <icon name="check" color="success" inline /> Draft prepared |
| README | <icon name="check" color="success" inline /> Draft prepared |
| Final GitHub audit | <icon name="clock" color="secondary" inline /> Pending |
| Release tag | <icon name="clock" color="secondary" inline /> Pending |

## 4. Next: Final GitHub audit

You're currently in the correct folder:

```text
university-timetable-daa %
```

Run:

```bash
git status
git branch -a
git log --oneline -8
git tag
```