#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

int len(int x) {
    if (x == 0) {
        return 1;
    }
    x++;
    return ceil(log10(static_cast<float>(x)));
}

struct Rect {
    char** buf = nullptr;
    int h = 0;
    int w = 0;

    Rect() = default;

    Rect(int height, int width)
    : h(height), w(width), buf(new char*[height]) {
        for (int i = 0; i < h; ++i) {
            buf[i] = new char[width];
            memset(buf[i], ' ', width);
        }
    }

    Rect(const Rect& other) = default;

    void free() {
        for (int i = 0; i < h; ++i) {
            delete[] buf[i];
        }
        delete[] buf;
    }

    void cleanUp() {
        for (int i = 0; i < h; ++i) {
            int j = w - 1;
            while (buf[i][j] == ' ') {
                buf[i][j] = 0;
                j--;
            }
        }
    }

    void draw(int x, int y, char c) {
        buf[y][x] = c;
    }

    void output() {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (buf[i][j] == 0) {
                    break;
                }
                std::cout << buf[i][j];
            }
            std::cout << '\n';
        }
    }
};

struct Node {
    Node* less;
    Node* more;

    int data;
    int vert = 1;
    int hor = 1;

    Node(int x, Node* left = nullptr, Node* right = nullptr)
    : data(x), hor(len(x)), less(left), more(right)
    {}

    ~Node() {
        delete less;
        delete more;
    }

    void output() {
        if (less != nullptr) {
            less->output();
        }
        std::cout << "[" << data << ", (" << vert << "x" << hor << ")" << "]";
        if (more != nullptr) {
            more->output();
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

        while (*ptr != nullptr) {
            if (x < (*ptr)->data) {
                ptr = &((*ptr)->less);
            } else {
                ptr = &((*ptr)->more);
            }
        }

        *ptr = new Node(x);
    }

    void setUp() {
        setUpRec(root);
    }

    void drawRect() {
        Rect result(root->vert, root->hor);
        drawRectRec(root, result, 0, 0, result.w - 1, result.h - 1);
        result.cleanUp();
        result.output();
        result.free();
    }

    void output() {
        root->output();
        std::cout << "\n";
    }

private:
    void add_first(int x) {
        root = new Node(x);
    }

    void setUpRec(Node* ptr) {
        ptr->vert = 0;
        ptr->hor = len(ptr->data);

        if (ptr->less != nullptr) {
            setUpRec(ptr->less);
            ptr->vert = std::max(ptr->vert, ptr->less->vert);
            ptr->hor += ptr->less->hor;
        }
        
        if (ptr->more != nullptr) {
            setUpRec(ptr->more);
            ptr->vert = std::max(ptr->vert, ptr->more->vert);
            ptr->hor += ptr->more->hor;
        }

        ptr->vert++;
    }

    void drawRectRec(
        Node* ptr, Rect& rect,
        int x1, int y1,
        int x2, int y2) {
        std::string num = std::to_string(ptr->data);

        int num_start = ptr->less == nullptr ? 0 : ptr->less->hor;

        for (int i = 0; i < num.size(); ++i) {
            rect.draw(x1 + num_start + i, y1, num[i]);
        }

        if (ptr->less != nullptr) {
            // std::cout << 0 << " " << 1 << " " << ptr->less->hor - 1 << " " << rect.h - 1 << "\n";
            drawRectRec(ptr->less, rect,
                x1, y1 + 1, 
                x1 + ptr->less->hor - 1, y2 - 1);
        }
        if (ptr->more != nullptr) {
            // std::cout << num_start + num.size() << " " << 1 << " " << rect.w - 1 << " " << rect.h - 1 << "\n";
            drawRectRec(ptr->more, rect,
                x1 + num_start + num.size(), y1 + 1,
                x2 - 1, y2 - 1);
        }
    }
};

int main(int, char**) {
    Tree tree;

    int x;
    while (std::cin >> x) {
        tree.add(x);
    }

    tree.setUp();

    // tree.output();

    tree.drawRect();

    // Rect r1(6, 6);

    // Rect r2 = r1.getSubrect(1, 1, 4, 4);

    // r2.buf[2][0] = '*';
    // r2.buf[2][1] = '*';
    // r2.buf[2][2] = '*';

    // r1.cleanUp();
    // r1.output();

    return 0;
}