#ifndef QUEUE_H
#define QUEUE_H

struct Record {
    int nomor;
    int nilai;
};

struct Queue {
    Record data[6];
    int head, count;
    long long pergeseran;
};

void createQueue(Queue&);
int sizeQueue(const Queue&);
int freeSpace(const Queue&);
bool enqueue(Queue&, Record);
bool dequeue(Queue&, Record&);
Record atQueue(const Queue&, int);
void printPhysical(const Queue&);
void clearQueue(Queue&);

#endif