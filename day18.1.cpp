#include "util.cpp"

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

bool valid(vector<string>& map, int i, int j) {
    return i >= 0 && j >= 0 && i < map.size() && j < map[i].size() && map[i][j] != '#';
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    // int m = 7, n = 7;
    int m = 71, n = 71;
    vector<string> map(m, string(n, '.'));
    string line;
    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int x, y;
        char trash;
        ss >> x >> trash >> y;
        map[y][x] = '#';
        i++;
        // if (i == 12) break;
        if (i == 1024) break;
    }
    int si = 0, sj = 0, ei = m-1, ej = n-1;

    queue<vector<int>> q;
    q.push({si,sj,0});

    unordered_set<pair<int,int>,pair_hash> v;
    int dist = INT_MAX;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        int i = curr[0], j = curr[1], step = curr[2];

        if (v.contains({i,j})) continue;
        v.insert({i,j});

        if (i == ei && j == ej) {
            dist = step;
            break;
        }

        for (auto& dir : dirs) {
            int ni = i+dir[0], nj = j+dir[1];
            if (valid(map, ni, nj)) {
                q.push({ni, nj, step+1});
            }
        }
    }
    print(dist);

    return 0;
}
/*
Tried: 
146, too low
*/