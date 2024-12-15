#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    int n = 101,m = 103;
    unordered_map<pair<int,int>,int,pair_hash> map;
    string line;
    while (getline(file, line)) {
        char discard;

        stringstream ss(line);
        do {
            ss >> discard;
        } while (discard != '=');
        int x, y, vx, vy;
        ss >> x >> discard >> y;

        do {
            ss >> discard;
        } while (discard != '=');
        ss >> vx >> discard >> vy;

        x += (vx * 100) % n;
        y += (vy * 100) % m;

        if (x < 0) {
            x = n + x;
        }
        if (y < 0) {
            y = m + y;
        }
        if (x >= n) {
            x = x % n;
        }
        if (y >= m) {
            y = y % m;
        }

        map[{x,y}]++;
    }

    int qs[4] = {0};
    for (auto const& [p, count] : map) {
        if (p.first < n / 2 && p.second < m / 2) {
            qs[0] += count;
        } else if (p.first > n / 2 && p.second < m / 2) {
            qs[1] += count;
        } else if (p.first < n / 2 && p.second > m / 2) {
            qs[2] += count;
        } else if (p.first > n / 2 && p.second > m / 2) {
            qs[3] += count;
        }
    }
    cout << qs[0] * qs[1] * qs[2] * qs[3] << endl;
    return 0;
}
/*
230436441
*/