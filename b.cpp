#include <iostream>
#include <string>
#include <sstream>

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
            std::cout << nd->data;
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

void reverse_output(Stack& stack) {
    Stack extra_stack;

    while (stack.size > 0) {
        extra_stack.push(stack.pop());
    }

    extra_stack.output();
}

int main(int, char**) {
    int k;
    std::cin >> k;
    
    std::stringstream input_stream;
    char c;
    while (std::cin >> c) {
        input_stream << c;
    }

    std::string input = input_stream.str();
    
    Stack stack;
    for (int i = 0; i < input.size(); ++i) {
        int cur = input[i] - '0';
        
        if (stack.size == 0) {
            stack.push(cur);
            continue;
        }

        if (cur > stack.get_top() && stack.size + input.size() - i > k) {
            while (stack.size != 0 && cur > stack.get_top() && stack.size + input.size() - i > k) {
                stack.pop();
            }
            stack.push(cur);
        } else if (k > stack.size) {
            stack.push(cur);
        }
    }

    reverse_output(stack);

    return 0;
}