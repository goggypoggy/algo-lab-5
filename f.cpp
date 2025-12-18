#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <print>

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
            memset(buf[i], '#', width);
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

    /*
    P1 -----
    |      |
    ----- P2
    */
    Rect getSubrect(
        int x1, int y1,
        int x2, int y2) {
        Rect subrect;

        int new_w = x2 - x1 + 1;
        int new_h = y2 - y1 + 1;

        subrect.buf = new char*[new_h];
        subrect.h = new_h;
        subrect.w = new_w;

        for (int i = 0; i < new_h; ++i) {
            subrect.buf[i] = buf[i + y1] + x1;
        }

        return subrect;
    }
};

struct Node {
    Node* less;
    Node* more;
    Node* parent;
    int data;
    int vert = 1;
    int hor = 1;

    Node(int x, Node* prnt = nullptr, Node* left = nullptr, Node* right = nullptr)
    : data(x), hor(len(x)), less(left), more(right), parent(prnt)
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

    void backtrack() {
        
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
            int height_left = (*ptr)->less == nullptr ? 0 : (*ptr)->less->vert;
            int height_right = (*ptr)->more == nullptr ? 0 : (*ptr)->more->vert;
            
            (*ptr)->hor += len(x);

            if (x < (*ptr)->data) {
                if (height_left >= height_right) {
                    (*ptr)->vert++;
                }
                parent = *ptr;
                ptr = &((*ptr)->less);
            } else {
                if (height_right >= height_left) {
                    (*ptr)->vert++;
                }
                parent = *ptr;
                ptr = &((*ptr)->more);
            }
        }

        *ptr = new Node(x, parent);
    }

    void drawRect() {
        Rect result(root->vert, root->hor);
        drawRectRec(root, result);
        result.output();
    }

    void output() {
        root->output();
        std::cout << "\n";
    }

private:
    void add_first(int x) {
        root = new Node(x);
    }

    void drawRectRec(Node* ptr, Rect& rect) {
        std::string num = std::to_string(ptr->data);

        int num_start = ptr->less == nullptr ? 0 : ptr->less->hor;

        for (int i = 0; i < num.size(); ++i) {
            rect.draw(num_start + i, 0, num[i]);
        }

        if (ptr->less != nullptr) {
            std::cout << 0 << " " << 1 << " " << ptr->less->hor - 1 << " " << rect.h - 1 << "\n";
            Rect subrect = rect.getSubrect(0, 1, ptr->less->hor - 1, rect.h - 1);
            drawRectRec(ptr->less, subrect);
        }
        if (ptr->more != nullptr) {
            std::cout << num_start + num.size() << " " << 1 << " " << rect.w - 1 << " " << rect.h - 1 << "\n";
            Rect subrect = rect.getSubrect(num_start + num.size(), 1, rect.w - 1, rect.h - 1);
            drawRectRec(ptr->more, subrect);
        }
    }
};

int main(int, char**) {
    Tree tree;

    tree.add(300);
    tree.add(2);
    tree.add(6000);
    tree.add(40);

    tree.output();

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