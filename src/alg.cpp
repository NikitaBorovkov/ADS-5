// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

using namespace std;

int prior(char zn) {
    if (zn == '(') {
        return 0;
    }
    if (zn == ')') {
        return 1;
    }
    if (zn == '+' || zn == '-') {
        return 2;
    }
    if (zn == '*' || zn == '/') {
        return 3;
    }
    return -1;
}
bool isDigit(string pref) {
    for (size_t i = 0; i < pref.size(); ++i) {
        if (pref[i] < '0' || pref[i] > '9') {
            return false;
        }
    }
    return true;
}

string infx2pstfx(string inf) {
    TStack <char, 100> stack1;
    string post;
    for (size_t i = 0; i < inf.size(); ++i) {
        int pr = prior(inf[i]);
        if (pr == -1) {
            if (!post.empty() && prior(inf[i - 1]) != -1) {
                post.push_back(' ');
            }
            post.push_back(inf[i]);
        } else if (pr == 0 || pr > prior(stack1.get()) || stack1.isEmpty()) {
            stack1.push(inf[i]);
        } else {
            if (pr == 1) {
                while (stack1.get() != '(') {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.pop();
            } else {
                while (prior(stack1.get()) >= pr) {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        post.push_back(' ');
        post.push_back(stack1.get());
        stack1.pop();
    }
  return post;
}

int eval(string post) {
    TStack <int, 100> stack2;
    string temp;
    int op1 = 0, op2 = 0;
    size_t start = 0, end = 0;
    for (size_t i = 0; i < post.size(); ++i) {
          if (post[i] == ' ' || i == post.size()-1) {
                end = i;
                if (i == post.size() - 1) end++;
                temp = post.substr(start, end - start);
                start = end + 1;
                if (isDigit(temp)) {
                    stack2.push(std::stoi(temp));
                } else {
                    op2 = stack2.get();
                    stack2.pop();
                    op1 = stack2.get();
                    stack2.pop();
                    if (temp == "+") stack2.push(op1 + op2);
                    else if (temp == "-") stack2.push(op1 - op2);
                    else if (temp == "*") stack2.push(op1 * op2);
                    else if (temp == "/") stack2.push(op1 / op2);
                }
            }
    }
    return stack2.get();
  return 0;
}
