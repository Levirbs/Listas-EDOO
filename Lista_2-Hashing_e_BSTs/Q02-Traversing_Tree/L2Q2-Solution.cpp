#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    
private:
    TreeNode* root;

    // Metodo recursivo para inserir um valor na arvore
    TreeNode* insert(TreeNode* node, int value) {
        if (!node) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }

        else if (value >= node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Metodo recursivo para exibir a arvore em pre-ordem
    void preOrder(TreeNode* node, bool& first) const {
        if (!node) {
            return;
        }

        if (!first) {
            cout << " ";
        }

        cout << node->data;
        first = false;
        preOrder(node->left, first);
        preOrder(node->right, first);
    }

    // Metodo recursivo para exibir a arvore em ordem
    void inOrder(TreeNode* node, bool& first) const {
        if (!node) {
            return;
        }

        inOrder(node->left, first);
        if (!first) {
            cout << " ";
        }

        cout << node->data;
        first = false;
        inOrder(node->right, first);
    }

    // Metodo recursivo para exibir a arvore em pos-ordem
    void postOrder(TreeNode* node, bool& first) const {
        if (!node) {
            return;
        }

        postOrder(node->left, first);
        postOrder(node->right, first);

        if (!first) {
            cout << " ";
        }

        cout << node->data;
        first = false;
    }

    // Metodo recursivo para destruir a arvore e liberar memoria
    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    // Construtor da arvore binaria
    BinaryTree() : root(nullptr) {}

    // Destrutor da arvore binaria
    ~BinaryTree() {
        destroy(root);
    }  

    // Metodo publico para inserir um valor na arvore
    void insert(int value) {
        root = insert(root, value);
    }

    // Metodo publico para exibir a arvore em uma ordem especifica
    void Display() const {
        bool first = true;

            cout << "Pre order : ";
            preOrder(root, first);

            cout << endl << "In order  :";
            inOrder(root, first);

            cout << endl << "Post order:";
            postOrder(root, first);
            
    }
};

int main() {
    int n, data;
    cin >> n;
    BinaryTree tree;

    for (int i = 0; i < n; ++i) {
        cin >> data;
        tree.insert(data);
    }

    tree.Display();

    return 0;

}