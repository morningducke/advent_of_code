#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;



struct Point {
    int i,j;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.i == rhs.i && lhs.j == rhs.j;
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.i << "," << p.j << ")";
    return os;
}

template <typename T>
void PrintMatrix(const vector<vector<T>>& matr) {
    for (const auto& i : matr) {
        for (const auto& j : i) {
            cout << j;
            if (j != i.back()) cout << " ";
        }
        cout << "\n";
    }
}


int BFS(vector<vector<char>> matr) {
    queue<Point> q;
    vector<vector<bool>> marked(matr.size(), vector<bool>(matr[0].size(), false));
    vector<vector<Point>> paths(matr.size(), vector<Point>(matr[0].size(), {-1, -1})); 
    vector<Point> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int len = 0;
    Point start_vert = {-1, -1};
    Point target_vert = {-1, -1};
    // find starting vertice
    for (int i = 0; i < matr.size() && (start_vert.i == -1 || target_vert.i == -1); ++i) {
        for (int j = 0; j < matr[0].size(); ++j) {
            if (matr[i][j] == 'S') {
                start_vert = {i, j};
                matr[i][j] = 'a';
            } else if (matr[i][j] == 'E') {
                target_vert = {i, j};
                matr[i][j] = 'z';
            }
            
        }
    }
    // cout << "Start: " << start_vert.i << " " << start_vert.j << "\n";
    // cout << "End: " << target_vert.i << " " << target_vert.j << "\n";

    // run bfs to find the shortest path
    q.push(start_vert);
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        if (marked[p.i][p.j]) continue;
        marked[p.i][p.j] = true; // mark as visited
        
        if (p == target_vert) break;

        
        for (const auto& d : directions) {
            Point p_next = p;
            p_next.i += d.i;
            p_next.j += d.j;
            if (p_next.i >=0 && p_next.i < matr.size() && p_next.j >= 0 && p_next.j < matr[0].size() && !marked[p_next.i][p_next.j]
                && matr[p_next.i][p_next.j] - matr[p.i][p.j] <= 1) {
                q.push(p_next);
                paths[p_next.i][p_next.j] = p;
            }    
        }
    }

   // PrintMatrix(paths);
   if (paths[target_vert.i][target_vert.j] == paths[start_vert.i][start_vert.j]) return INT_MAX;

    while(paths[target_vert.i][target_vert.j] != paths[start_vert.i][start_vert.j]) {
        len++;
        target_vert = paths[target_vert.i][target_vert.j];    
    }
    return len;
};


int main()  {

    
  
    ifstream input("input.txt");
    string in;
    vector<vector<char>> matr;
    while (getline(input, in))
    {
        vector<char> row;
        for (const auto& c : in) {
            row.push_back(c);
        }
        matr.push_back(row);
    }
    input.close();
   
    //PrintMatrix(matr);

    int len = BFS(matr);
    cout << "Part 1: " << len << "\n";

    for (auto& row : matr) {
        for (auto& c : row) {
            if (c == 'S') c = 'a';
        }
    }

    for (auto& row : matr) {
        for (auto& c : row) {
            if (c == 'a') {
                c = 'S';
                len = min(len, BFS(matr));
                c = 'a';
            }
        }
    }

    cout << "Part 2: " << len << "\n";
    return 0;
}