#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

enum class Outcomes {
    LOST = 0,
    DRAW = 3,
    WON = 6
};

int main() {
    map<char, int> shape_scores;
    // map<char, char> shapes = {{'X','A'}, {'Y', 'B'}, {'Z', 'C'}};
    shape_scores['A'] = 1; shape_scores['B'] = 2; shape_scores['C'] = 3;


    string in;
    int rolling_sum = 0;

    while (getline(cin, in)) {       
        if (in == "-1") break;

        istringstream is(in);
        char shape1, shape2, res;
        is >> shape2;
        is >> res;

        switch (res) {
            case 'X':
                if (shape2 == 'A') rolling_sum += shape_scores['C'];
                else if (shape2 == 'B') rolling_sum += shape_scores['A'];
                else rolling_sum += shape_scores['B'];
                break;
            case 'Y':
                rolling_sum += shape_scores[shape2] + static_cast<int>(Outcomes::DRAW);
                break;
            case 'Z':
                if (shape2 == 'A') rolling_sum += shape_scores['B'];
                else if (shape2 == 'B') rolling_sum += shape_scores['C'];
                else rolling_sum += shape_scores['A'];
                rolling_sum += 6;
                break;
            default:
                break;
        }
        // shape1 = shapes[shape1];

        // if (shape1 == shape2) {
        //     rolling_sum += static_cast<int>(Outcomes::DRAW); 
        // } else {
        //     // if ((shape1 == 'A' && shape2 == 'B') || (shape1 == 'B' && shape2 == 'C') || (shape1 == 'C' && shape2 == 'A')) break;
        //     if ((shape1 == 'A' && shape2 == 'C') || (shape1 == 'B' && shape2 == 'A') || (shape1 == 'C' &&  shape2 == 'B')) {
        //         rolling_sum += static_cast<int>(Outcomes::WON);
        //     }
        // }
        // rolling_sum += + shape_scores[shape1];    
    }
    cout << rolling_sum;
    return 0;
}