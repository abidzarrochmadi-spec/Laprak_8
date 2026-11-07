#include "queue.h"
#include <iostream>

void createQueue(Queue& q) {
    q.head = 0;
    q.count = 0;
    q.pergeseran = 0;
}

int sizeQueue(const Queue& q) {
    return q.count;
}

int freeSpace(const Queue& q) {
    return 6 - q.count;
}

bool enqueue(Queue& q, Record r) {
    if (q.count == 6) return false;

    int idx = (q.head + q.count) % 6;

    q.data[idx] = r;
    q.count++;

    return true;
}

bool dequeue(Queue& q, Record& r) {
    if (q.count == 0) return false;

    r = q.data[q.head];

    q.head = (q.head + 1) % 6;
    q.count--;

    if (q.count == 0)
        q.head = 0;

    return true;
}

Record atQueue(const Queue& q, int i) {
    return q.data[(q.head + i) % 6];
}

void printPhysical(const Queue& q) {
    for (int i = 0; i < 6; i++) {
        bool active = false;

        for (int j = 0; j < q.count; j++) {
            if ((q.head + j) % 6 == i)
                active = true;
        }

        std::cout << i << ": ";

        if (active)
            std::cout << q.data[i].nomor << ":" << q.data[i].nilai;
        else
            std::cout << "-";

        std::cout << "  ";
    }

    std::cout << "\nhead=" << q.head
              << " count=" << q.count << "\n";
}

void clearQueue(Queue& q) {
    q.head = 0;
    q.count = 0;
}