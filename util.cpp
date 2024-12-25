#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
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

template <typename... Args>
void print(const Args&... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template <typename T>
void print(pair<T,T> p) {
    cout << p.first << ':' << p.second << endl;
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
void print(const unordered_set<T>& set) {
    for (const auto& e : set) {
        cout << e << ' ';
    }
    cout << endl;
}

template <typename T>
struct is_pair : false_type {};

template <typename T1, typename T2>
struct is_pair<pair<T1, T2>> : true_type {};

template <typename T>
void print(const vector<T>& vec) {
    for (const auto& element : vec) {
        if constexpr (is_pair<T>::value) {
            cout << '(' << element.first << ", " << element.second << ") ";
        } else {
            cout << element << ' ';
        }
    }
    cout << endl;
}

template <typename T>
void print(const vector<vector<T>>& vec) {
    for (const auto& inner : vec) {
        print(inner);
    }
}

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

struct vector_hash {
    template <typename T>
    inline size_t operator()(const vector<T>& v) const {
        size_t h = 0;
        hash<T> hasher;
        for (const T& e : v) {
            h ^= hasher(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
