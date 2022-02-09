#ifndef PQ_H
#define PQ_H

#include <iostream>
#include <vector>

#include "math.h"
template <class T, class F>
struct PQ {
    std::vector<T> elements;
    F func;  // };

    int size;
    bool sorted;
    PQ(F func)
        : elements(std::vector<T>()), func(func), size(0), sorted(false){};
    // PQ(std::function<bool(const T, const T)> f)
    //     : elements(std::vector<T>()), less(f), size(0), sorted(false){};

    int right_child(int i) { return 2 * i + 2; }
    int left_child(int i) { return 2 * i + 1; }
    int parent(int i) { return floor((i - 1) / 2); }

    void push(T label) {
        elements.push_back(label);
        sorted = false;
        size++;
    };

    void build() {
        if (sorted) return;
        for (int i = (size / 2) - 1; i >= 0; i--) {
            down_heap(i);
        }
        sorted = true;
    };

    bool empty() { return size == 0; };

    void down_heap(int i) {
        int left = left_child(i);
        int right = right_child(i);
        int smallest = i;

        if (left < size && func(elements[left], elements[smallest]))
            smallest = left;
        if (right < size && func(elements[right], elements[smallest]))
            smallest = right;

        if (smallest != i) {
            swap(i, smallest);
            down_heap(smallest);
        }
    };

    T peek() {
        if (size == 0) throw "";
        build();

        return elements[0];
    };

    void swap(int a, int b) {
        T c(elements[a]);
        elements[a] = elements[b];
        elements[b] = c;
    };

    T pop() {
        build();

        T m = peek();
        swap(0, --size);
        down_heap(0);

        return m;
    };

    void print() {
        build();
        for (int i = 0; i < size; i++) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    };
};

#endif
