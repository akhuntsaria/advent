#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

void walk(vector<string>& map, vector<vector<int>>& points, int i, int j, int dir, int p) {
    int m = map.size(), n = map[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || map[i][j] == '#' || points[i][j] <= p) return;
    points[i][j] = p;
    walk(map, points, i-1, j, 0, p + (dir == 0 ? 1 : 1001));
    walk(map, points, i, j+1, 1, p + (dir == 1 ? 1 : 1001));
    walk(map, points, i+1, j, 2, p + (dir == 2 ? 1 : 1001));
    walk(map, points, i, j-1, 3, p + (dir == 3 ? 1 : 1001));
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> map;
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }
    int m = map.size(), n = map[0].size(), si = m - 2, sj = 1, ei = 1, ej = n - 2;

    vector<vector<int>> points(m, vector<int>(n, INT_MAX));
    walk(map, points, si, sj, 1, 0);
    cout << points[ei][ej] << endl;
    return 0;
}
/*

###############
#.......#....E#
#.#.###.#.###^#
#.....#.#...#^#
#.###.#####.#^#
#.#.#.......#^#
#.#.#####.###^#
#..>>>>>>>>v#^#
###^#.#####v#^#
#>>^#.....#v#^#
#^#.#.###.#v#^#
#^....#...#v#^#
#^###.#.#.#v#^#
#S..#.....#>>^#
###############
*/