#include "util.cpp"

int MOD = 16777216;

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string line;
    u64 res = 0;
    while (getline(file, line)) {
        u64 secret = stoull(line);
        cout << secret << endl;

        for (int i = 0;i < 2000;i++) {
            secret = ((secret * 64) ^ secret) % MOD;
            secret = ((secret / 32) ^ secret) % MOD;
            secret = ((secret * 2048) ^ secret) % MOD;
        }
        res += secret;
    }
    cout << res << endl; 
    return 0;
}
/*

*/