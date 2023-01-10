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

using namespace std;

class Monkey {
public:
    Monkey(queue<int64_t> items, char op_type, string op_operand, int divisor, int mk_true, int mk_false) {
        this->items_ = items;
        this->op_type_ = op_type;
        this->op_operand_ = op_operand;
        this->divisor_ = divisor;
        this->mk_true_ = mk_true;
        this->mk_false_ = mk_false;
    }

    Monkey() {}
    
    int64_t PerformOperation(int64_t old_worry) const {
        int64_t operand_value = op_operand_ == "old" ? old_worry : stoi(op_operand_);
        
        switch (op_type_) {
          case '+':
            return old_worry + operand_value;
            break;
          case '*':
            return old_worry * operand_value;
            break;

          default:
            break;
        }

        return -1;
    }

    int PerformTest(int64_t worry) const {
        return worry % divisor_ == 0 ? mk_true_ : mk_false_;
    }

    void items_pop() {
        items_.pop();
    }

    int items_top() const {
        return items_.front();
    }
    
    void items_push(int worry) {
        items_.push(worry);
    }

    queue<int64_t> get_items() const {
        return items_;
    }

    int get_items_size() const {
        return items_.size();
    }
    char get_op_type() const {
        return op_type_;
    }

    string get_op_operand() const {
        return op_operand_;
    }

    int get_divisor() const { 
        return divisor_;
    }

    int get_mk_true() const {
        return mk_true_;
    }

    int get_mk_false() const {
        return mk_false_;
    }

private:
    queue<int64_t> items_;
    char op_type_;
    string op_operand_;
    int divisor_;
    int mk_true_;
    int mk_false_;
};

void SkipWords(istringstream& is, int count, char separator) {
    string in;
    while (count-- && getline(is, in, separator)) {}
}

Monkey ParseMonkey(ifstream& input) {
    string in;
    istringstream is;
    queue<int64_t> items;
    char op_type = 0;
    string op_operand;
    int divisor = 0;
    int mk_true = 0;
    int mk_false = 0;
    constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

    getline(input, in); // monkey num - skip

    getline(input, in); // starting items
    is = istringstream(in);
    is.ignore(max_size, ':');
    while (getline(is, in, ',')) {
        items.push(stoi(in));
    }
    

    getline(input, in); // operation
    is = istringstream(in);
    is.ignore(max_size, '=');
    SkipWords(is, 2, ' '); // skip until opeartion and operand 
    is >> op_type;
    is >> op_operand;
    
    getline(input, in); // test

    is = istringstream(in);
    SkipWords(is, 5, ' '); // skip until divisor
    is >> divisor;

    getline(input, in); // true
    is = istringstream(in);
    SkipWords(is, 9, ' '); // skip until monkey's number
    is >> mk_true;

    getline(input, in); // false
    is = istringstream(in);
    SkipWords(is, 9, ' '); // skip until monkey's number
    is >> mk_false;
    
    getline(input, in); // read end of line
    return Monkey(items, op_type, op_operand, divisor, mk_true, mk_false);     
};

void PrintMonkey(Monkey monkey, ostream& os) {
    queue<int64_t> items = monkey.get_items();
    os << "  Starting items: ";
    
    while (!items.empty()) {
        os << items.front();
        if (items.size() != 1) os << ", ";

        items.pop();
    }
    os << '\n';
    os << "  Operation: new = old " << monkey.get_op_type() << " " << monkey.get_op_operand() << '\n';

    os << "  Test: divisible by " << monkey.get_divisor() << '\n';
    os << "    If true: throw to monkey " << monkey.get_mk_true() << '\n'; 
    os << "    If false: throw to monkey " << monkey.get_mk_false() << "\n\n"; 
}
int main()  {

    
    vector<Monkey> monkeys;
    ifstream input("input.txt");
    
    while (input.peek() != false && !input.eof())
    {
        monkeys.push_back(ParseMonkey(input));

    }
    input.close();
   

    int num_of_turns = 10000; 
    vector<long long int> inspect_count(monkeys.size(), 0);

    int64_t mod_n = 1;
    for (const auto& monkey : monkeys) {
        mod_n *= monkey.get_divisor();
    }

    while (num_of_turns--) {
        for (size_t i = 0; i < monkeys.size(); ++i) {
            
            inspect_count[i] += monkeys[i].get_items_size();
            while (monkeys[i].get_items_size() != 0) {
                int64_t new_worry = monkeys[i].PerformOperation(monkeys[i].items_top()) % mod_n; // calc new worry 
                monkeys[i].items_pop();
                int64_t monkey_rec = monkeys[i].PerformTest(new_worry); // decide which monkey receives the item
                monkeys[monkey_rec].items_push(new_worry);
            }
            
        }
    }
    
    sort(inspect_count.begin(), inspect_count.end(), greater<int>());
    cout << "Part 2: " << inspect_count[0] * inspect_count[1] << "\n";

    // int m_count = 0;
    // for (const auto& monkey : monkeys) {
    //     cout << "Monkey " << m_count++ << ":\n";
    //     PrintMonkey(monkey, cout);
    // }


    return 0;
}