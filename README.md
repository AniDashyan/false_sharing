# False Sharing Demonstration

## Overview

This project demonstrates the performance impact of false sharing in multi-threaded applications. It compares the execution time of incrementing two counters stored in adjacent memory (prone to false sharing) versus counters separated by padding to reside in distinct cache lines. The program runs counter updates in single-threaded and multi-threaded scenarios, measuring and averaging execution times over multiple runs.

## Build & Run

### Clone and Build the Project
```bash
git clone https://github.com/AniDashyan/false_sharing.git
cd false_sharing

cmake -S . -B build
cmake --build build --config Release
```

### Run the Executable

```bash
./build/false_sharing --iter [N] --runs [M]
```

### Command-Line Options

- `--iter [N]`: Specifies the number of iterations for each counter increment (default: 100,000,000).
- `--runs [M]`: Specifies the number of runs to average the execution times (default: 5).

## Example Output

Running the program with default settings (`--iter 100000000 --runs 5`) might produce output like this:

```
Run  1 :
Non-threaded time:  115  ms
Threaded (false sharing) time:  176  ms
Threaded (padded) time:  51  ms

Run  2 :
Non-threaded time:  95  ms
Threaded (false sharing) time:  186  ms
Threaded (padded) time:  54  ms

Run  3 :
Non-threaded time:  97  ms
Threaded (false sharing) time:  173  ms
Threaded (padded) time:  57  ms

Run  4 :
Non-threaded time:  124  ms
Threaded (false sharing) time:  178  ms
Threaded (padded) time:  50  ms

Run  5 :
Non-threaded time:  106  ms
Threaded (false sharing) time:  168  ms
Threaded (padded) time:  48  ms

Average times over  5  runs:
Non-threaded:  107  ms
Threaded (false sharing):  176  ms
Threaded (padded):  52  ms
```

## How Does It Work?

The program illustrates false sharing by comparing two counter structures:

- **CountersAdjacent**: Stores two integers (`x` and `y`) in adjacent memory, likely sharing the same cache line. When multiple threads update these counters concurrently, they compete for the same cache line, causing false sharing and performance degradation due to cache coherence protocols.

- **CountersPadded**: Adds padding (64 bytes, typical cache line size) between `x` and `y`, ensuring each counter resides in a separate cache line, reducing contention.

The program performs the following steps:

1. Runs a non-threaded test where one thread updates both counters sequentially.
2. Runs a threaded (adjacent) test where two threads update the adjacent counters, triggering false sharing.
3. Runs a threaded (padded) test where two threads update padded counters, avoiding false sharing.
4. Measures execution times using a timer and averages results over multiple runs.

The padded version typically runs faster than the adjacent version in the threaded case, demonstrating the performance cost of false sharing and the benefit of aligning data to cache lines.
```
