#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "gizi.h"

using namespace std;

int main() {
    DataGizi gizi[100]; int jumlahData = 0;
    AkunUser users[100]; int jumlahUser = 0;
    
    gizi[0] = {"Nasi Putih", "Makanan Utama", {130.0, 2.7, 28.2, 0.3}, true, "Admin"};
    gizi[1] = {"Ayam Goreng", "Lauk Pauk",   {260.0, 27.3, 1.8, 16.8}, true, "Admin"};
    gizi[2] = {"Sate Ayam", "Lauk Pauk",     {200.0, 20.0, 15.0, 10.0}, true, "Admin"};
    gizi[3] = {"Rendang Daging", "Lauk Pauk",{468.0, 47.0, 10.5, 30.0}, true, "Admin"};
    gizi[4] = {"Sayur Bayam", "Sayuran",     {23.0, 2.9, 3.6, 0.4}, true, "Admin"};
    jumlahData = 5;

    int menuAwal;
    do {
        system("cls");
        cout << "========================================\n";
        cout << " SISTEM INFORMASI MANAJEMEN DATA GIZI\n";
        cout << "========================================\n";
        cout << "1. Login\n2. Register\n0. Keluar\nPilihan: "; 
        
        try {
            if (!(cin >> menuAwal)) throw runtime_error("Pilihan menu harus menggunakan angka!");
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] FATAL ERROR: " << e.what() << "\nTekan Enter untuk mencoba lagi...";
            cin.get();
            menuAwal = -1;
            continue; 
        }

        if      (menuAwal == 1)  menuLogin(gizi, jumlahData, users, jumlahUser);
        else if (menuAwal == 2)  menuRegister(users, jumlahUser);
        else if (menuAwal != 0) {
            cout << "\n[!] Pilihan tidak valid!\nTekan Enter Untuk Kembali...";
            cin.get();
        }
    } while (menuAwal != 0);

    system("cls");
    cout << "\nTerima kasih telah menggunakan Sistem Informasi Manajemen Data Gizi!\n";
    return 0;
}