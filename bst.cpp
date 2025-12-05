#include "bst.h"
#include "list.h"

BSTNode* bstNew(const string& k, Node* r) {
    BSTNode* x = new BSTNode;
    x->key = k;
    x->ref = r;
    x->left = x->right = NULL;
    return x;
}

BSTNode* bstInsertOrUpdate(BSTNode* root, const string& k, Node* r) {
    if (!root) return bstNew(k, r);
    if (k < root->key) root->left = bstInsertOrUpdate(root->left, k, r);
    else if (k > root->key) root->right = bstInsertOrUpdate(root->right, k, r);
    else root->ref = r;
    return root;
}

BSTNode* bstFind(BSTNode* root, const string& k) {
    if (!root) return NULL;
    if (k == root->key) return root;
    if (k < root->key) return bstFind(root->left, k);
    return bstFind(root->right, k); 
}

BSTNode* bstMin(BSTNode* x) {
    while (x && x->left)
        x = x->left;
    return x;
}

BSTNode* bstDelete(BSTNode* root, const string& k, bool& ok) {
    if (!root) return NULL;
    if (k < root->key) root->left = bstDelete(root->left, k, ok);
    else if (k > root->key) root->right = bstDelete(root->right, k, ok);
    else {
        ok = true;
        if (!root->left) {
            BSTNode* r = root->right;
            delete root;
            return r;
        }
        if (!root->right) {
            BSTNode* l = root->left;
            delete root;
            return l;
        }
        BSTNode* m = bstMin(root->right);
        root->key = m->key;
        root->ref = m->ref;
        root->right = bstDelete(root->right, m->key, ok);
    }
    return root;
}

void bstInorder(BSTNode* root) {
    if (!root) return;

    bstInorder(root->left);

    if (root->ref) {
        printRow(root->ref);                          // in dòng tổng
        printProducts(root->ref->order.products);     // in các product của đơn đó
        cout << "\n";                                 // cách 1 dòng giữa các order
    }

    bstInorder(root->right);
}

void bstClear(BSTNode* root) {
    if (!root) return;
    bstClear(root->left);
    bstClear(root->right);
    delete root;
}
