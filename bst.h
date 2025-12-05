#pragma once
#include "structs.h"

BSTNode* bstNew(const string& k, Node* r);
BSTNode* bstInsertOrUpdate(BSTNode* root, const string& k, Node* r);
BSTNode* bstFind(BSTNode* root, const string& k);
BSTNode* bstMin(BSTNode* x);
BSTNode* bstDelete(BSTNode* root, const string& k, bool& ok);
void bstInorder(BSTNode* root);
void bstClear(BSTNode* root);
