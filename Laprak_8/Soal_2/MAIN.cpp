#include "queue.h"
#include <iostream>
#include <sstream>
#include <climits>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    Queue q;
    createQueue(q);

    int nextNo = 1;
    string line;

    cout << "BUFFER HASIL UKUR (kapasitas 6)\n";
    cout << "Perintah: TULIS, AMBIL, LIHAT, RINGKAS, KOSONGKAN, SELESAI\n";

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
            cout << "Program selesai.\n";
            break;
        }

        else if (cmd == "TULIS") {
            int k;

            if (!(ss >> k) || k < 1 || k > 6) {
                cout << "Ditolak: k harus 1-6.\n";
                continue;
            }

            int vals[6];
            int x;
            bool valid = true;
            int got = 0;

            for (int i = 0; i < k; i++) {
                if (!(ss >> x)) {
                    valid = false;
                    break;
                }

                vals[got++] = x;

                if (x < -1000 || x > 1000)
                    valid = false;
            }

            string extra;

            if (ss >> extra)
                valid = false;

            if (!valid) {
                cout << "Ditolak: nilai harus -1000 sampai 1000 "
                     << "dan jumlah nilai harus tepat k.\n";
                continue;
            }

            if (freeSpace(q) < k) {
                cout << "Ditolak: ruang kosong hanya "
                     << freeSpace(q) << ".\n";
                continue;
            }

            for (int i = 0; i < got; i++) {
                enqueue(q, {nextNo++, vals[i]});
            }

            cout << "Berhasil menambahkan "
                 << k << " rekaman.\n";
        }

        else if (cmd == "AMBIL") {
            int k;
            string extra;

            if (!(ss >> k) || (ss >> extra) ||
                k <= 0 || k > 6 || k > sizeQueue(q)) {

                cout << "Ditolak: jumlah data tidak valid. "
                     << "Data tersedia: " << sizeQueue(q) << ".\n";
                continue;
            }

            for (int i = 0; i < k; i++) {
                Record r;

                dequeue(q, r);

                cout << "Keluar: "
                     << r.nomor << ":"
                     << r.nilai << "\n";
            }
        }

        else if (cmd == "LIHAT") {
            cout << "FIFO: ";

            if (sizeQueue(q) == 0)
                cout << "Kosong";

            for (int i = 0; i < sizeQueue(q); i++) {
                Record r = atQueue(q, i);

                cout << r.nomor << ":" << r.nilai;

                if (i + 1 < sizeQueue(q))
                    cout << ", ";
            }

            cout << "\nFisik: ";

            printPhysical(q);
        }

        else if (cmd == "RINGKAS") {
            int n = sizeQueue(q);

            long long total = 0;
            int mn = INT_MAX;
            int mx = INT_MIN;

            for (int i = 0; i < n; i++) {
                int v = atQueue(q, i).nilai;

                total += v;

                if (v < mn) mn = v;
                if (v > mx) mx = v;
            }

            cout << "Jumlah: " << n << "\n";
            cout << "Total: " << total << "\n";

            if (n == 0) {
                cout << "Minimum: TIDAK ADA\n";
                cout << "Maksimum: TIDAK ADA\n";
                cout << "Rata-rata: TIDAK ADA\n";
            } else {
                cout << "Minimum: " << mn << "\n";
                cout << "Maksimum: " << mx << "\n";

                cout << "Rata-rata: "
                     << fixed << setprecision(2)
                     << (double)total / n << "\n";
            }
        }

        else if (cmd == "KOSONGKAN") {
            clearQueue(q);

            cout << "Buffer berhasil dikosongkan.\n";
        }

        else {
            cout << "Perintah tidak dikenal.\n";
        }
    }

    cout << "\nTotal pergeseran: "
         << q.pergeseran << " rekaman\n";

    return 0;
}