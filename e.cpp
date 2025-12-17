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

    tree.add(3);
    tree.add(2);
    tree.add(6);
    tree.add(4);
    tree.add(4);

    tree.output();

    std::cout << "\n";
    std::cout << tree.root->parent << "\n";
    std::cout << tree.root << " == " << tree.root->more->parent << "\n";
    std::cout << tree.root->more << " == " << tree.root->more->less->parent << "\n";

    std::cout << "result of find(): " << tree.find(2) << "\n";

    return 0;
}