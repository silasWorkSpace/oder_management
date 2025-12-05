#pragma once

#include <string>
using namespace std;

struct Product {
    string name;
    string productID;
    double unitPrice;
    double quantity;
    Product() : unitPrice(0), quantity(0) {}
};

// Linked list sản phẩm trong 1 đơn
struct ProductNode {
    Product data;
    ProductNode* next;
    ProductNode() : next(NULL) {}
};

struct Order {
    string id;        // Mã đơn hàng
    string customer;  // Tên khách hàng
    long long total;     // Tổng tiền = sum(unitPrice * quantity)
    ProductNode* products; // danh sách sản phẩm

    Order() : total(0), products(NULL) {}
};

struct Customer {
    string name;
    string customerID;
    string contactNumber;
};

struct Node {
    Order order;
    Customer customer;
    Node* next;
    Node() : next(NULL) {}
};

struct List {
    Node* first;
    Node* last;
    List() : first(NULL), last(NULL) {}
};

struct BSTNode {
    string key;
    Node* ref;
    BSTNode* left;
    BSTNode* right;
    BSTNode() : ref(NULL), left(NULL), right(NULL) {}
};

const int HASH_SIZE = 211;

struct HTRefNode {
    Node* ref;
    HTRefNode* next;
    HTRefNode() : ref(NULL), next(NULL) {}
};

struct HTEntry {
    string name;
    HTRefNode* refs;
    HTEntry* next;
    HTEntry() : refs(NULL), next(NULL) {}
};

struct HashTable {
    HTEntry* bucket[HASH_SIZE];
    HashTable() { for (int i = 0; i < HASH_SIZE; ++i) bucket[i] = NULL; }
};

