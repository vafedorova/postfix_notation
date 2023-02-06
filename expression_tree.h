#ifndef _EXPRESSION_TREE_H_
#define _EXPRESSION_TREE_H_
#include <string>
enum Operation {add = '+', subtract = '-', multiply = '*', divide = '/', value = 0};

class Node {
    Operation operation;
    int value;
    bool value_calculated;
    bool calulate_value();
    Node *first_operand = nullptr;
    Node *second_operand = nullptr;
    public:
    Node(Operation op, int value = 0) :
        operation(op), value_calculated(op == Operation::value), value(value),
        first_operand(nullptr), second_operand(nullptr)
    {

    };
    int get_value();
    void set_operands(Node *first, Node *second) {
        first_operand = first;
        second_operand = second;
    }
    friend Node *create_tree_from_postfix(const std::string &s);
    friend Node *create_tree_from_infix(const std::string &s);

    friend std::ostream &operator<<(std::ostream &os, Node &node);
    friend void print_tree_as_prefix(Node *root, std::ostringstream &os);
    friend void print_tree_as_postfix(Node *root, std::ostringstream &os);
};

std::ostream &operator<<(std::ostream &os, Node &node);
void print_tree_as_prefix(Node *root, std::ostringstream &os);
void print_tree_as_postfix(Node *root, std::ostringstream &os);
Node *create_tree_from_prefix(const std::string &s);
Node *create_tree_from_postfix(const std::string &s);
Node *create_tree_from_infix(const std::string &s);
std::string prefix_from_tree(Node *root);
std::string postfix_from_tree(Node *root);
std::string infix_from_tree(Node *root);
#endif 