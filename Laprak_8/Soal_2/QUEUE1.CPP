#include "queue.h"
#include <iostream>

void createQueue(Queue& q) {
    q.head = q.tail = -1;
    q.pergeseran = 0;
}

int sizeQueue(const Queue& q) {
    return q.head == -1 ? 0 : q.tail - q.head + 1;
}

int freeSpace(const Queue& q) {
    return 6 - sizeQueue(q);
}

bool enqueue(Queue& q, Record r) {
    if (freeSpace(q) == 0) return false;

    if (q.head == -1)
        q.head = q.tail = 0;
    else
        ++q.tail;

    q.data[q.tail] = r;
    return true;
}

bool dequeue(Queue& q, Record& r) {
    if (q.head == -1) return false;

    r = q.data[q.head];

    int n = sizeQueue(q) - 1;

    for (int i = 0; i < n; i++) {
        q.data[i] = q.data[i + 1];
        q.pergeseran++;
    }

    if (n == 0) {
        q.head = q.tail = -1;
    } else {
        q.head = 0;
        q.tail = n - 1;
    }

    return true;
}

Record atQueue(const Queue& q, int i) {
    return q.data[q.head + i];
}

void printPhysical(const Queue& q) {
    for (int i = 0; i < 6; i++) {
        std::cout << i << ": ";

        if (q.head != -1 && i >= q.head && i <= q.tail)
            std::cout << q.data[i].nomor << ":" << q.data[i].nilai;
        else
            std::cout << "-";

        std::cout << "  ";
    }

    std::cout << "\nhead=" << q.head
              << " tail=" << q.tail << "\n";
}

void clearQueue(Queue& q) {
    q.head = q.tail = -1;
}