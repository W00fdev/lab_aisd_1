#include "List.h"

using std::logic_error;
using std::out_of_range;
using std::runtime_error;

using std::cout;

bool List::base_pop() {
    if (size == 0u)
        throw logic_error("Pop already empty list");
    if (size == 1u) {
        delete begin;
        begin = nullptr;
        end = nullptr;
        return true;
    }
    return false;
}

void List::push_back(int data) {
    if (size == 0u) {
        begin = new Node(data);
        end = begin;
    } else {
        end->next = new Node(data);
        end = end->next;
    }

    size++;
}

void List::push_front(int data) {
    if (size == 0u) {
        begin = new Node(data);
        end = begin;
    } else {
        Node *begin_saved = begin;
        begin = new Node(data, begin_saved);
    }

    size++;
}

void List::pop_back() {
    if (!base_pop()){
        Node *current = begin;
        while (current->next != end) {
            current = current->next;
        }
        delete end;
        end = current;                 // set new end
        end->next = nullptr;
    }

    size--;
}

void List::pop_front() {
    if (!base_pop()) {
        Node *new_begin = begin->next;
        delete begin;
        begin = new_begin;
    }
    size--;
}

void List::insert(int data, size_t index) {
    if (index > size)
        throw out_of_range("Index is greater than a List size {insert_error}");
    else if (index == 0u || size == 0u) {
        push_front(data);
    } else if (index == size) {
        push_back(data);
    } else {
        size_t counter = 0u;
        Node *current = begin;
        while (counter != index - 1) {
            current = current->next;
            counter++;
        }

        Node *old_next = current->next;
        current->next = new Node(data);
        current->next->next = old_next;

        size++;
    }
}

int List::at(size_t index) const {
    if (index == 0u) return begin->value;
    if (index >= size)
        throw out_of_range("Index is greater than a List size {at_error}");

    Node *current = begin;
    size_t counter = 0u;
    while (counter != index) {
        current = current->next;
        counter++;
    }

    return current->value;
}

void List::remove(size_t index) {
    if (index == 0u) {
        pop_front();
    }
    else if (index >= size)
        throw out_of_range("Index is greater than a List size {remove_error}");
    else if (index == size - 1) {
        pop_back();
    } else {
        Node *current = begin;
        size_t counter = 0u;
        while (counter != index - 1) {
            current = current->next;
            counter++;
        }

        // Deleting node algorithm
        Node *old_next = current->next->next;
        delete current->next;
        current->next = old_next;

        size--;
    }
}

size_t List::get_size() const {
    return size;
}

void List::print_to_console(std::string separator) const {
    if (size == 0u) {
        cout << "List is empty.\n";
    } else {
        Node *current = begin;
        while (current != nullptr) {
            cout << current->value << separator;
            current = current->next;
        }
        cout << "nullptr\n";
    }
}

void List::clear() {
    while (size != 0u) {
        pop_front();
    }
}

void List::set(size_t index, int data) {
    if (size == 0u)
        throw logic_error("There are no elements to swap in the list.");

    if (index == 0u)
        begin->value = data;
    else if (index >= size)
        throw out_of_range("Index is greater than a List size {set_error}");
    else if (index == size - 1)
        end->value = data;
    else {
        Node *current = begin;
        size_t counter = 0u;
        while (counter != index) {
            current = current->next;
            counter++;
        }
        if (current == nullptr) throw out_of_range("Cannot find the right element in set()");
        current->value = data;
    }
}

bool List::isEmpty() const {
    return size == 0u;
}

size_t List::find_last(List *l_other) const {
    if (size < l_other->get_size()) throw out_of_range("Size of the sub-List is greater than size of the original List");

    Node *other_cur = l_other->begin;
    Node *my_cur    = begin;
    size_t index = 0u, result = size + 1;   // Defined value of unknown result
    size_t counter_start_with = 0u;
    bool in_loop = false, found = false;

    while (my_cur != nullptr) {
        if (other_cur->value == my_cur->value) {
            if (!in_loop) {                     // sets that we are now in the loop
                counter_start_with = index;     // and we need to fall back after the loop
                in_loop = true;
            }

            if (other_cur == l_other->end) {
                result = counter_start_with; // If we have l_other = 1 element.
                found = true;                // or we need to reset our position.
            }
        }

        if (found || (other_cur->value != my_cur->value && (in_loop || other_cur == nullptr))) {
            // If it was in the loop before, it needs to fall back to the entry point == counter_start_with
            size_t counter = 0u;
            Node *runner = begin;
            while (counter < counter_start_with) {
                runner = runner->next;
                counter++;
            }                               // move our L1 pointer to the entry point
            index = counter_start_with;
            my_cur = runner;                // set our L1 pointer

            in_loop = false;                // now it's not in the loop
            other_cur = l_other->begin;      // Search new subsequence from L2's begin
            found = false;
        } else if (!found && in_loop) {
            other_cur = other_cur->next;    // just move the L2 pointer
        }

        my_cur = my_cur->next;          // always getting next
        index++;
    }

    if (result == size + 1) throw logic_error("Can't find the subsequence");

    return result;
}


bool operator== (const List &l, const List &r) {
    if (l.get_size() != r.get_size()) return false;

    List::Node *l_cur = l.begin;
    List::Node *r_cur = r.begin;
    while (l_cur != nullptr) {
        if (l_cur->value != r_cur->value) return false;
        l_cur = l_cur->next;
        r_cur = r_cur->next;
    }
    return true;
}