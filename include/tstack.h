// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
     T arr[100];
     int t;
 public:
     TStack() : t(-1) {}
     bool isEmpty() const {
         return t == -1;
     }
     bool isFull() const {
         return t == size - 1;
     }
     T get() {
         return arr[top];
     }
     void pop() {
         if (t >= 0)
             t--;
     }
     void push(T value) {
         if (t < size - 1)
             arr[++] = value;
     }
};
#endif  // INCLUDE_TSTACK_H_
