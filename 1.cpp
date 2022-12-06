#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    string in;

    priority_queue<int, vector<int>, greater<int>> pq;
    int rolling_sum = 0;

    while (getline(cin, in)) {       
        if (in.empty()) {
            if (pq.size() < 3) {
                pq.push(rolling_sum);
            } 
            else if (pq.top() < rolling_sum) {
                pq.pop();
                pq.push(rolling_sum);
            } 
            rolling_sum = 0;
        } else {
            int num = stoi(in);
            if (num == -1) break;
            rolling_sum += num;
        }    
        
    }
    if (pq.size() < 3) {
        pq.push(rolling_sum);
    } else if (pq.top() < rolling_sum) {
        pq.pop();
        pq.push(rolling_sum);
    }
    rolling_sum = 0;
    for (int i = 0; i < 3; ++i) {
        rolling_sum += pq.top();
        pq.pop();
    }

    cout << rolling_sum;
    return 0;
}