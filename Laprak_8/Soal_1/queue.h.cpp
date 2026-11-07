#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

struct Paket {
    string kode;
    int berat;
    Paket* next;
};

struct Queue {
    Paket* head;
    Paket* tail;
};

void createQueue(Queue& q);
bool isEmptyQueue(const Queue& q);
Paket* alokasi(const string& kode, int berat);
void dealokasi(Paket* p);
void enqueue(Queue& q, Paket* p);
Paket* dequeue(Queue& q);
Paket* findElm(const Queue& q, const string& kode);
Paket* fFindElm(const Queue& a, const Queue& b,
                const string& kode, char& lokasi, int& posisi);
int nbList(const Queue& q);
void printInfo(const Queue& q);
void delAll(Queue& q);

#endif