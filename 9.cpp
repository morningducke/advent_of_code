#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

struct Point {
    int x, y;
};

map<char, vector<int>> dirs = {{'U', {0, -1}}, {'D', {0, 1}}, {'R', {1, 0}}, {'L', {-1, 0}}};
// sum of squared distances by axis
// if distance == 4 -> move tail in one direction
// if distance == 5 -> move tail diagonally
// if < 4 -> dont need to move the tail
int distance(Point p1, Point p2) {
    return abs(p1.x - p2.x)*abs(p1.x - p2.x) + abs(p1.y - p2.y)*abs(p1.y - p2.y);
}

void update_count(Point& tail, vector<vector<char>>& matr, int& visited_count) {
    if (matr[tail.y][tail.x] == '.') {
        visited_count++;
    }
    matr[tail.y][tail.x] = '#';
    
}

void update_tail(Point& head, Point& tail, vector<vector<char>>& matr) {
    int dist = distance(head, tail);
    int x_dist = head.x - tail.x;
    int y_dist = head.y - tail.y;
    if (dist == 4) {
        if (x_dist != 0) {
            tail.x += x_dist > 0 ? 1 : -1;
        } else {
            tail.y += y_dist > 0 ? 1 : -1;
        }
        
        
    } else if (dist == 5) {
        if (abs(x_dist) == 2) {
            tail.x += x_dist > 0 ? 1 : -1;
            tail.y = head.y;
        } else {
            tail.x = head.x;
            tail.y += y_dist > 0 ? 1 : -1;
        }
    } else if (dist == 8) {
        tail.x += x_dist > 0 ? 1 : -1;
        tail.y += y_dist > 0 ? 1 : -1;
    }

    if (tail.y < 0 || tail.y >= matr.size() || tail.x < 0 || tail.x >= matr[0].size())
        throw out_of_range("Tail out of bounds x:" + to_string(tail.x) + " y:" + to_string(tail.y) + "\n Head at x: " + to_string(head.x) + " y:" + to_string(head.y));

}
void move_head(Point& head, vector<Point>& tails, vector<vector<char>>& matr, char direction, int amount, int& visited_count) {
    while (amount--)
    {
        head.x += dirs[direction][0];
        head.y += dirs[direction][1];
        if (head.y < 0 || head.y >= matr.size() || head.x < 0 || head.x >= matr[0].size()) throw out_of_range("Head out of bounds");

        Point cur_head = head;
        for (int i = 0; i < tails.size(); ++i) {
            try {
                update_tail(cur_head, tails[i], matr);
            } catch (exception& e) {
                cout << e.what() << " at tail #" << i + 1 << "\n";
                return;
            }
            
            cur_head = tails[i];
        }

        update_count(tails.back(), matr, visited_count);
        
    }
}

void print_matrix(vector<vector<char>>& matr) {
    ofstream file("matrix.txt");
    for (const auto& v : matr) {
        for (const auto& c : v) {
            file << c;
        }
        file << "\n";
    }
}
int main()  {

    int width = 1000;
    int height = 1000;
    vector<vector<char>> matr(height, vector<char>(width, '.'));
    
    matr[height / 2 - 1][width / 2 - 1] = '#';
    string in;
    Point head = {width / 2 - 1, height / 2 - 1};
    vector<Point> tails(9, {width / 2 - 1, height / 2 - 1});
    int visited_count = 1;
    ifstream input("input.txt");
    while (getline(input, in))
    {
        istringstream is(in);
        char direction = 0;
        int amount = 0;
        is >> direction;
        is >> amount;
        move_head(head, tails, matr, direction, amount, visited_count);
    }
    input.close();

    
    // for (int i = tails.size() - 1; i >= 0; --i) {
    //     Point p = tails[i];
    //     matr[p.y][p.x] = i + '1';
    // }
    // matr[head.y][head.x] = 'H';
    // print_matrix(matr);
    cout << "Part 2: " << visited_count << "\n";
    return 0;
}