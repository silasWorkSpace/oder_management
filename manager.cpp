#include "manager.h"
#include <fstream>
#include <iostream>
using namespace std;

// ===== Helper cho Product list =====
void addProductToOrder(Order& o, const Product& p) {
    ProductNode* node = new ProductNode;
    node->data = p;
    node->next = NULL;

    if (!o.products) {
        o.products = node;
    }
    else {
        ProductNode* cur = o.products;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    o.total += p.unitPrice * p.quantity;
}

void clearProducts(ProductNode*& head) {
    while (head) {
        ProductNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void Manager::init() {
    initList(store);
    idIndex = NULL;
    htInit(custIdx);
}

void Manager::addOrUpdate() {
    string id;
    cout << "Enter Order ID: ";
    getline(cin >> ws, id);

    BSTNode* found = bstFind(idIndex, id);
    if (found) {
        cout << "Order already exists. Updating not implemented for products yet.\n";
        return;
    }

    Node* x = new Node;
    x->order.id = id;

    cout << "Customer Name: ";
    getline(cin, x->order.customer);
    x->customer.name = x->order.customer;

    cout << "Customer ID: ";
    getline(cin, x->customer.customerID);

    cout << "Contact Number: ";
    getline(cin, x->customer.contactNumber);

    int nProd;
    cout << "How many products in this order? ";
    cin >> nProd;
    cin.ignore();

    x->order.total = 0;
    x->order.products = NULL;

    for (int i = 0; i < nProd; ++i) {
        Product p;
        cout << "\n--- Product " << (i + 1) << " ---\n";
        cout << "Product ID: ";
        getline(cin, p.productID);
        cout << "Product Name: ";
        getline(cin, p.name);
        cout << "Unit Price: ";
        cin >> p.unitPrice;
        cout << "Quantity: ";
        cin >> p.quantity;
        cin.ignore();

        addProductToOrder(x->order, p);
    }

    addLast(store, x);
    idIndex = bstInsertOrUpdate(idIndex, x->order.id, x);
    htAddRef(custIdx, x->order.customer, x);

    cout << "\nOrder added. Total = " << x->order.total << "\n";
}

void Manager::remove() {
    string id;
    cout << "Enter Order ID to remove: ";
    getline(cin >> ws, id);

    BSTNode* found = bstFind(idIndex, id);
    if (!found || !found->ref) {
        cout << "Order not found\n";
        return;
    }

    Node* target = found->ref;

    htRemoveRef(custIdx, target->order.customer, target);

    bool ok = false;
    idIndex = bstDelete(idIndex, id, ok);

    clearProducts(target->order.products);
    removeByPointer(store, target);

    cout << "Order removed successfully.\n";
}

void Manager::searchById() {
    string id;
    cout << "Enter Order ID: ";
    getline(cin >> ws, id);

    BSTNode* found = bstFind(idIndex, id);
    if (!found || !found->ref) {
        cout << "Order not found\n";
        return;
    }

    printHeader();
    printRow(found->ref);
    cout << "Products:\n";
    printProducts(found->ref->order.products);
}

void Manager::searchByCustomer() {
    string name;
    cout << "Enter Customer Name: ";
    getline(cin >> ws, name);

    HTEntry* e = htGetEntry(custIdx, name);
    if (!e || !e->refs) {
        cout << "No orders for this customer.\n";
        return;
    }

    cout << "Orders of " << name << ":\n";
    printHeader();
    HTRefNode* r = e->refs;
    while (r) {
        printRow(r->ref);
        r = r->next;
    }
}

void Manager::showAllSorted() {
    if (!idIndex) {
        cout << "No orders.\n";
        return;
    }
    cout << "\n--- All Orders (sorted by ID) ---\n";
    printHeader();
    bstInorder(idIndex);
}

void Manager::save(const string& path) {
    ofstream file(path);
    if (!file) {
        cout << "Cannot open file for writing.\n";
        return;
    }

    for (Node* p = store.first; p; p = p->next) {
        ProductNode* prod = p->order.products;
        if (!prod) {
            file << p->order.id << ","
                << p->order.customer << ","
                << p->customer.customerID << ","
                << p->customer.contactNumber << ","
                << "," << "," << 0 << "," << 0
                << "\n";
        }
        else {
            while (prod) {
                file << p->order.id << ","
                    << p->order.customer << ","
                    << p->customer.customerID << ","
                    << p->customer.contactNumber << ","
                    << prod->data.productID << ","
                    << prod->data.name << ","
                    << prod->data.unitPrice << ","
                    << prod->data.quantity
                    << "\n";
                prod = prod->next;
            }
        }
    }

    file.close();
    cout << "Saved to " << path << "\n";
}

void Manager::load(const string& path) {
    ifstream file(path);
    if (!file) {
        cout << "File not found: " << path << "\n";
        return;
    }

    initList(store);
    idIndex = NULL;
    htInit(custIdx);

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string token[8];
        size_t start = 0, pos;
        int idx = 0;
        while ((pos = line.find(',', start)) != string::npos && idx < 7) {
            token[idx++] = line.substr(start, pos - start);
            start = pos + 1;
        }
        token[idx] = line.substr(start);

        string orderID = token[0];
        string customerName = token[1];
        string customerID = token[2];
        string phone = token[3];
        string productID = token[4];
        string productName = token[5];
        double unitPrice = stod(token[6]);
        double quantity = stod(token[7]);

        BSTNode* found = bstFind(idIndex, orderID);
        Node* orderNode = NULL;

        if (!found) {
            orderNode = new Node;
            orderNode->order.id = orderID;
            orderNode->order.customer = customerName;
            orderNode->order.total = 0;
            orderNode->order.products = NULL;

            orderNode->customer.name = customerName;
            orderNode->customer.customerID = customerID;
            orderNode->customer.contactNumber = phone;

            addLast(store, orderNode);
            idIndex = bstInsertOrUpdate(idIndex, orderID, orderNode);
            htAddRef(custIdx, customerName, orderNode);
        }
        else {
            orderNode = found->ref;
        }

        if (!productID.empty()) {
            Product p;
            p.productID = productID;
            p.name = productName;
            p.unitPrice = unitPrice;
            p.quantity = quantity;
            addProductToOrder(orderNode->order, p);
        }
    }

    file.close();
    cout << "Loaded from " << path << "\n";
}
