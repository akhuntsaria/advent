#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

int min_tokens(int adx, int ady, int bdx, int bdy, int px, int py) {
    auto tokens = INT_MAX;
    for (int a = 0;a < max(px / adx, py / ady);a++) {
        for (int b = 0;b < max(px / bdx, py / bdy);b++) {
            if (adx * a + bdx * b == px && ady * a + bdy * b == py) {
                tokens = min(tokens, a * 3 + b);
            }
        }
    }
    return tokens == INT_MAX ? 0 : tokens;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    int sum = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        auto [adx, ady] = parse_line(line, '+');
        
        getline(file, line);
        auto [bdx, bdy] = parse_line(line, '+');

        getline(file, line);
        auto [px, py] = parse_line(line, '=');

        sum += min_tokens(adx, ady, bdx, bdy, px, py);
    }
    cout << sum << endl;
    return 0;
}
/*
*/