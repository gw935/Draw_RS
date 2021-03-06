// Struktur fuer binaere Suchbaume

#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include "tree.h"
using namespace std;

// Erzeuge einen neuen Knoten
struct TreeNode* Tree::NewTreeNode(int key, string info, string color) {
    struct TreeNode* node = new TreeNode();
    node->up = nil;
    node->key = key;
    node->info = info;
    node->left = nil;
    node->right = nil;
    node->color = color;
    return(node);
}

Tree::Tree() {
    nil = new TreeNode;
    nil->color = "BLACK";
    nil->left = nullptr;
    nil->right = nullptr;
    nil->key = 0;
    nil->info = "";
    root = nil;
}


// Erzeuge einen Beispielbaum (binaerer Suchbaum mit 5 Knoten)
// Schlechte Implementierung (ohne TreeInsert())
// Schlecht, denn je mehr Knoten im Baum sind, desto mehr Zeiger muessen (fehleranfaellig) von Hand gesetzt werden.
// Bis naechste Woche TreeInsert() bitte sauber implementieren, dann den unten auskommenierten Programmcode benutzen.
//struct TreeNode* TreeExample1() {
//    struct TreeNode* tree = NewTreeNode(40, "Info zu Schluessel 40");
//    tree->left = NewTreeNode(10, "Info zu Schluessel 10"); tree->left->up = tree;
//    tree->right = NewTreeNode(70, "Info zu Schluessel 70"); tree->right->up = tree;
//    tree->right->left = NewTreeNode(60, "Info zu Schluessel 60"); tree->right->left->up = tree->right;
//    tree->right->right = NewTreeNode(80, "Info zu Schluessel 80"); tree->right->right->up = tree->right;
//    return(tree);
//}

struct TreeNode* Tree::TreeExample1() {
    struct TreeNode* tree = NULL;
    tree = Tree::TreeInsert(tree, 40, "Info zu Schluessel 40");
    tree = Tree::TreeInsert(tree, 10, "Info zu Schluessel 10");
    tree = Tree::TreeInsert(tree, 70, "Info zu Schluessel 70");
    tree = Tree::TreeInsert(tree, 60, "Info zu Schluessel 60");
    tree = Tree::TreeInsert(tree, 80, "Info zu Schluessel 80");
    return(tree);
}





// Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht
// Rücke jede Zeile mit sovielen Tabs ein, wie in indentation angegeben
void Tree::TreePrint(struct TreeNode* tree, int indentation) {
    int i;
    if (tree!=NULL) {
        TreePrint(tree->right, indentation+1);
        for (i=0;i <indentation; i++) {
            cout << "\t";
        }
    cout << "(key: " << tree->key << ", info: '" << tree->info << "')\n\n\n";
        TreePrint(tree->left, indentation+1);
    }
    return;
}


// Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht
void Tree::TreePrint(struct TreeNode* tree) {
    cout << "\n\n";
    TreePrint(tree, 0);
}

// Fuege den Schluessel key mit Infoteil info in den binaeren Suchbaum tree ein
// Fuege den Schluessel key mit Infoteil info in den binaeren Suchbaum tree ein
struct TreeNode* Tree::TreeInsert(struct TreeNode* tree, int key, string info) {
    // Einfuegen, wenn noch kein Knoten existiert
    if(tree == nullptr) {
        cout << "DEBUG (Insert): Lege ersten Knoten " << key << " an." << endl;
        tree = Tree::NewTreeNode(key, info, "BLACK");
        root = tree;
    }
    // Einfuegen, wenn bereits Knoten existieren
    else {
        // Pruefen, wo der Knoten eingefuegt werden soll
        // Ist der derzeit angeschaute Knoten..
        // ...groesser...
        if(tree->key > key) {
            // Schaue unten links...
            if(tree->left == nil) {
                // Lege Knoten an, falls noch kein Knoten existiert
                tree->left = Tree::NewTreeNode(key, info, "RED");
                tree->left->up = tree;
                TreeInsertFixRB(tree->left);

                if(tree->up != nil) {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " links unter Knoten " << tree->up->key << " an." << endl;
                }
                else {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " links unter Wurzel " << tree->key << " an." << endl;
                }
            }
            else {
                TreeInsert(tree->left, key, info);
            }
        }
        // ...kleiner...
        else if(tree->key < key) {
            // Schaue unten rechts...
            if(tree->right == nil) {
                // Lege Knoten an, falls noch kein Knoten existiert
                tree->right = Tree::NewTreeNode(key, info, "RED");
                tree->right->up = tree;
                TreeInsertFixRB(tree->right);

                if(tree->up != nil) {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " rechts unter Knoten " << tree->up->key << " an." << endl;
                }
                else {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " rechts unter Wurzel " << tree->key << " an." << endl;
                }
            }
            else {
                TreeInsert(tree->right, key, info);
            }
        }
        // oder existiert bereits ein Knoten mit gleichem Wert?
        else {
            //cout << "DEBUG (Insert): Knoten " << key << " existiert bereits." << endl;
        }
    }
    return tree; // Wurzel des Baums ausgeben
}


void Tree::TreeInsertFixRB(struct TreeNode* z) {
    while(z->up->color == "RED"){

            /* z's parent is left child of z's grand parent*/
            if(z->up == z->up->up->left){

                /* z's grand parent's right child is RED */
                if(z->up->up->right->color == "RED"){
                    z->up->color = "BLACK";
                    z->up->up->right->color = "BLACK";
                    z->up->up->color = "RED";
                    z = z->up->up;
                }

                /* z's grand parent's right child is not RED */
                else{

                    /* z is z's parent's right child */
                    if(z == z->up->right){
                        z = z->up;
                        TreeLeftRotate(z);
                    }

                    z->up->color = "BLACK";
                    z->up->up->color = "RED";
                    TreeRightRotate(z->up->up);
                }
            }

            /* z's parent is z's grand parent's right child */
            else{

                /* z's left uncle or z's grand parent's left child is also RED */
                if(z->up->up->left->color == "RED"){
                    z->up->color = "BLACK";
                    z->up->up->left->color = "BLACK";
                    z->up->up->color = "RED";
                    z = z->up->up;
                }

                /* z's left uncle is not RED */
                else{
                    /* z is z's parents left child */
                    if(z == z->up->left){
                        z = z->up;
                        TreeRightRotate(z);
                    }

                    z->up->color = "BLACK";
                    z->up->up->color = "RED";
                    TreeLeftRotate(z->up->up);
                }
            }
        }

        root->color = "BLACK";
}


// Gib Zeiger auf den Knoten im binaeren Suchbaum tree zurueck, der den Schluessel key speichert
// Wenn der Schluessel nicht vorhanden ist soll NULL zurueckgegeben werden
struct TreeNode* Tree::TreeSearch(struct TreeNode* tree, int key){
    if(tree->key == key){
        return tree;
    } else if(tree->key > key){
        TreeSearch(tree->left, key);
    } else if(tree->key < key){
        TreeSearch(tree->right, key);
    }
    return nullptr;
}


void Tree::TreeRightRotate(struct TreeNode* rotateThisNode) {
    struct TreeNode* x = rotateThisNode;
    struct TreeNode* y = x->left;
    if(x->left != nil){
        x->left = y->right;
        if (y->right != nil)
            y->right->up = x;
        y->up = x->up;
        if (x->up == nil)
            this->root = y;
        else if (x == x->up->right)
            x->up->right = y;
        else
            x->up->left = y;
        y->right = x;
        x->up = y;
    }
}

void Tree::TreeLeftRotate(struct TreeNode* rotateThisNode) {
    struct TreeNode* x = rotateThisNode;
    struct TreeNode* y = x->right;
    if(x->right != nil){
        x->right = y->left;
        if (y->left != nil)
            y->left->up = x;

        y->up = x->up;

        if (x->up == nil)
            this->root = y;
        else if (x == x->up->left)
            x->up->left = y;
        else
            x->up->right = y;
        y->left = x;
        x->up = y;
    }
}
