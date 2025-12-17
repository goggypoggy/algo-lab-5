#include <iostream>

struct Node {
    Node* less;
    Node* more;
    Node* parent;
    int data;
    int size = 1;

    Node(int x, Node* prnt = nullptr, Node* left = nullptr, Node* right = nullptr)
    : data(x), less(left), more(right), parent(prnt)
    {}

    ~Node() {
        delete less;
        delete more;
    }

    void output() {
        if (less != nullptr) {
            less->output();
        }
        std::cout << "[" << data << ", (" << size << ")" << "]";
        if (more != nullptr) {
            more->output();
        }
    }

    void backtrack() {
        size--;
        if (parent != nullptr) {
            parent->backtrack();
        }
    }
};

struct Tree {
    Node* root = nullptr;

    void add(int x) {
        if (root == nullptr) {
            add_first(x);
            return;
        }

        Node** ptr = &root;
        Node* parent = nullptr;

        while (*ptr != nullptr) {
            (*ptr)->size++;
            if ((*ptr)->data == x) {
                (*ptr)->backtrack();
                return;
            }

            if (x < (*ptr)->data) {
                parent = *ptr;
                ptr = &((*ptr)->less);
            } else {
                parent = *ptr;
                ptr = &((*ptr)->more);
            }
        }

        *ptr = new Node(x, parent);
    }

    // requires 0-indexed pos!!!
    int find(int pos) {
        Node* ptr = root;

        int cur_pos = 0;
        if (ptr->less != nullptr) {
            cur_pos += ptr->less->size;
        }

        while (cur_pos != pos) {
            if (pos < cur_pos) {
                cur_pos--;
                ptr = ptr->less;
                if (ptr->more != nullptr) {
                    cur_pos -= ptr->more->size;
                }
            } else {
                cur_pos++;
                ptr = ptr->more;
                if (ptr->less != nullptr) {
                    cur_pos += ptr->less->size;
                }
            }
        }

        return ptr->data;
    }

    void output() {
        root->output();
    }

private:
    void add_first(int x) {
        root = new Node(x);
    }
};

int main(int, char**) {
    Tree tree;

    char c;
    while (std::cin >> c) {
        if (c == '+') {
            int x;
            std::cin >> x;

            tree.add(x);
        } else {
            int k;
            std::cin >> k;

            std::cout << tree.find(k - 1) << "\n";
        }
    }

    return 0;
}