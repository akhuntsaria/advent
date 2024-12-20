#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long u64;

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    unordered_set<string> avail;

    string line;
    getline(file, line);
    for (int i = 0;i < line.size();) {
        int next = line.find(", ", i);
        string design = line.substr(i, next-i);
        avail.insert(design);

        if (next == string::npos) break;
        i = next + 2;
    }

    u64 res = 0;
    getline(file, line); // Empty line
    while (getline(file, line)) {
        vector<u64> dp(line.size());
        for (int i = 0;i < line.size();i++) {
            if (i != 0 && dp[i-1] == 0) continue;
            for (int len = 1;len <= line.size() - i;len++) {
                string part = line.substr(i, len);
                if (avail.contains(part)) {
                    dp[i + len - 1] += i == 0 ? 1 : dp[i-1];
                }
            }
        }
        res += dp[line.size()-1];
    }
    cout << res << endl;
    
    return 0;
}
/*
16016658540
*/