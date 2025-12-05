#include "list.h"
#include <iomanip>

void initList(List& L) {
    L.first = L.last = NULL;
}

void addLast(List& L, Node* x) {
    if (!x) return;
    x->next = NULL;
    if (L.first == NULL) L.first = L.last = x;
    else {
        L.last->next = x;
        L.last = x;
    }
}

bool removeByPointer(List& L, Node* target) {
    if (!L.first || !target) return false;

    if (L.first == target) {
        L.first = target->next;
        if (L.last == target) L.last = NULL;
        delete target;
        return true;
    }

    Node* p = L.first;
    while (p->next && p->next != target)
        p = p->next;

    if (!p->next) return false;

    p->next = target->next;
    if (L.last == target)
        L.last = p;

    delete target;
    return true;
}

int countProducts(ProductNode* head) {
    int c = 0;
    while (head) {
        ++c;
        head = head->next;
    }
    return c;
}

void printProducts(ProductNode* head) {
    while (head) {
        cout << "    - "
            << head->data.productID << " | "
            << head->data.name << " | "
            << fixed << setprecision(2) << head->data.unitPrice
            << " x " << fixed << setprecision(2) << head->data.quantity
            << "\n";
        head = head->next;
    }
}

void printHeader() {
    cout << left << setw(12) << "OrderID"
        << left << setw(20) << "Customer"
        << left << setw(10) << "Total"
        << left << setw(14) << "CustID"
        << left << setw(14) << "Phone"
        << left << setw(10) << "#Prod"
        << "\n";
    cout << string(80, '-') << "\n";
}

void printRow(Node* p) {
    int prodCount = countProducts(p->order.products);
    cout << left << setw(12) << p->order.id
        << left << setw(20) << p->order.customer
        << left << setw(10) << fixed << setprecision(2) << p->order.total
        << left << setw(14) << p->customer.customerID
        << left << setw(14) << p->customer.contactNumber
        << left << setw(10) << prodCount
        << "\n";
}
