#ifndef TREE_H
#define TREE_H

// Struktur fuer binaere Suchbaume
#include <string>
using namespace std;

struct TreeNode {
    struct TreeNode* up;
    int key;
    string info;
    string color;
    struct TreeNode* left;
    struct TreeNode* right;
};

class Tree {
private:
    struct TreeNode* root = NULL;
    struct TreeNode* nil = NULL;
public:
    Tree();
    struct TreeNode* NewTreeNode(int key, string info, string color);
    struct TreeNode* TreeExample1();
    void TreePrint(struct TreeNode* tree);
    void TreePrint(struct TreeNode* tree, int indentation);
    struct TreeNode* TreeInsert(struct TreeNode* tree, int key, string info);
    struct TreeNode* TreeSearch(struct TreeNode* tree, int key);
    void TreeUpdate(struct TreeNode* tree, int key, string info);
    struct TreeNode* TreeGenerateRandomTree(int n, int seed);
    struct TreeNode* TreeExampleSequenceN(int n);
    struct TreeNode* TreeExampleFullLevelN(int n);
    // RS Funktionen
    void TreeRightRotate(struct TreeNode* rotateThisNode);
    void TreeLeftRotate(struct TreeNode* rotateThisNode);
    void TreeInsertFixRB(struct TreeNode* node);
};


#endif // TREE_H
