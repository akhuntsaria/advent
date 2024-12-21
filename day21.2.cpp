#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long u64;

unordered_map<char, pair<int,int>> numpad = {
    {'7', {3, 0}}, {'8', {3, 1}}, {'9', {3, 2}},
    {'4', {2, 0}}, {'5', {2, 1}}, {'6', {2, 2}},
    {'1', {1, 0}}, {'2', {1, 1}}, {'3', {1, 2}},
                   {'0', {0, 1}}, {'A', {0, 2}}
};

unordered_map<char, pair<int,int>> dirpad = {
                   {'^', {1, 1}}, {'A', {1, 2}}, 
    {'<', {0, 0}}, {'v', {0, 1}}, {'>', {0, 2}}
};

unordered_map<string, u64> min_dirpad_path_sizes;

void numpad_paths(pair<int,int> from,pair<int,int> to, vector<string>& paths, string path) {
    if (from.first == 0 && from.second == 0) return;
    if (from.first == to.first && from.second == to.second) {
        path += 'A';
        paths.push_back(path);
        return;
    }

    if (from.first < to.first) numpad_paths({from.first+1,from.second}, to, paths, path + '^');
    if (from.first > to.first) numpad_paths({from.first-1,from.second}, to, paths, path + 'v'); 
    if (from.second < to.second) numpad_paths({from.first,from.second+1}, to, paths, path + '>');
    if (from.second > to.second) numpad_paths({from.first,from.second-1}, to, paths, path + '<'); 
}

int dirpad_paths(pair<int,int> from,pair<int,int> to, vector<string>& paths, string path) {
    if (from.first == 1 && from.second == 0) return INT_MAX;
    if (from.first == to.first && from.second == to.second) {
        path += 'A';
        paths.push_back(path);
        return path.size();
    }

    int res = INT_MAX;
    if (from.first < to.first) res = min(res, dirpad_paths({from.first+1,from.second}, to, paths, path + '^'));
    if (from.first > to.first) res = min(res, dirpad_paths({from.first-1,from.second}, to, paths, path + 'v'));  
    if (from.second < to.second) res = min(res, dirpad_paths({from.first,from.second+1}, to, paths, path + '>'));
    if (from.second > to.second) res = min(res, dirpad_paths({from.first,from.second-1}, to, paths, path + '<')); 
    return res;
}

u64 min_dirpad_path_size(string& path, int step) {
    if (step == 0) return path.size();

    string cache_key = path + ":" + to_string(step);
    if (min_dirpad_path_sizes.contains(cache_key)) {
        return min_dirpad_path_sizes[cache_key];
    }

    char from = 'A';
    u64 total_path_size = 0;
    for (int i = 0;i < path.size();i++) {
        vector<string> next_part_paths;
        dirpad_paths(dirpad[from], dirpad[path[i]], next_part_paths, "");
        u64 min_next_part_size = ULLONG_MAX;
        for (string& next_part_path : next_part_paths) {
            min_next_part_size = min(min_next_part_size, min_dirpad_path_size(next_part_path, step-1));
        }
        from = path[i];
        total_path_size += min_next_part_size;
    }

    return min_dirpad_path_sizes[cache_key] = total_path_size;
}

u64 min_numpad_path_size(char fc, char tc) {
    pair<int,int> from = numpad[fc], to = numpad[tc];

    vector<string> paths;
    numpad_paths(from, to, paths, "");
    u64 min_path_size = ULLONG_MAX;
    for (string& path : paths) {
        min_path_size = min(min_path_size, min_dirpad_path_size(path, 25));
    }
    return min_path_size;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string code;
    u64 res = 0;
    while (getline(file, code)) {
        char from = 'A';
        u64 size = 0;
        for (int i = 0;i < code.size();i++) {                    
            size += min_numpad_path_size(from, code[i]);
            from = code[i];
        }
        res += stoi(code) * size;
    }
    cout << res << endl;
    return 0;
}
/*
*/