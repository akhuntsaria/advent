#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

typedef unsigned long long u64;

using namespace std;

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};
int n, m;

// Either an edge or a different plant
bool is_side(vector<string>& map, int i, int j, char c) {
    if (i < 0 || j < 0 || i >= n || j >= m) return true;
    if (map[i][j] != c) return true;
    return false;
}

set<int> sides(vector<string>& map, int i, int j, char prev) {
    set<int> result;
    if (i < 0 || j < 0 || i >= n || j >= m) return result;
    
    char c = map[i][j];
    if (prev != c) return result;
    
    for (int dir_idx = 0; dir_idx < dirs.size(); dir_idx++) {
        auto dir = dirs[dir_idx];
        if (is_side(map, i + dir[0], j + dir[1], c)) {
            result.insert(dir_idx);
        }
    }
    
    return result;
}

// Returns area and perimeter
pair<int, int> walk(vector<string>& map, int i, int j, vector<vector<bool>>& v, char prev) {
    if (i < 0 || j < 0 || i >= n || j >= m || v[i][j] || map[i][j] != prev) return {0, 0};
    
    v[i][j] = true;
    char c = map[i][j];
    pair<int, int> res = {1, 0};

    for (int dir_idx = 0; dir_idx < dirs.size(); dir_idx++) {
        auto dir = dirs[dir_idx];
        if (!is_side(map, i + dir[0], j + dir[1], c)) continue;
        
        vector<vector<int>> flanks = {
            {dir[0] == 0 ? -1 : 0, dir[1] == 0 ? -1 : 0},
            {dir[0] == 0 ? 1 : 0, dir[1] == 0 ? 1 : 0}
        };
        
        bool new_side = true;
        for (auto& flank : flanks) {
            if (!new_side) break;
            
            // Go along the side and check if it was already considered
            // The worst case is slow
            int ni = i + flank[0], nj = j + flank[1];
            while (true) {
                if (!sides(map, ni, nj, c).count(dir_idx)) break;
                if (v[ni][nj]) {
                    new_side = false;
                    break;
                }
                ni += flank[0];
                nj += flank[1];
            }
        }
        
        if (new_side) res.second++;
    }
    
    for (auto& dir : dirs) {
        auto next = walk(map, i + dir[0], j + dir[1], v, c);
        res.first += next.first;
        res.second += next.second;
    }
    
    return res;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> map;
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    n = map.size();
    m = map[0].size();
    vector<vector<bool>> v(n, vector<bool>(m));
    u64 sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto res = walk(map, i, j, v, map[i][j]);
            sum += res.first * res.second;
        }
    }
    
    cout << sum << endl;
    return 0;
}
/*
c
cc
 c

Side = perimeter increase in the same way, direction

Side set
Store start and end coords?

If already visited and part of the same side - don't increase sides

912002
*/