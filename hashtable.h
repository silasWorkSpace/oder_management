#pragma once
#include "structs.h"

unsigned htHash(const string& s);
void htInit(HashTable& T);
void htAddRef(HashTable& T, const string& name, Node* ref);
bool htRemoveRef(HashTable& T, const string& name, Node* ref);
HTEntry* htGetEntry(HashTable& T, const string& name);
void htClear(HashTable& T);
