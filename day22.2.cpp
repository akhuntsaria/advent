#include "util.cpp"

int MOD = 16777216;

u64 step(u64 secret) {
    secret = ((secret * 64) ^ secret) % MOD;
    secret = ((secret / 32) ^ secret) % MOD;
    secret = ((secret * 2048) ^ secret) % MOD;
    return secret;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string line;
    vector<vector<int>> secrets;
    int i = 0;
    
    while (getline(file, line)) {
        u64 secret = stoull(line);
        secrets.push_back(vector<int>());
        secrets[i].push_back(secret%10);
        for (int j = 0;j < 2000;j++) {
            secret = step(secret);
            secrets[i].push_back(secret%10);
        }
        i++;
    }

    int res = 0;
    unordered_map<vector<int>,int,vector_hash> sequences; // seq -> sum
    for (i = 0;i < secrets.size();i++) {
        unordered_set<vector<int>,vector_hash> visited;
        for (int j = 4;j < secrets[i].size();j++) {
            vector<int> seq;
            for (int k = 3;k >= 0;k--) {
                seq.push_back(secrets[i][j-k] - secrets[i][j-k-1]);
            }
            if (visited.contains(seq)) continue;
            visited.insert(seq);
            sequences[seq] += secrets[i][j];
            res = max(res, sequences[seq]);
        }
    }
    print(res);
    return 0;
}
/*
Map of 4-sequences?

Tried:
1475
*/