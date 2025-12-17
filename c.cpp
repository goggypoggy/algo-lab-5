#include <iostream>

struct Node {
    Node* prev;
    Node* next;
    int data;

    Node(int x, Node* prv = nullptr, Node* nxt = nullptr)
    : data(x), prev(prv), next(nxt) {}

    void isolate() {
        prev = nullptr;
        next = nullptr;
    }

    ~Node() {
        delete next;
    }
};

struct Dequeue {
    Node* tail = nullptr;
    Node* head = nullptr;

    void push_back(int x) {
        if (head == nullptr) {
            add_first(x);
            return;
        }

        Node* new_node = new Node(x, head, nullptr);

        head->next = new_node;
        head = new_node;
    }

    void push_front(int x) {
        if (tail == nullptr) {
            add_first(x);
            return;
        }

        Node* new_node = new Node(x, nullptr, tail);

        tail->prev = new_node;
        tail = new_node;
    }

    int pop_front() {
        if (tail == head) {
            return pop_first();
        }

        int value = tail->data;
        
        Node* old_node = tail;
        tail = tail->next;
        tail->prev = nullptr;

        old_node->isolate();
        delete old_node;

        return value;
    }

    int pop_back() {
        if (tail == head) {
            return pop_first();
        }

        int value = head->data;
        
        Node* old_node = head;
        head = head->prev;
        head->next = nullptr;

        old_node->isolate();
        delete old_node;

        return value;
    }

    ~Dequeue() {
        delete tail;
    }

    void output() {
        for (Node* nd = tail; nd != nullptr; nd = nd->next) {
            std::cout << nd->data << (nd->next == nullptr ? "\n" : " ");
        }
    }

    void output_backwards() {
        for (Node* nd = head; nd != nullptr; nd = nd->prev) {
            std::cout << nd->data << (nd->prev == nullptr ? "\n" : " ");
        }
    }

    int front() {
        return tail->data;
    }

    int back() {
        return head->data;
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

int mod(int x, int m) {
    while (x < 0) {
        x += m;
    }

    return x % m;
}

int main(int, char**) {
    Dequeue dequeue;

    int n;
    int k;

    std::cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        dequeue.push_back(x);
    }

    for (int i = 0; i < k; ++i) {
        int x = dequeue.front();
        int y = dequeue.back();

        if (x < y) {
            dequeue.pop_front();
            dequeue.push_back(mod(x + y, 1 << 30));
        } else {
            dequeue.pop_back();
            dequeue.push_front(mod(y - x, 1 << 30));
        }
    }

    dequeue.output();

    return 0;
}