#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

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

                vector<pair<int, int>> curr = {
                    {a.first + xd, a.second + yd},
                    {b.first - xd, b.second - yd}
                };

                for (const auto& p : curr) {
                    if (p.first >= 0 && p.first < height && p.second >= 0 && p.second < width) {
                        antinodes.insert(p);
                    }
                }
            }
        }
    }

    cout << antinodes.size() << endl;
    return 0;
}

