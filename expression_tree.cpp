#include "expression_tree.h"
#include <vector>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <stack>

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

ostream &operator<< (ostream &os, Node *node) {
    if (node == nullptr)
    {
        os << "nullptr";
        return os;
    }
    os << *node;
    return os;
}

Node *parse_expression_prefix(string &str);

Node *create_tree_from_prefix(const string &s) {
    string str = s + ' ';
    return parse_expression_prefix(str);
}

Node *parse_expression_prefix(string &str) {
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
        curr_node->set_operands(parse_expression_prefix(str), parse_expression_prefix(str));
        return curr_node;
    }
    return nullptr;
}

Node *parse_expression_postfix(string &str);

Node *create_tree_from_postfix(const string &s) {
    string str = s;
    reverse(str.begin(), str.end());
    str += ' ';
    return parse_expression_postfix(str);
}

Node *parse_expression_postfix(string &str) {
    size_t pos = string::npos;
    string lexeme;
    if ((pos = str.find(' ')) != string::npos) {
        lexeme = str.substr(0, pos);
        str = str.substr(pos + 1);
        // lexeme = '234' | '1' | '+' | '-' | ...
        if (isdigit(lexeme[0])) {
            reverse(lexeme.begin(), lexeme.end());
            int num = atoi(lexeme.c_str());
            return new Node(Operation::value, num);
        }
        assert(lexeme.size() == 1);
        Operation op = static_cast<Operation>(lexeme[0]);
        Node *curr_node = new Node(op);
        Node *second = parse_expression_postfix(str);
        Node *first = parse_expression_postfix(str);
        curr_node->set_operands(first, second);
        return curr_node;
    }
    return nullptr;
}

Node *parse_expression_infix(string &str);

Node *create_tree_from_infix(const string &s) {
    string str = s;
    return parse_expression_infix(str);
}

// str = '-123 - 543'
Node *parse_expression_infix(string &str) {
    ostringstream stack_os;
    Node *root = nullptr;
    Node *curr_node = root;
    stack<Node *> st;
    int i = 0;
    int sign = 1;
    while (i != str.size()) {
        //cout << i << ": " << str[i] << " stack.size = " << st.size() << endl;
        if (isdigit(str[i])) {
            ostringstream digit;
            digit << str[i];
            while (++i < str.size() && isdigit(str[i]))
                digit << str[i];
            Node *value_node = new Node(Operation::value, sign * atoi(digit.str().c_str()));
            if (sign == -1)
                sign *= -1;
            if (st.empty() || st.top() == nullptr) {
                st.push(value_node);
                stack_os << "push " << st.top() << "\n";
            }
            else {
                Node *op_node = st.top();
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                op_node->set_operands(st.top(), value_node);
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                st.push(op_node);
                stack_os << "push " << st.top() << "\n";

            }
            i--;
        } 
        else if (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/') {
            if (str[i] == '-') {
                if (st.empty() || st.top() == nullptr || st.top()->operation != 0) {
                    sign *= -1;
                    i++;
                    continue;
                }
            }
            Node *op_node = new Node(static_cast<Operation>(str[i]));
            st.push(op_node);   
            stack_os << "push " << st.top() << "\n";
        }
        else if (str[i] == '(')  {
            st.push(nullptr); // nullptr in stack stands for '('
            stack_os << "push " << st.top() << "\n";
        }
        else if (str[i] == ')')  {
            Node *top_node = st.top();
            stack_os << "pop " << st.top() << "\n";
            assert(!st.empty());
            st.pop();
            if (st.top() == nullptr) {
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                st.push(top_node);
                stack_os << "push " << st.top() << "\n";
            } else {
                st.push(top_node);
                stack_os << "push " << st.top() << "\n";
                Node *right = st.top();
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                Node *op_node = st.top();
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                Node *left = st.top();
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop();
                assert(st.top() == nullptr);
                stack_os << "pop " << st.top() << "\n";
                assert(!st.empty());
                st.pop(); //pop '(' from stack
                op_node->set_operands(left, right);
                st.push(op_node);
                stack_os << "push " << st.top() << "\n";
            }
        }
        else if (str[i] == ' ')  {
        }
        i++;
    }
    if (st.size() > 1) {
        assert(st.size() == 3);
        Node *right = st.top();
        stack_os << "pop " << st.top() << "\n";
        assert(!st.empty());
        st.pop();
        Node *op_node = st.top();
        stack_os << "pop " << st.top() << "\n";
        assert(!st.empty());
        st.pop();
        Node *left = st.top();
        stack_os << "pop " << st.top() << "\n";
        assert(!st.empty());
        st.pop();
        op_node->set_operands(left, right);
        st.push(op_node);
        stack_os << "push " << st.top() << "\n";
    }
    // cout << stack_os.str();
    return st.top();
}

string prefix_from_tree(Node *root) {
    ostringstream os;
    os << "prefix: ";
    print_tree_as_prefix(root, os);
    return os.str();
}

string postfix_from_tree(Node *root) {
    ostringstream os;
    os << "postfix: ";
    print_tree_as_postfix(root, os);
    return os.str();
}

string infix_from_tree(Node *root) {
    ostringstream os;
    print_tree_as_infix(root, os);
    string result_wo_parenths = os.str();
    return "infix: " + result_wo_parenths.substr(1, result_wo_parenths.size() - 2);
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

void print_tree_as_infix(Node *root, ostringstream &os) {
    if (root == nullptr) {
        return;
    }
    if (root->operation == Operation::value) {
        os << *root;
        assert(root->first_operand == nullptr && root->second_operand == nullptr);
    }
    else {
        os << "(";
        print_tree_as_infix(root->first_operand, os);
        os << " " <<  *root << " ";
        print_tree_as_infix(root->second_operand, os);
        os << ")";
    }
}