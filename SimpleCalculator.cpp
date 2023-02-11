#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

bool IsNumber(const string& str) {
    for (const char x : str) {
        if (isdigit(x) == 0) return false;
    }
    
    return true;
}

bool IsDouble(const string& str) {
    for (const char x : str) {
        if (isdigit(x) == 0 && x != '.') return false;
    }
    return true;
}

vector<string> Split(string str) {
    vector<string> result;
    int curIndex = 0;

    for (int i = 0; i < str.length(); i++) {
        
        if (!isdigit(str[i]) && str[i] != '.') {
            if (str.substr(curIndex, i - curIndex) != "") result.push_back(str.substr(curIndex, i - curIndex));
            result.push_back(str.substr(i, 1));
            curIndex = i + 1;
        }
        else if (i == str.length() - 1) {
            result.push_back(str.substr(curIndex));
        }
    }
    return result;
}

int GetOpPrec(const string& op) {
    if (op == "*" || op == "/") return 3;
    else if (op == "+" || op == "-") return 2;
    else if (op == "(") return 1;
    else return 0;
}

int CompPrec(const string& op1, const string& op2) {
    int op1Prec = GetOpPrec(op1.c_str());
    int op2Prec = GetOpPrec(op2.c_str());

    if (op1Prec > op2Prec) return 1;
    else if (op1Prec == op2Prec) return 0;
    else return -1;
}

vector<string> ConvToPostFix(vector<string> exp) {
    vector<string> result;
    stack<string> opStack;

    for (string op : exp) {
        if (IsDouble(op)) {
            result.push_back(op);
        }
        else {
            if (opStack.empty()) {
                opStack.push(op);
            }
            else {
                if (op == ")") {
                    while (opStack.top() != "(") {
                        result.push_back(opStack.top());
                        opStack.pop();
                    }
                    opStack.pop();
                }
                else {
                    if (CompPrec(opStack.top(), op) < 0) {
                        opStack.push(op);
                    }
                    else {
                        while (!opStack.empty() && CompPrec(opStack.top(), op) >= 0) {
                            result.push_back(opStack.top());
                            opStack.pop();
                        }
                        opStack.push(op);
                    }
                }
            }
        }
    }

    while (!opStack.empty()) {
        result.push_back(opStack.top());
        opStack.pop();
    }

    return result;
}

double Calculator(vector<string> exp) {
    stack<double> nums;

    for (string op : exp) {
        if (IsDouble(op)) {
            double tmp;
            stringstream ssDouble(op);
            ssDouble >> tmp;
            nums.push(tmp);
        }
        else {
            double op2 = nums.top(); nums.pop();
            double op1 = nums.top(); nums.pop();

            if (op == "+") nums.push(op1 + op2);
            else if (op == "-") nums.push(op1 - op2);
            else if (op == "*") nums.push(op1 * op2);
            else if (op == "/") nums.push(op1 / op2);
        }
    }

    return nums.top();
}

int main() {
    string str1; cin >> str1;
    vector<string> exp = Split(str1);
    
    exp = ConvToPostFix(exp);

    cout << Calculator(exp);

    return 0;
}
