#include "util.cpp"

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

    auto cmp = [](vector<int>& left, vector<int>& right) { return left[3] > right[3]; };
    priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> q(cmp);
    q.push({si,sj,1,0});

    unordered_set<vector<int>,vector_hash> v;

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        int i = curr[0], j = curr[1], d = curr[2], p = curr[3];

        if (map[i][j] == 'E') {
            cout << p << endl;
            break;
        }

        if (v.contains({i,j})) continue;
        v.insert({i,j});

        int ni = i+dirs[d][0], nj = j+dirs[d][1];
        if (valid(map, ni, nj)) {
            q.push({ni, nj, d, p+1});
        }
        
        for (int rot : {-1, 1}) {
            auto nd = (d + rot + 4) % 4;
            ni = i + dirs[nd][0];
            nj = j + dirs[nd][1];
            if (!valid(map, ni, nj)) continue;
            q.push({ni, nj, nd, p+1001});
        }
    }

    return 0;
}
