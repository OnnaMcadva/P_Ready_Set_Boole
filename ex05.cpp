
#include <iostream>
#include <string>
#include <stack>

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char v) : value(v), left(nullptr), right(nullptr) {}
};

Node* build_ast(const std::string& formula) {
    std::stack<Node*> st;

    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            st.push(new Node(c));
        } else if (c == '!') {
            Node* a = st.top(); st.pop();
            Node* node = new Node('!');
            node->left = a;
            st.push(node);
        } else {
            Node* b = st.top(); st.pop();
            Node* a = st.top(); st.pop();
            Node* node = new Node(c);
            node->left = a;
            node->right = b;
            st.push(node);
        }
    }

    return st.top();
}

Node* clone(Node* node) {
    if (!node) return nullptr;
    Node* copy = new Node(node->value);
    copy->left = clone(node->left);
    copy->right = clone(node->right);
    return copy;
}

Node* to_nnf(Node* node, bool negated = false) {
    if (!node) return nullptr;

    if (node->value >= 'A' && node->value <= 'Z') {
        if (negated) {
            Node* neg_node = new Node('!');
            neg_node->left = clone(node);
            return neg_node;
        }
        return clone(node);
    }

    if (node->value == '!') {
        return to_nnf(node->left, !negated);
    }

    if (!negated) {
        if (node->value == '>') {
            // A > B → !A | B
            Node* a = to_nnf(node->left, true);
            Node* b = to_nnf(node->right, false);
            Node* or_node = new Node('|');
            or_node->left = a;
            or_node->right = b;
            return or_node;
        } else if (node->value == '=') {
            // A = B → (A & B) | (!A & !B)
            Node* a = to_nnf(node->left, false);
            Node* b = to_nnf(node->right, false);
            Node* not_a = to_nnf(node->left, true);
            Node* not_b = to_nnf(node->right, true);

            Node* and1 = new Node('&'); and1->left = a; and1->right = b;
            Node* and2 = new Node('&'); and2->left = not_a; and2->right = not_b;

            Node* or_node = new Node('|'); or_node->left = and1; or_node->right = and2;
            return or_node;
        }
    }

    char op = node->value;
    Node* a = node->left;
    Node* b = node->right;

    if (negated) {
        char new_op = (op == '&') ? '|' : '&';
        Node* left = to_nnf(a, true);
        Node* right = to_nnf(b, true);
        Node* res = new Node(new_op);
        res->left = left;
        res->right = right;
        return res;
    } else {
        Node* left = to_nnf(a, false);
        Node* right = to_nnf(b, false);
        Node* res = new Node(op);
        res->left = left;
        res->right = right;
        return res;
    }
}

void to_rpn(Node* node, std::string& result) {
    if (!node) return;
    to_rpn(node->left, result);
    to_rpn(node->right, result);
    result += node->value;
}

void delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

std::string negation_normal_form(const std::string& formula) {
    Node* ast = build_ast(formula);
    Node* nnf_ast = to_nnf(ast);
    std::string result;
    to_rpn(nnf_ast, result);
    delete_tree(ast);
    delete_tree(nnf_ast);
    return result;
}

// int main() {
//     std::cout << negation_normal_form("AB&!") << "\n";     // A!B!|
//     std::cout << negation_normal_form("AB|!") << "\n";     // A!B!&
//     std::cout << negation_normal_form("AB>") << "\n";      // A!B|
//     std::cout << negation_normal_form("AB=") << "\n";      // AB&A!B!&|
//     std::cout << negation_normal_form("AB|C&!") << "\n";   // A!B!&C!|
//     return 0;
// }