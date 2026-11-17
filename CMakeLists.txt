cmake_minimum_required(VERSION 3.16)

project(UniversityTimetableDAA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(timetable
    src/main.cpp
    src/data/DataLoader.cpp
    src/validation/DataValidator.cpp
    src/algorithms/searching/BinarySearch.cpp
    src/algorithms/sorting/MergeSort.cpp
    src/algorithms/sorting/QuickSort.cpp
    src/algorithms/divide_conquer/MaximumSubarray.cpp
    src/algorithms/divide_conquer/FastExponentiation.cpp
    src/timetable/TimetableAllocator.cpp
    src/timetable/TimetableValidator.cpp
    src/timetable/TimetableExporter.cpp
    src/algorithms/greedy/GreedyScheduling.cpp
    src/algorithms/greedy/GraphAlgorithms.cpp
    src/algorithms/greedy/HuffmanCoding.cpp
    src/algorithms/dp/DynamicProgramming.cpp
    src/algorithms/dp/AdvancedDP.cpp
    src/algorithms/backtracking/ExactAlgorithms.cpp
    src/algorithms/extra/ExtraAlgorithms.cpp
    src/timetable/BacktrackingAllocator.cpp
)

add_executable(exact_algorithms_test
    tests/exact_algorithms_test.cpp
    src/algorithms/backtracking/ExactAlgorithms.cpp
)

enable_testing()
add_test(NAME exact_algorithms COMMAND exact_algorithms_test)

add_executable(stress_test
    benchmarks/StressTest.cpp
    src/timetable/TimetableAllocator.cpp
    src/timetable/TimetableValidator.cpp
)