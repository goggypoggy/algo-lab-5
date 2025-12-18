#include <iostream>

struct Node {
    Node* less;
    Node* more;
    int data;
    int height = 1;
    int deltaH = 0;

    Node(int x, Node* left = nullptr, Node* right = nullptr)
    : data(x), less(left), more(right)
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
        std::cout << "[" << data << " (" << height << ":" << deltaH << ")]";
        if (more != nullptr) {
            std::cout << " ";
            more->output_debug();
        }
    }
};

struct Tree {
    Node* root = nullptr;

    void insert(int x) {
        root = insert_(x, root);
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

    Node* insert_(int x, Node* ptr) {
        if (ptr == nullptr) {
            return new Node(x);
        }
        if (x < ptr->data) {
            ptr->less = insert_(x, ptr->less);
        } else {
            ptr->more = insert_(x, ptr->more);
        }
        ptr->updateHeight();
        return balance(ptr);
    }

    Node* small_left(Node* q) {
        Node* p = q->more;

        q->more = p->less;

        p->less = q;

        q->updateHeight();
        p->updateHeight();

        return p;
    }

    Node* small_right(Node* q) {
        Node* p = q->less;

        q->less = p->more;

        p->more = q;

        q->updateHeight();
        p->updateHeight();

        return p;
    }

    Node* big_left(Node* r) {
        Node* q = r->more;
        Node* p = q->less;

        r->more = p->less;
        q->less = p->more;

        p->less = r;
        p->more = q;

        r->updateHeight();
        q->updateHeight();
        p->updateHeight();

        return p;
    }

    Node* big_right(Node* r) {
        Node* q = r->less;
        Node* p = q->more;

        q->more = p->less;
        r->less = p->more;

        p->less = q;
        p->more = r;

        q->updateHeight();
        r->updateHeight();
        p->updateHeight();

        return p;
    }

    Node* balance(Node* ptr) {
        if (ptr->deltaH == -2) {
            if (ptr->more->deltaH <= 0) {
                return small_left(ptr);
            } else {
                return big_left(ptr);
            }
        } else if (ptr->deltaH == 2) {
            if (ptr->less->deltaH >= 0) {
                return small_right(ptr);
            } else {
                return big_right(ptr);
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