
# DAA Complexity Analysis Report

## University Timetable and Classroom Allocation Engine

**Language:** C++17  
**Project:** University Timetable and Classroom Allocation Engine

---

# 1. Project Overview

The project generates university timetables using course,
faculty, batch, classroom and time-slot information.

The system supports:

- Greedy timetable generation
- Backtracking-based timetable generation
- Faculty, room and batch conflict detection
- Classroom capacity and laboratory constraints
- Course and timetable searching
- Algorithm performance comparisons
- CSV export and automated testing

The main scheduling problem is a constrained resource
allocation problem.

---

# 2. Inputs and Outputs

## Inputs

- Courses and weekly lecture requirements
- Faculty assignments
- Student batches
- Classrooms and seating capacities
- Laboratory requirements
- Available time slots

## Outputs

- Generated weekly timetable
- Faculty and classroom assignments
- Scheduled and unscheduled lecture counts
- Constraint diagnostics
- Algorithm performance statistics
- Exported CSV timetable

## Hard Constraints

1. A faculty member cannot teach overlapping classes.
2. A batch cannot attend overlapping classes.
3. A classroom cannot host overlapping classes.
4. Classroom capacity must accommodate enrollment.
5. Laboratory courses require suitable laboratory rooms.
6. Each course must receive its required weekly lectures.
7. In the current scheduling policy, a course offering
   cannot have more than one lecture per day.

## Invariants

After every successful assignment:

- Previously assigned lectures remain unchanged.
- No assigned faculty, room or batch has an overlapping
  booking.
- Every assigned lecture uses a suitable classroom.
- The partial timetable satisfies all checked constraints.

The backtracking allocator restores the previous partial
schedule whenever it removes an unsuccessful assignment.

## Edge Cases

- Empty university dataset
- Missing faculty or room references
- Insufficient room capacity
- No suitable laboratory
- Overlapping time intervals
- Insufficient available slots
- Duplicate identifiers
- Impossible scheduling instances
- Backtracking search-limit exhaustion

---

# 3. Asymptotic Complexity

The following table describes the algorithmic implementations
used in the project.

Here, n represents the primary input size unless otherwise
specified.

| Algorithm | Best | Average | Worst | Auxiliary Space |
|---|---|---|---|---|
| Iterative Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| Recursive Binary Search | O(1) | O(log n) | O(log n) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort (last pivot) | O(n log n) | O(n log n) | O(n²) | O(log n) average, O(n) worst |
| Maximum Subarray (D&C) | O(n log n) | O(n log n) | O(n log n) | O(log n) |
| Fast Exponentiation | O(1) for exponent zero | O(log e) | O(log e) | O(log e) |
| Celebrity Identification | O(n) | O(n) | O(n) | O(1) |
| Classical Matrix Multiplication | O(n³) | O(n³) | O(n³) | O(n²) output |
| Strassen Matrix Multiplication | O(n^2.807) | O(n^2.807) | O(n^2.807) | O(n²) auxiliary for standard implementation |
| Activity Selection | O(n) after sorting | O(n) after sorting | O(n) after sorting | O(n) output |
| Interval Partitioning (current implementation) | O(n²) including insertion sort | O(n²) | O(n²) | O(n) |
| Fractional Knapsack (current insertion sort) | O(n) best-case sort + selection | O(n²) | O(n²) | O(n) output |
| Huffman Coding (current linear minimum scans) | O(n + k²) | O(n + k²) | O(n + k²) | O(k) |
| Dijkstra (adjacency matrix) | O(V²) | O(V²) | O(V²) | O(V) auxiliary |
| Prim (adjacency matrix) | O(V²) | O(V²) | O(V²) | O(V) auxiliary |
| Kruskal (insertion sorting) | O(E + Eα(V)) best-case sorting | O(E² + Eα(V)) | O(E² + Eα(V)) | O(V + E) |
| 0/1 Knapsack DP | O(nW) | O(nW) | O(nW) | O(nW) |
| Matrix Chain Multiplication DP | O(n³) | O(n³) | O(n³) | O(n²) |
| LCS | O(mn) | O(mn) | O(mn) | O(mn) |
| Optimal BST DP | O(n³) | O(n³) | O(n³) | O(n²) |
| Bellman-Ford | O(E) with early stopping | O(VE) | O(VE) | O(V) |
| Floyd-Warshall | O(V³) | O(V³) | O(V³) | O(V²) |
| TSP Bitmask DP | O(n² 2^n) | O(n² 2^n) | O(n² 2^n) | O(n 2^n) |
| Naive String Matching | O(n) for fixed m | O(nm) worst-case bound | O(nm) | O(1) excluding matches |
| Rabin-Karp | O(n+m) expected | O(n+m) expected | O(nm) | O(1) excluding matches |
| Finite Automaton (current construction) | O(n + 256m³) upper bound | O(n + 256m³) upper bound | O(n + 256m³) | O(256m) |
| KMP | O(n+m) | O(n+m) | O(n+m) | O(m) |

Notation:

- V = number of vertices
- E = number of edges
- W = knapsack capacity
- m = pattern length or second sequence length
- k = number of distinct Huffman symbols
- e = exponent
- α(V) = inverse Ackermann function

The table uses O notation for upper bounds.
For tight bounds, Θ notation should be used where the
algorithm performs the stated amount of work for the
specified input model.

---

# 4. Recurrence Relations

## 4.1 Binary Search — Iteration Method

Binary Search repeatedly reduces the search space by half.

T(n) = T(n/2) + c

Expanding:

T(n) = T(n/4) + 2c

T(n) = T(n/8) + 3c

After k iterations:

T(n) = T(n/2^k) + kc

The recursion stops when:

n/2^k = 1

Therefore:

k = log₂ n

Hence:

T(n) = Θ(log n)

The iterative version uses constant auxiliary memory.
The recursive version requires logarithmic stack space.

---

## 4.2 Merge Sort — Master Theorem

Merge Sort divides the array into two approximately
equal halves and merges them in linear time.

T(n) = 2T(n/2) + Θ(n)

Master Theorem parameters:

a = 2
b = 2
f(n) = Θ(n)

n^(log_b a) = n

This is Master Theorem Case 2.

Therefore:

T(n) = Θ(n log n)

---

## 4.3 Merge Sort — Recursion Tree

At each level, the total merging work is Θ(n).

Level 0: n

Level 1: n/2 + n/2 = n

Level 2: 4(n/4) = n

The recursion tree has Θ(log n) levels.

Total work:

n × log₂ n

Therefore:

T(n) = Θ(n log n)

---

## 4.4 Quick Sort — Worst Case

Our implementation selects the last element as pivot.

For already sorted input, partitioning produces
subproblems of sizes n-1 and 0.

T(n) = T(n-1) + Θ(n)

Expanding:

T(n) = n + (n-1) + (n-2) + ... + 1

Using the arithmetic series:

T(n) = n(n+1)/2

Therefore:

T(n) = Θ(n²)

The standard Master Theorem cannot be applied directly
because this recurrence does not divide the input by
a constant factor.

---

## 4.5 Quick Sort — Balanced Case

With balanced partitions:

T(n) = 2T(n/2) + Θ(n)

Therefore:

T(n) = Θ(n log n)

The expected complexity under suitable random-input
assumptions is also Θ(n log n).

---

## 4.6 Maximum Subarray — Substitution Method

The divide-and-conquer implementation solves two
half-sized problems and computes the best crossing
subarray in linear time.

T(n) = 2T(n/2) + cn

Assume:

T(n) ≤ an log₂ n

Substituting:

T(n) ≤ 2a(n/2)log₂(n/2) + cn

T(n) ≤ an(log₂ n - 1) + cn

T(n) ≤ an log₂ n + (c-a)n

For a ≥ c, the upper bound holds, with a suitable
base-case constant.

The recursion tree supplies a matching lower bound.

Therefore:

T(n) = Θ(n log n)

---

## 4.7 Fast Exponentiation

Exponentiation by squaring reduces the exponent by half.

T(e) = T(e/2) + Θ(1)

By repeated substitution:

T(e) = T(e/2^k) + Θ(k)

The recursion reaches its base case after Θ(log e)
levels for positive exponents.

Therefore:

T(e) = Θ(log e)

---

## 4.8 Strassen Matrix Multiplication

Strassen performs seven recursive matrix multiplications
instead of eight.

T(n) = 7T(n/2) + Θ(n²)

Master Theorem:

a = 7
b = 2

n^(log₂ 7) ≈ n^2.807

Since n² grows polynomially more slowly than
n^(log₂ 7), Master Theorem Case 1 applies.

Therefore:

T(n) = Θ(n^2.807)

This assumes the standard recursive Strassen structure
with matrix addition and subtraction work of Θ(n²).

---

# 5. Greedy vs Backtracking

The project implements two timetable generation strategies.

## Greedy Allocation

The Greedy allocator examines candidate rooms and time
slots and accepts the first assignment satisfying its
constraints.

Advantages:

- Simple implementation
- Fast on the tested dataset
- Produces a useful initial timetable

Limitations:

- Does not reconsider earlier decisions
- May fail to schedule all lectures even when a complete
  timetable exists
- Does not guarantee an optimal timetable

## Backtracking Allocation

Backtracking recursively assigns lectures.

If a later assignment fails, the algorithm removes an
earlier assignment and explores another possibility.

Advantages:

- Can reconsider earlier decisions
- Can find a complete schedule when one exists and
  the search is allowed to finish

Limitations:

- Exponential worst-case search
- Can consume substantial time and stack memory
- The implementation uses a search-node limit

A search-limit result is inconclusive and must not be
reported as proof that no feasible timetable exists.

---

# 6. Experimental Results

## 6.1 Normal Scenario

Required lectures: 24

| Metric | Greedy | Backtracking |
|---|---:|---:|
| Scheduled lectures | 24 | 24 |
| Valid timetable | Yes | Yes |
| Candidate checks | 594 | 594 |
| Execution time (ms) | 0.276708 | 0.667625 |

Both algorithms produced valid complete schedules.

Backtracking performed no necessary reversal of earlier
decisions in this scenario, so the candidate counts
were identical.

Greedy had lower execution time in this measurement.

## 6.2 Reduced-Room Scenario

| Metric | Greedy | Backtracking |
|---|---:|---:|
| Scheduled lectures | 24 | 24 |
| Candidate checks | 300 | 300 |
| Execution time (ms) | 0.203 | 0.428042 |

Both algorithms completed the reduced-room scenario.

This experiment did not force Greedy to fail.

Independent validation of the reduced-room outputs
should be recorded before claiming full correctness.

## 6.3 Stress Testing

| Courses | Rooms | Required | Scheduled | Checks | Time (ms) |
|---:|---:|---:|---:|---:|---:|
| 30 | 10 | 90 | 90 | 8,595 | 8.85054 |
| 150 | 30 | 450 | 450 | 141,975 | 209.485 |
| 300 | 60 | 900 | 900 | 567,450 | 1437.55 |

The smallest stress-test dataset passed independent
timetable validation.

The medium and large cases completed allocation but
did not undergo the full independent validation.

These results show increasing execution time and
candidate checks with dataset size.

Three observations are insufficient to establish an
empirical tight asymptotic bound.

---

# 7. Complexity Classes

## P

Problems solvable in polynomial time by deterministic
algorithms.

Examples include:

- Sorting
- Binary Search on sorted data
- Shortest paths with non-negative weights
- Maximum bipartite matching

## NP

Decision problems for which a proposed solution can be
verified in polynomial time.

A complete timetable can be verified by checking every
assignment and its constraints.

## NP-Complete

A decision problem is NP-complete if it belongs to NP
and is NP-hard.

A generalized university timetable feasibility problem
is NP-complete when it includes sufficiently general
conflict constraints.

## NP-Hard

Optimization problems can be NP-hard even when they
are not decision problems.

Finding a timetable minimizing a sufficiently general
combination of penalties while satisfying hard constraints
is an NP-hard optimization problem.

---

# 8. Reduction from Graph Coloring

We show a polynomial-time reduction from graph coloring
to a generalized timetable feasibility problem.

Given:

- An undirected graph G = (V, E)
- A positive integer k representing available colors

Construct a timetable instance:

1. Create one lecture for every vertex in V.
2. Create k available time slots.
3. For every graph edge (u,v), introduce a scheduling
   conflict requiring lectures u and v to occupy
   different time slots.
4. Provide sufficient room resources so room capacity
   does not introduce additional restrictions.

Each graph color corresponds to one time slot.

If the graph has a valid k-coloring, assign every lecture
to the time slot corresponding to its color.

Adjacent vertices have different colors, so conflicting
lectures receive different time slots.

Conversely, if the constructed timetable is feasible,
assign each vertex the color corresponding to its
lecture's time slot.

Conflicting lectures use different slots, so this is
a valid k-coloring.

Therefore:

G is k-colorable if and only if the constructed timetable
is feasible.

The construction requires polynomial time.

For k ≥ 3, graph k-colorability is NP-complete.

Therefore, generalized timetable feasibility with
arbitrary pairwise lecture conflicts is NP-hard.

Since a proposed timetable can be checked in polynomial
time, its decision version is NP-complete.

Important qualification:

This reduction applies to the generalized scheduling
model supporting arbitrary pairwise conflicts. Our
current application primarily models faculty, batch,
room and lab constraints. The reduction does not by
itself establish NP-completeness for every restricted
version of our current implementation.

---

# 9. Algorithm Selection Guide

| Problem | Recommended approach | Reason |
|---|---|---|
| Initial timetable generation | Greedy | Fast and simple baseline |
| Recovering from failed assignments | Backtracking | Can reconsider earlier decisions |
| Sorting course records | Merge Sort | Predictable worst-case behavior |
| Searching sorted course IDs | Binary Search | Logarithmic search |
| Searching timetable text | KMP | Linear-time matching |
| Campus shortest routes | Dijkstra | Non-negative weighted paths |
| Minimum campus infrastructure | Prim or Kruskal | Minimum spanning tree |
| Faculty-course assignment | Bipartite Matching | Maximum compatible assignment |
| Capacity-constrained network allocation | Ford-Fulkerson | Maximum flow |
| Small exact routing problem | TSP Bitmask DP | Optimal solution for bounded size |

---

# 10. Limitations

1. The timetable allocator currently uses a basic greedy
   strategy and does not guarantee optimal utilization.
2. The backtracking allocator has exponential worst-case
   behavior and uses a search limit.
3. Faculty availability and preferences are not fully modeled.
4. Large stress-test outputs need independent validation.
5. Memory instrumentation is incomplete for some algorithms.
6. Some algorithms use analytical test inputs rather than
   being directly integrated into timetable generation.
7. The finite-automaton implementation has expensive
   preprocessing.
8. The current search is case-sensitive.
9. The present benchmark measurements are single-run results
   rather than repeated statistical measurements.

---

# 11. Ethical and Practical Considerations

Automated scheduling should not unfairly assign inconvenient
periods to particular faculty members or student batches.

A production system should consider:

- Faculty workload balance
- Accessibility requirements
- Student timetable gaps
- Laboratory availability
- Manual review and override
- Privacy of student and faculty information

The generated timetable should be reviewed before official
publication.

---

# 12. Conclusion

The project demonstrates how algorithm design techniques
can support university scheduling and resource allocation.

Greedy allocation successfully generated complete schedules
for the tested university datasets.

Backtracking provides an alternative approach capable of
reconsidering assignments when a greedy choice causes a
later conflict.

Additional algorithms support searching, graph routing,
resource allocation, optimization and complexity analysis.

The experimental results demonstrate successful allocation
on the tested inputs, while the theoretical analysis
explains the performance characteristics and limitations
of the chosen algorithms.
