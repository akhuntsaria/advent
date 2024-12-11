#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

typedef unsigned long long u64;

using namespace std;

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    unordered_map<u64,u64> counts;
    u64 stone;
    while (file >> stone) {
        counts[stone] += 1;
    }

    for (int i = 0; i < 75; i++) {
        unordered_map<u64,u64> new_counts;
        for (const auto& [stone, count] : counts) {
            if (stone == 0) {
                new_counts[1] += count;
            } else {
                string str = to_string(stone);
                if (str.length() % 2 == 0) {
                    auto mid = str.length() / 2;
                    auto n1 = stoull(str.substr(0, mid)),
                        n2 = stoull(str.substr(mid));
                    new_counts[n1] += count;
                    new_counts[n2] += count;
                } else {
                    new_counts[stone * 2024] += count;
                }
            }
        }
        new_counts.swap(counts);
    }

    u64 total = 0;
    for (const auto& [key, value] : counts) {
        total += value;
    }
    cout << total << endl;

    return 0;
}
/*
0 -> 1 -> 2024 -> 20 24 -> 2 0 2 4 -> 4048 1 4048 8096 -> 40 48 2024 40 48 80 96 -> 4 0 4 8 20 24 4 0 4 8 8 0 9 6

Memoize?
DP?
Precalc?
Graph with nodes as cached values?
Parallel?

Initial order doesn't matter

counts by step
0
1

0 1
1 1

0 1 2024
1 1 1

0 1 20 24 2024
1 1 1  1  1

Cache both value and step
Unique nums only

Calculate only if the step is new
Count of repeated elements instead of storing them

539803843
 */