#include <iostream>
#include <cstdlib>

void Swap( int *a, int *b ) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// [min; max]
int Rand( int min, int max ) {
    return min + (std::rand() % (max - min));
}

// [l; r)
void Partition( int l, int r, int *A ) {
    int pivot = A[Rand(l, r - 1)];
    int i = l;
    int j = r - 1;
    
    while (i <= j) {
        while (A[i] < pivot && i < r) {
            i++;
        }

        while (A[j] > pivot && j >= l) {
            j--;
        }

        if (i <= j) {
            Swap(A + i, A + j);
            i++;
            j--;
        }
    }

    if (l < j) {
        Partition(l, j + 1, A);
    }
    if (i < r - 1) {
        Partition(i, r, A);
    }
}

void QuickSort( int *A, int N ) {
    Partition(0, N, A);
}


struct Node {
    Node* next;
    int data;

    Node(int x, Node* nxt = nullptr)
    : data(x), next(nxt) {}

    ~Node() {
        delete next;
    }
};

struct Stack {
    Node* top = nullptr;
    size_t size = 0;

    void push(int x) {
        size++;
        if (top == nullptr) {
            add_first(x);
            return;
        }

        Node* new_node = new Node(x, top);
        top = new_node;
    }

    int pop() {
        size--;
        if (top->next == nullptr) {
            return pop_first();
        }

        int value = top->data;
        
        Node* old_node = top;
        top = top->next;
        old_node->next = nullptr;
        delete old_node;

        return value;
    }

    int get_top() {
        if (top == nullptr) {
            return -1;
        }
        return top->data;
    }

    ~Stack() {
        delete top;
    }

    void output() {
        for (Node* nd = top; nd != nullptr; nd = nd->next) {
            std::cout << nd->data << (nd->next == nullptr ? "\n" : ", ");
        }
    }

private:
    void add_first(int x) {
        top = new Node(x);
    }

    int pop_first() {
        // if (tail == nullptr) {
        //     throw;
        // }
        int value = top->data;

        delete top;
        top = nullptr;

        return value;
    }
};

int greedy_take(int* a, int n, int d) {
    Stack stack;

    stack.push(a[0]);

    for (int i = 1; i < n; ++i) {
        if (a[i] - d >= stack.get_top()) {
            stack.push(a[i]);
        }
    }

    // stack.output();
    return stack.size;
}

int main(int, char**) {
    int n;
    int k;

    std::cin >> n >> k;

    int* a = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    QuickSort(a, n);

    int l = 0;
    int r = a[n - 1] - a[0];
    
    while (l + 1 < r) {
        //std::cout << l << " " << m << " " << r << "\n";
        int m = (l + r) / 2;
        int res = greedy_take(a, n, m);
        if (res < k) {
            r = m;
        } else {
            l = m;
        }
        //std::cout << l << " " << m << " " << r << "\n";
    }

    std::cout << l;

    return 0;
}