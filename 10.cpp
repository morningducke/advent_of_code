#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

#define WIDTH 40
#define HEIGHT 6

using namespace std;

int cycle(int& cycle_count, int x, unordered_set<int>& special_cycles) {
    int p_x = cycle_count % WIDTH;
    if (abs(p_x - x) <= 1) {
        cout << "#";
    } else {
        cout << ".";
    }

    if (p_x == WIDTH - 1) {
        cout << "\n";
    }
    cycle_count++;
    return special_cycles.count(cycle_count) > 0 ? cycle_count * x : 0;
}
int main()  {

    
    vector<vector<int>> g;
    string in;
    int x = 1, signal_sum = 0, cycle_count = 0;
    ifstream input("input.txt");
    unordered_set<int> special_cycles = {20, 60, 100, 140, 180, 220};
    while (getline(input, in))
    {
        istringstream is(in);
        is >> in;
        if (in == "noop") {
            signal_sum += cycle(cycle_count, x, special_cycles);
        } else {
            is >> in;
            signal_sum += cycle(cycle_count, x, special_cycles);
            signal_sum += cycle(cycle_count, x, special_cycles);
            x += stoi(in);
        }

    }
    input.close();



    cout << "Part 1: " << signal_sum << "\n";

    return 0;
}