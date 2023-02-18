#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <string>
#include "BinaryTree.h"

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

BTree<string>* MakeExpTree(vector<string> exp) {
    stack<BTree<string>*> s;

    for (string op : exp) {
        if (IsDouble(op)) {
            BTree<string>* btNum = new BTree<string>(op);
            s.push(btNum);
        }
        else {
            BTree<string>* btRight = s.top(); s.pop();
            BTree<string>* btLeft = s.top(); s.pop();

            BTree<string>* btParent = new BTree<string>(op);

            btParent->MakeLeftSubTree(btLeft);
            btParent->MakeRightSubTree(btRight);

            s.push(btParent);
        }
    }

    return s.top();
}

double CalculateExpTree(BTree<string>* bt) {
    double op1, op2;

    if (bt->GetLeftTree() == NULL && bt->GetRightTree() == NULL) { return stod(bt->GetData()); }

    op1 = CalculateExpTree(bt->GetLeftTree());
    op2 = CalculateExpTree(bt->GetRightTree());

    if (bt->GetData() == "+") return op1 + op2;
    else if (bt->GetData() == "-") return op1 - op2;
    else if (bt->GetData() == "*") return op1 * op2;
    else if (bt->GetData() == "/") return op1 / op2;
}

int main() {
    BTree<string>* root;
    string exp; cin >> exp;
    vector<string> postfix = ConvToPostFix(Split(exp));
    root = MakeExpTree(postfix);

    cout << CalculateExpTree(root);

    return 0;
}
