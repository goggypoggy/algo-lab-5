#include <iostream>

struct Node {
    Node* less;
    Node* more;
    Node* parent;
    int data;
    int height = 1;
    int deltaH = 0;

    Node(int x, Node* prnt = nullptr, Node* left = nullptr, Node* right = nullptr)
    : data(x), less(left), more(right), parent(prnt)
    {}

    ~Node() {
        // delete less;
        // delete more;
    }

    void updateHeight() {
        if (less == nullptr && more == nullptr) {
            height = 1;
            deltaH = 0;
            return;
        }

        int left = 0;
        if (less != nullptr) {
            left = less->height;
        }
        
        int right = 0;
        if (more != nullptr) {
            right = more->height;
        }

        height = std::max(left, right) + 1;
        deltaH = left - right;
    }

    void isolate() {
        less = nullptr;
        more = nullptr;
    }

    void output_clean() {
        std::cout << data;
        if (less != nullptr) {
            std::cout << " ";
            less->output_clean();
        }
        if (more != nullptr) {
            std::cout << " ";
            more->output_clean();
        }
    }

    void output_debug() const {
        if (less != nullptr) {
            less->output_debug();
            std::cout << " ";
        }
        std::cout << "[" << data << " (" << height << ":" << deltaH << ") ^(" << (parent == nullptr ? 0 : parent->data) << ")]";
        if (more != nullptr) {
            std::cout << " ";
            more->output_debug();
        }
    }

    void backtrack() {
        updateHeight();
        if (parent != nullptr) {
            parent->backtrack();
        }
    }
};

struct Tree {
    Node* root = nullptr;

    void insert(int x) {
        root = insert_(x, root, nullptr);
    }

    bool search(int x) {
        Node* ptr = root;

        while (ptr != nullptr) {
            if (x == ptr->data) {
                return true;
            }
            if (x < ptr->data) {
                ptr = ptr->less;
            } else {
                ptr = ptr->more;
            }
        }

        return false;
    }

    void output() {
        root->output_clean();
        std::cout << "\n";
        root->output_debug();
        std::cout << "\n";
    }

private:
    void add_first(int x) {
        root = new Node(x);
    }

    Node* insert_(int x, Node* ptr, Node* predecessor) {
        if (ptr == nullptr) {
            return new Node(x, predecessor);
        }
        if (x < ptr->data) {
            ptr->less = insert_(x, ptr->less, ptr);
        } else {
            ptr->more = insert_(x, ptr->more, ptr);
        }
        ptr->updateHeight();
        return balance(ptr);
    }

    Node* small_left(Node* q) {
        Node* p = q->more;

        q->more = p->less;
        std::cout << "hi";
        q->more->parent = q;
        std::cout << "hi";

        p->parent = q->parent;
        p->less = q;
        q->parent = p;

        q->updateHeight();
        p->updateHeight();

        return p;
    }

    Node* balance(Node* ptr) {
        if (ptr->deltaH == -2) {
            if (ptr->more->deltaH <= 0) {
                // small left
                std::cout << "small left at " << ptr->data << "\n";
                return small_left(ptr);
            } else {
                // big left
                std::cout << "big left at " << ptr->data << "\n";
            }
        } else if (ptr->deltaH == 2) {
            if (ptr->less->deltaH >= 0) {
                // small right
                std::cout << "small right at " << ptr->data << "\n";
            } else {
                // big right
                std::cout << "big right at " << ptr->data << "\n";
            }
        }
        return ptr;
    }
};

int main(int, char**) {
    Tree tree;

    std::string command;
    while (std::cin >> command) {
        if (command == "insert") {
            int x;
            std::cin >> x;

            tree.insert(x);
        } else if (command == "exists") {
            int x;
            std::cin >> x;

            std::cout << (tree.search(x) ? "true" : "false") << "\n";
        } else if (command == "output") {
            tree.output();
        }
    }

    return 0;

    /*
insert 1
insert 3
insert 6
    */
}