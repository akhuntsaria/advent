#include "util.cpp"

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    unordered_set<vector<int>, vector_hash> locks, 
        keys;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "#####") {
            vector<int> lock(5, 0);
            for (int i = 0;i < 5;i++) {
                getline(file, line);
                for (int j = 0;j < 5;j++) {
                    lock[j] += line[j] == '#';
                }
            }
            locks.insert(lock);
            getline(file, line); // Empty
        } else { // .....
            vector<int> key(5, 0);
            for (int i = 0;i < 5;i++) {
                getline(file, line);
                for (int j = 0;j < 5;j++) {
                    key[j] += line[j] == '#';
                }
            }
            keys.insert(key);
            getline(file, line); // Full
        }
    }

    int res = 0;
    for (auto& key : keys) {
        for (auto& lock : locks) {
            bool fit = true;
            for (int i = 0;i < 5;i++) {
                if (key[i] + lock[i] > 5) {
                    fit = false;
                    break;
                }
            }
            if (fit) res++;
        }
    }
    print(res);
}
/*

*/