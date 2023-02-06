#include "expression_tree.h"
#include <vector>
#include <cassert>
#include <exception>
#include <iostream>

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

Node *create_tree_from_prefix(const string &s) {
    throw logic_error("Not implemented yet");
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
    throw logic_error("Not implemented yet");
}