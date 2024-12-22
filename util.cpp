#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long u64;

template <typename T>
bool eq(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0;i < a.size();i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template <typename T>
void print(T param) {
    cout << param << endl;
}

template <typename K, typename V>
void print(const map<K, V>& map) {
    for (const auto& pair : map) {
        cout << pair.first << ':' << pair.second << ' ';
    }
    cout << endl;
}

template <typename K, typename V>
void print(const unordered_map<K, V>& map) {
    for (const auto& pair : map) {
        cout << pair.first << ':' << pair.second << ' ';
    }
    cout << endl;
}

template <typename T>
void print(const vector<T>& vec) {
    for (const auto& element : vec) {
        cout << element << ' ';
    }
    cout << endl;
}

template <typename T>
void print(const vector<vector<T>>& vec) {
    for (const auto& inner : vec) {
        for (const auto& element : inner) {
            cout << element << ' ';
        }
        cout << endl;
    }
}

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

struct vector_hash {
    inline size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (auto n : v) h = h * 31 + n;
        return h;
    }
};
