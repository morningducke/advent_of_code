#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

enum class Outcomes {
    LOST = 0,
    DRAW = 3,
    WON = 6
};

int main() {


    string in;
    int rolling_sum = 0;
    
    
    while (getline(cin, in)) {       
        if (in == "-1") break;
        vector<pair<int,int>> ranges(2);

        istringstream is(in);
        string num;
        int l = 0;
        for (int i = 0; i < 2; ++i) {
            getline(is, num, '-');
            l = stoi(num);
            getline(is, num, ',');
            ranges[i] = {l, stoi(num)};
        }

        sort(ranges.begin(), ranges.end());    
        
        if (ranges[0].second >= ranges[1].first) {
            rolling_sum++;
        } 

    }

    cout << rolling_sum;
    
    return 0;
}