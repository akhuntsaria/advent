#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

int main() {
    ifstream file("input8.2.txt");

    unordered_map<char, vector<pair<int, int>>> ants;
    vector<string> map;
    string line;

    while (getline(file, line)) {
        for (int j = 0; j < line.length(); ++j) {
            char c = line[j];
            if (c == '.') continue;
            
            ants[c].push_back({map.size(), j});
        }
        map.push_back(line);
    }

    unordered_set<pair<int, int>, pair_hash> antinodes;
    int width = map[0].length(),
        height = map.size();

    for (const auto& [c, points] : ants) {
        for (int i = 0; i < points.size(); ++i) {
            auto a = points[i];
            for (int j = i + 1; j < points.size(); ++j) {
                auto b = points[j];

                int xd = a.first - b.first;
                int yd = a.second - b.second;

                for (int k = a.first,l = a.second;k >= 0 && k < width && l >= 0 && l < height;k += xd,l += yd) {
                    if (k == b.first && l == b.second) continue;
                    antinodes.insert({k, l});
                }
                for (int k = b.first,l = b.second;k >= 0 && k < width && l >= 0 && l < height;k -= xd,l -= yd) {
                    if (k == a.first && l == a.second) continue;
                    antinodes.insert({k, l});
                }
            }
        }
    }

    cout << antinodes.size() << endl;
    return 0;
}

