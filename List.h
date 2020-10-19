#pragma once
#include <vector>
#include <iostream>

using std::vector;

class List{
    class Node {
    public:
        int value;
        Node *next;

        Node(int data, Node *_next = nullptr) {
            //value(data), next(_next) {}
            value = data;
            next = _next;
        }
        ~Node() {}
    };

public:

    List() {
        size  = 0u;
        begin = nullptr;
        end  = nullptr;
    }

    List(const vector<int> &arr) {
        size = 0u;
        begin = nullptr;
        end  = nullptr;

        for(const auto& val : arr)
            push_back(val);
    }

    ~List() {
        clear();    // Очищаем память
    }

    friend bool operator== (const List &l, const List &r);

    // Push value to the end of List
    void push_back(int);

    // Push value to the begin of the List
    void push_front(int);

    // Pop the last element of the List
    void pop_back();

    // Pop the first element of the List
    void pop_front();

    // Insert the element by before the index of List
    void insert(int, size_t);

    // Get copy of value by index
    int at(size_t) const;

    // Remove element on position of index
    void remove(size_t);

    // Get the List's size
    size_t get_size() const;

    // Simplified output to the console, using separator
    void print_to_console(std::string separator = " -> ") const;

    // Clear the List
    void clear();

    // Swap the value of the element by the index
    void set(size_t, int);

    // Simple check
    bool isEmpty() const;

    // Search of the last entry List1 in the our List
    size_t find_last(List*) const;

private:
    Node *begin;
    Node *end;
    size_t size;

    bool base_pop();
};
