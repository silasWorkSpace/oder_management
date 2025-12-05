#pragma once

#include "structs.h"
#include "bst.h"
#include "list.h"
#include "hashtable.h"
#include <fstream>

struct Manager {
    List store;
    BSTNode* idIndex;
    HashTable custIdx;

    void init();
    void addOrUpdate();
    void remove();
    void searchById();
    void searchByCustomer();
    void showAllSorted();
    void save(const string& path);
    void load(const string& path);
};

