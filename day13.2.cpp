#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

typedef long long i64;

using namespace std;

pair<int, int> parse_line(string& line, char sep) {
    int first, second;
    char discard;

    stringstream ss(line);
    do {
        ss >> discard;
    } while (discard != sep);
    ss >> first;

    do {
        ss >> discard;
    } while (discard != sep);
    ss >> second;

    return {first, second};
}

i64 cramer(int adx, int ady, int bdx, int bdy, i64 px, i64 py) {
    i64 det = adx * bdy - bdx * ady;

    i64 a = bdy * px - bdx * py;
    if (a % det != 0) return 0;

    i64 b = adx * py - ady * px;
    if (b % det != 0) return 0;

    a /= det;
    b /= det;
    return a * 3 + b;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    i64 sum = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        auto [adx, ady] = parse_line(line, '+');
        
        getline(file, line);
        auto [bdx, bdy] = parse_line(line, '+');

        getline(file, line);
        auto [px, py] = parse_line(line, '=');

        sum += cramer(adx, ady, bdx, bdy, px + 10000000000000ll, py + 10000000000000ll);
    }
    cout << sum << endl;
    return 0;
}
/*
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

8400/22 
5400/34

94a + 22b = 8400
34a + 67b = 5400

det 94 * 67 - 34 * 22
a (67 * 8400 - 22 * 5400) / (94 * 67 - 34 * 22)
b (94 * 5400 - 34 * 8400) / (94 * 67 - 34 * 22)
*/