#include "queue.h"
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    Queue A, B;

    createQueue(A);
    createQueue(B);

    long long terkirim = 0;
    long long totalTerkirim = 0;

    string line;

    cout << "SISTEM SORTIR DAN PENGIRIMAN PAKET\n";
    cout << "Perintah: MASUK, PINDAH, KIRIM, CARI, LIHAT, REKAP, BERSIHKAN, SELESAI\n";

    while (true) {
        cout << "\n> ";

        if (!getline(cin, line)) break;

        stringstream ss(line);
        string cmd;

        ss >> cmd;

        for (char& c : cmd)
            c = toupper((unsigned char)c);

        if (cmd.empty()) continue;

        if (cmd == "SELESAI") {
            delAll(A);
            delAll(B);

            cout << "Program selesai.\n";
            break;
        }

        else if (cmd == "MASUK") {
            string kode, extra;
            int berat;

            if (!(ss >> kode >> berat) || (ss >> extra)) {
                cout << "Format: MASUK kode berat\n";
                continue;
            }

            bool valid = !kode.empty() && kode.size() <= 10;

            if (!valid || berat < 1 || berat > 5000) {
                cout << "Data tidak valid.\n";
                continue;
            }

            if (findElm(A, kode) || findElm(B, kode)) {
                cout << "Ditolak: kode duplikat.\n";
                continue;
            }

            Paket* p = alokasi(kode, berat);

            if (p == nullptr) {
                cout << "Alokasi memori gagal.\n";
                continue;
            }

            enqueue(A, p);

            cout << "Berhasil: " << kode << " masuk A.\n";
        }

        else if (cmd == "PINDAH" || cmd == "KIRIM") {
            int n;
            string extra;

            if (!(ss >> n) || (ss >> extra)) {
                cout << "Masukkan jumlah paket.\n";
                continue;
            }

            Queue& sumber = (cmd == "PINDAH") ? A : B;

            if (n <= 0 || n > nbList(sumber)) {
                cout << "Ditolak: jumlah paket tidak valid.\n";
                continue;
            }

            for (int i = 0; i < n; i++) {
                Paket* p = dequeue(sumber);

                if (cmd == "PINDAH") {
                    enqueue(B, p);
                } else {
                    cout << "Terkirim: " << p->kode
                         << " - " << p->berat << " gram\n";

                    terkirim++;
                    totalTerkirim += p->berat;

                    dealokasi(p);
                }
            }

            cout << "Operasi berhasil.\n";
        }

        else if (cmd == "CARI") {
            string kode, extra;

            if (!(ss >> kode) || (ss >> extra)) {
                cout << "Format: CARI kode\n";
                continue;
            }

            char lokasi;
            int posisi;

            Paket* p = fFindElm(A, B, kode, lokasi, posisi);

            if (p != nullptr) {
                cout << "Ditemukan di " << lokasi
                     << ", posisi " << posisi
                     << ", berat " << p->berat << " gram.\n";
            } else {
                cout << "TIDAK DITEMUKAN\n";
            }
        }

        else if (cmd == "LIHAT") {
            cout << "A: ";
            printInfo(A);

            cout << "\nB: ";
            printInfo(B);

            cout << endl;
        }

        else if (cmd == "REKAP") {
            long long wa = 0, wb = 0;

            for (Paket* p = A.head; p; p = p->next)
                wa += p->berat;

            for (Paket* p = B.head; p; p = p->next)
                wb += p->berat;

            cout << "A: " << nbList(A) << " paket, "
                 << wa << " gram\n";

            cout << "B: " << nbList(B) << " paket, "
                 << wb << " gram\n";

            cout << "Terkirim: " << terkirim << " paket, "
                 << totalTerkirim << " gram\n";
        }

        else if (cmd == "BERSIHKAN") {
            delAll(A);
            delAll(B);

            cout << "Antrean berhasil dibersihkan.\n";
        }

        else {
            cout << "Perintah tidak dikenal.\n";
        }
    }

    return 0;
}