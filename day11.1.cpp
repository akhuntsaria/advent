#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

typedef unsigned long long u64;

using namespace std;

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<u64> stones;
    u64 stone;
    while (file >> stone) {
        stones.push_back(stone);
    }

    for (int i = 0; i < 25; i++) {
        vector<u64> new_stones;
        for (auto stone : stones) {
            if (stone == 0) {
                new_stones.push_back(1);
            } else {
                string str = to_string(stone);
                if (str.length() % 2 == 0) {
                    auto mid = str.length() / 2;
                    new_stones.push_back(stoull(str.substr(0, mid)));
                    new_stones.push_back(stoull(str.substr(mid)));
                } else {
                    new_stones.push_back(stone * 2024);
                }
            }
        }
        stones = new_stones;
    }

    cout << stones.size() << endl;

    return 0;
}