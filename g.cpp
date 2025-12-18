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
        // delete less;
        // delete more;
    }

    int deltaH() {
        return (less == nullptr ? 0 : less->size) - (more== nullptr ? 0 : more->size);
    }

    void updateSize() {
        int left = (less == nullptr ? 0 : less->size);
        int right = (more== nullptr ? 0 : more->size);

        size = std::max(left, right) + 1;
    }

    void isolate() {
        less = nullptr;
        more = nullptr;
    }

    void backtrack() {
        size--;
        if (parent != nullptr) {
            parent->backtrack();
        }
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
        std::cout << "[" << data << " (" << size << ") ^(" << (parent == nullptr ? 0 : parent->data) << ")]";
        if (more != nullptr) {
            std::cout << " ";
            more->output_debug();
        }
    }
};

struct Tree {
    Node* root = nullptr;

    void insert(int x) {
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
        balance(ptr);
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

    void small_left(Node** a) {
        Node* b = (*a)->more;
        std::cout << (*a)->parent << " " << (*a) << '\n';
        Node* prev_parent = (*a)->parent;
        // (*a)->more->parent = (*a)->parent;
        (*a)->output_debug();

        Node* c = b->less;
        
        (*a)->more = c;
        if (c != nullptr) {
            c->parent = (*a);
        }
        (*a)->updateSize();
        

        b->less = (*a);
        (*a)->parent = b;
        b->updateSize();

        b->parent = prev_parent;
        b->output_debug();
        *a = b;
        
    }

    void balance(Node** ptr) {
        std::cout << "balancing:\n";
        (*ptr)->output_debug();
        std::cout << "\n";

        if ((*ptr)->deltaH() == 2) {
            Node* a = (*ptr)->less;

            if (a->deltaH() >= 0) {
                // малый правый
            } else {
                // большой правый
            }
        } else if ((*ptr)->deltaH() == -2) {
            Node* b = (*ptr)->more;

            if (b->deltaH() <= 0) {
                // малый левый
                std::cout << "small left on " << (*ptr)->data << "\n";
                small_left(ptr);
                //Node* b = (*ptr)->more;
                // std::cout << (*ptr)->more->parent->data << '\n';
                // // b->parent = (*ptr)->parent;
                // (*ptr)->more->parent = (*ptr)->parent;
                // (*ptr)->output_debug();

                // Node* c = b->less;
                
                // (*ptr)->more = c;
                // if (c != nullptr) {
                //     c->parent = (*ptr);
                // }
                // (*ptr)->updateSize();
                

                // b->less = (*ptr);
                // (*ptr)->parent = b;
                // b->updateSize();

                // *ptr = b;
            } else {
                // большой левый
            }
        }

        std::cout << "result:\n";
        (*ptr)->output_debug();
        std::cout << "\n";

        if ((*ptr)->parent != nullptr) {
            balance(&((*ptr)->parent));
        }
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