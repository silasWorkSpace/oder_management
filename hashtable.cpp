#include "hashtable.h"

unsigned htHash(const string& s) {
    unsigned long h = 0;
    for (char c : s)
        h = h * 31 + (unsigned char)c;
    return (unsigned)(h % HASH_SIZE);
}

void htInit(HashTable& T) {
    for (int i = 0; i < HASH_SIZE; ++i)
        T.bucket[i] = NULL;
}

void htAddRef(HashTable& T, const string& name, Node* ref) {
    unsigned idx = htHash(name);
    HTEntry* p = T.bucket[idx];

    while (p) {
        if (p->name == name) {
            HTRefNode* r = new HTRefNode;
            r->ref = ref;
            r->next = p->refs;
            p->refs = r;
            return;
        }
        p = p->next;
    }

    HTEntry* e = new HTEntry;
    e->name = name;
    e->next = T.bucket[idx];
    e->refs = NULL;
    T.bucket[idx] = e;

    HTRefNode* r = new HTRefNode;
    r->ref = ref;
    r->next = NULL;
    e->refs = r;
}

bool htRemoveRef(HashTable& T, const string& name, Node* ref) {
    unsigned idx = htHash(name);
    HTEntry* p = T.bucket[idx];
    HTEntry* prev = NULL;

    while (p) {
        if (p->name == name) {
            HTRefNode* q = p->refs;
            HTRefNode* qprev = NULL;
            while (q) {
                if (q->ref == ref) {
                    if (qprev) qprev->next = q->next;
                    else p->refs = q->next;
                    delete q;
                    return true;
                }
                qprev = q;
                q = q->next;
            }
        }
        prev = p;
        p = p->next;
    }
    return false;
}

HTEntry* htGetEntry(HashTable& T, const string& name) {
    unsigned idx = htHash(name);
    HTEntry* p = T.bucket[idx];
    while (p) {
        if (p->name == name)
            return p;
        p = p->next;
    }
    return NULL;
}

void htClear(HashTable& T) {
    for (int i = 0; i < HASH_SIZE; ++i) {
        HTEntry* p = T.bucket[i];
        while (p) {
            HTEntry* next = p->next;
            HTRefNode* r = p->refs;
            while (r) {
                HTRefNode* rn = r->next;
                delete r;
                r = rn;
            }
            delete p;
            p = next;
        }
        T.bucket[i] = NULL;
    }
}
