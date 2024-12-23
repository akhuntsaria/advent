#include "util.cpp"

struct state {
    int i, j, dir, points;
    vector<pair<int,int>> path;
};

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

bool valid(vector<string>& map, int i, int j) {
    return i >= 0 && j >= 0 && i < map.size() && j < map[i].size() && map[i][j] != '#';
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> map;
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }
    int m = map.size(), n = map[0].size(), si = m - 2, sj = 1;

    queue<state> q;
    q.push({si,sj,1,0,{{si,sj}}});

    unordered_map<vector<int>,int,vector_hash> v;
    unordered_set<pair<int,int>,pair_hash> best;

    int minp = INT_MAX;

    while (!q.empty()) {
        auto c = q.front();
        q.pop();

        vector<int> key = {c.i,c.j,c.dir};
        if (v.contains(key) && c.points > v[key]) continue;
        v[key] = c.points;

        if (map[c.i][c.j] == 'E') {
            if (c.points < minp) {
                best.clear();
                minp = c.points;
            }
            if (c.points == minp) {
                best.insert(c.path.begin(), c.path.end());
            }
            continue;
        }

        int ni = c.i + dirs[c.dir][0],
            nj = c.j + dirs[c.dir][1];
        if (valid(map, ni, nj)) {
            auto new_path = c.path;
            new_path.push_back({ni,nj});
            q.push({ni, nj, c.dir, c.points + 1, new_path});
        }

        for (int rot : {-1, 1}) {
            auto ndir = (c.dir + rot + 4) % 4;
            ni = c.i + dirs[ndir][0];
            nj = c.j + dirs[ndir][1];
            if (!valid(map, ni, nj)) continue;
            auto new_path = c.path;
            new_path.push_back({ni,nj});
            q.push({ni, nj, ndir, c.points + 1001, new_path});
        }
    }
    cout << best.size() << endl;

    return 0;
}
