#include "expression_tree.h"
#include <vector>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>

using namespace std;

vector<char> operation_symbols = {'+', '-', '/', '*'};

bool Node::calulate_value() {
    switch (operation) {
        case add:
            value = first_operand->get_value() + second_operand->get_value();
            value_calculated = true;
            break;
        case subtract:
            value = first_operand->get_value() - second_operand->get_value();
            value_calculated = true;
            break;
        case multiply:
            value = first_operand->get_value() * second_operand->get_value();
            value_calculated = true;
            break;
        case divide:
            value = first_operand->get_value() / second_operand->get_value();
            value_calculated = true;
            break;
        case Operation::value:
            break;
    }
    return value_calculated;
}

int Node::get_value() {
    if (value_calculated || !value_calculated && calulate_value()) {
        return value;
    }
    assert(false);
    return 0;
}

ostream &operator<< (ostream &os, Node &node) {
    if (node.operation == Operation::value)
        os << node.get_value();
    else
        os << static_cast<char>(node.operation);
    return os;
}

Node *parse_expression(string &str);

Node *create_tree_from_prefix(const string &s) {
    string str = s + ' ';
    return parse_expression(str);
}

Node *parse_expression(string &str) {
    size_t pos = string::npos;
    string lexeme;
    if ((pos = str.find(' ')) != string::npos) {
        lexeme = str.substr(0, pos);
        str = str.substr(pos + 1);
        // lexeme = '234' | '1' | '+' | '-' | ...
        if (isdigit(lexeme[0])) {
            int num = atoi(lexeme.c_str());
            return new Node(Operation::value, num);
        }
        assert(lexeme.size() == 1);
        Operation op = static_cast<Operation>(lexeme[0]);
        Node *curr_node = new Node(op);
        curr_node->set_operands(parse_expression(str), parse_expression(str));
        return curr_node;
    }
    return nullptr;
}

Node *create_tree_from_postfix(const string &s) {
    Node *root = nullptr;
    size_t pos = string::npos;
    string str = s;
    string lexeme;
    while  ((pos = str.find(' ')) != string::npos) {
        lexeme = str.substr(0, pos);
        str = str.substr(pos + 1);
        cout << str << "  lexeme = " << lexeme << endl;
        if (isdigit(lexeme[0])) {

        } else {

        }
    }
    lexeme = str;
    str = "";
    cout << str << "  lexeme = " << lexeme << endl;
    return root;
}

Node *create_tree_from_infix(const string &s) {
    Node *root = nullptr;
    size_t pos = string::npos;
    string str = s;
    string lexeme;
    while  ((pos = str.find(' ')) != string::npos) {
        lexeme = str.substr(0, pos);
        str = str.substr(pos + 1);
        cout << str << "  lexeme = " << lexeme << endl;
        if (isdigit(lexeme[0])) {

        } else {

        }
    }
    lexeme = str;
    str = "";
    cout << str << "  lexeme = " << lexeme << endl;
    return root;
}

string prefix_from_tree(Node *root) {
    ostringstream os;
    print_tree_as_prefix(root, os);
    return os.str();
}

string postfix_from_tree(Node *root) {
    ostringstream os;
    print_tree_as_postfix(root, os);
    return os.str();
}

void print_tree_as_prefix(Node *root, ostringstream &os) {
    if (root == nullptr) {
        return;
    }
    os << *root << " ";
    print_tree_as_prefix(root->first_operand, os);
    print_tree_as_prefix(root->second_operand, os);
}

void print_tree_as_postfix(Node *root, ostringstream &os) {
    if (root == nullptr) {
        return;
    }
    print_tree_as_postfix(root->first_operand, os);
    print_tree_as_postfix(root->second_operand, os);
    os << *root << " ";
}