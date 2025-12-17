#include <iostream>

struct Node {
    Node* next;
    int data;

    Node(int x, Node* nxt = nullptr)
    : data(x), next(nxt) {}

    ~Node() {
        delete next;
    }
};

struct Queue {
    Node* tail = nullptr;
    Node* head = nullptr;

    void push_back(int x) {
        if (head == nullptr) {
            add_first(x);
            return;
        }

        head->next = new Node(x);
        head = head->next;
    }

    int pop_front() {
        if (tail == head) {
            return pop_first();
        }

        int value = tail->data;
        
        Node* old_node = tail;
        tail = tail->next;
        old_node->next = nullptr;
        delete old_node;

        return value;
    }

    ~Queue() {
        delete tail;
    }

    void output() {
        for (Node* nd = tail; nd != nullptr; nd = nd->next) {
            std::cout << nd->data << "\n";
        }
    }

private:
    void add_first(int x) {
        Node* new_node = new Node(x);

        tail = new_node;
        head = new_node;
    }

    int pop_first() {
        // if (tail == nullptr) {
        //     throw;
        // }
        int value = tail->data;

        delete tail;
        tail = nullptr;
        head = nullptr;

        return value;
    }
};

int main(int, char**) {
    Queue queue;
    Queue results;

    int n;
    std::cin >> n;

    char operation;
    int value;
    while (n != 0) {
        std::cin >> operation;

        if (operation == '+') {
            std::cin >> value;

            queue.push_back(value);
        } else {
            results.push_back(queue.pop_front());
        }
        n--;
    }

    results.output();

    return 0;
}