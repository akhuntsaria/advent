#include <deque>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

typedef unordered_set<pair<int,int>,pair_hash> pair_set;

int minp = INT_MAX;

void walk(vector<string>& map, 
          pair_set& best, 
          pair_set& path, 
          vector<vector<vector<int>>>& points, 
          int i, int j, int dir, int p) {

    int m = map.size(), n = map[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || map[i][j] == '#' 
        || path.contains({i,j}) || points[i][j][dir] < p) return;
    points[i][j][dir] = p;

    if (map[i][j] == 'E') {
        if (p < minp) {
            best.clear();
            minp = p;
        }
        for (auto& tile : path) {
            best.insert(tile);
        }
        return;
    }
    path.insert({i,j});
    walk(map, best, path, points, i-1, j, 0, p + (dir == 0 ? 1 : 1001));
    walk(map, best, path, points, i, j+1, 1, p + (dir == 1 ? 1 : 1001));
    walk(map, best, path, points, i+1, j, 2, p + (dir == 2 ? 1 : 1001));
    walk(map, best, path, points, i, j-1, 3, p + (dir == 3 ? 1 : 1001));
    path.erase({i,j});
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> map;
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }
    int m = map.size(), n = map[0].size(), si = m - 2, sj = 1, ei = 1, ej = n - 2, dir = 1;

    vector<vector<vector<int>>> points(m, vector<vector<int>>(n, vector<int>(4, INT_MAX)));
    unordered_set<pair<int,int>,pair_hash> best, path;

    walk(map, best, path, points, si, sj, 1, 0);

    best.insert({ei,ej});
    cout << best.size() << endl;
    return 0;
}
/*
each cell, each direction -> points

###############
#.......#....O#
#.#.###.#.###O#
#.....#.#...#O#
#.###.#####.#O#
#.#.#.......#O#
#.#.#####.###O#
#..OOOOOOOOO#O#
###O#O#####O#O#
#OOO#O....#O#O#
#O#O#O###.#O#O#
#OOOOO#...#O#O#
#O###.#.#.#O#O#
#O..#.....#OOO#
###############
*/