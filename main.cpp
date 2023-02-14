#include <vector>
#include <iostream>
#include <cassert>
#include "expression_tree.h"

using namespace std;

int main() {
    string notation;
    cin >> notation;
    string s;
    getline(cin, s); //TODO: FIX!!!
    getline(cin, s);
    Node *root = nullptr;
    if (notation == "prefix") {
        root = create_tree_from_prefix(s);
    }
    else if (notation == "postfix") {
        root = create_tree_from_postfix(s);
    } 
    else if (notation == "infix") {
        root = create_tree_from_infix(s);
    }
    else {
        assert(false);
    }
    cout << (root != nullptr ? root->get_value() : 0) << endl;
    cout << prefix_from_tree(root) << endl;
    cout << postfix_from_tree(root) << endl;
    cout << infix_from_tree(root) << endl;
}