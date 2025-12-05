#pragma once
#include "structs.h"
#include <iostream>
using namespace std;

void initList(List& L);
void addLast(List& L, Node* x);
bool removeByPointer(List& L, Node* target);

void printHeader();
void printRow(Node* p);

// Cho phần hiển thị chi tiết product
int countProducts(ProductNode* head);
void printProducts(ProductNode* head);
