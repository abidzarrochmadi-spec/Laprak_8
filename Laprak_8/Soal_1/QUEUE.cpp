#include "queue.h"
#include <iostream>
#include <new>

void createQueue(Queue& q) {
    q.head = nullptr;
    q.tail = nullptr;
}

bool isEmptyQueue(const Queue& q) {
    return q.head == nullptr;
}

Paket* alokasi(const string& kode, int berat) {
    return new(nothrow) Paket{kode, berat, nullptr};
}

void dealokasi(Paket* p) {
    delete p;
}

void enqueue(Queue& q, Paket* p) {
    if (p == nullptr) return;

    p->next = nullptr;

    if (isEmptyQueue(q)) {
        q.head = q.tail = p;
    } else {
        q.tail->next = p;
        q.tail = p;
    }
}

Paket* dequeue(Queue& q) {
    if (isEmptyQueue(q)) return nullptr;

    Paket* p = q.head;
    q.head = q.head->next;

    if (q.head == nullptr) {
        q.tail = nullptr;
    }

    p->next = nullptr;
    return p;
}

Paket* findElm(const Queue& q, const string& kode) {
    Paket* p = q.head;

    while (p != nullptr) {
        if (p->kode == kode) return p;
        p = p->next;
    }

    return nullptr;
}

Paket* fFindElm(const Queue& a, const Queue& b,
                const string& kode, char& lokasi, int& posisi) {
    int i = 1;

    for (Paket* p = a.head; p != nullptr; p = p->next, i++) {
        if (p->kode == kode) {
            lokasi = 'A';
            posisi = i;
            return p;
        }
    }

    i = 1;

    for (Paket* p = b.head; p != nullptr; p = p->next, i++) {
        if (p->kode == kode) {
            lokasi = 'B';
            posisi = i;
            return p;
        }
    }

    lokasi = '-';
    posisi = 0;
    return nullptr;
}

int nbList(const Queue& q) {
    int n = 0;

    for (Paket* p = q.head; p != nullptr; p = p->next) {
        n++;
    }

    return n;
}

void printInfo(const Queue& q) {
    if (isEmptyQueue(q)) {
        cout << "Kosong";
        return;
    }

    for (Paket* p = q.head; p != nullptr; p = p->next) {
        cout << p->kode << "(" << p->berat << "g)";

        if (p->next != nullptr) {
            cout << " -> ";
        }
    }
}

void delAll(Queue& q) {
    while (!isEmptyQueue(q)) {
        Paket* p = dequeue(q);
        dealokasi(p);
    }
}