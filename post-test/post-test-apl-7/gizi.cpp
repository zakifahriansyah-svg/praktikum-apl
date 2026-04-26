#include "gizi.h"
#include <iomanip>
#include <cstdlib>
#include <stdexcept> 
#include <windows.h>  

const string LINE = "+----+----------------------+-----------------+---------------+-------------+-----------+-----------+\n";
const string HEAD = "| No | Nama Makanan         | Kategori        | Kalori (kkal) | Protein (g) | Karbo (g) | Lemak (g) |\n";

void animasiLoading() {
    cout << "Memproses data";
    for(int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << "\n";
}

void cetakBaris(int nomorUrut, DataGizi* gizi) {
    cout << "| " << left << setw(2) << nomorUrut << " | " << setw(20) << gizi->namaMakanan << " | " << setw(15) << gizi->kategori
         << " | " << setw(13) << gizi->nutrisi.kalori << " | " << setw(11) << gizi->nutrisi.protein
         << " | " << setw(9)  << gizi->nutrisi.karbohidrat << " | " << setw(9) << gizi->nutrisi.lemak << " |\n";
}

void cetakTabelGizi(DataGizi gizi[], int jumlahData) {
    cout << "\n===== DAFTAR DATA GIZI MAKANAN =====\n";
    cout << LINE << HEAD << LINE;
    bool ada = false; int nomorUrut = 1;
    for (int i = 0; i < jumlahData; i++)
        if (gizi[i].isConfirmed) { cetakBaris(nomorUrut++, &gizi[i]); ada = true; }
    if (!ada) cout << "| " << left << setw(97) << "Belum ada data." << " |\n";
    cout << LINE << "\n";
}

void cetakTabelGizi(DataGizi gizi[], int jumlahData, string kategoriCari) {
    cout << "\n===== HASIL FILTER KATEGORI: " << kategoriCari << " =====\n";
    cout << LINE << HEAD << LINE;
    bool ada = false; int nomorUrut = 1;
    for (int i = 0; i < jumlahData; i++)
        if (gizi[i].isConfirmed && gizi[i].kategori == kategoriCari) { cetakBaris(nomorUrut++, &gizi[i]); ada = true; }
    if (!ada) cout << "| " << left << setw(97) << "Data tidak ditemukan." << " |\n";
    cout << LINE << "\n";
}

void bubbleSortNamaDescending(DataGizi gizi[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (gizi[j].namaMakanan < gizi[j + 1].namaMakanan) swap(gizi[j], gizi[j + 1]);
}

void bubbleSortNamaAscending(DataGizi gizi[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (gizi[j].namaMakanan > gizi[j + 1].namaMakanan) swap(gizi[j], gizi[j + 1]);
}

void selectionSortKaloriAscending(DataGizi gizi[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (gizi[j].nutrisi.kalori < gizi[min_idx].nutrisi.kalori) min_idx = j;
        if (min_idx != i) swap(gizi[min_idx], gizi[i]);
    }
}

void insertionSortProteinDescending(DataGizi gizi[], int n) {
    for (int i = 1; i < n; i++) {
        DataGizi key = gizi[i]; int j = i - 1;
        while (j >= 0 && gizi[j].nutrisi.protein < key.nutrisi.protein) { gizi[j + 1] = gizi[j]; j = j - 1; }
        gizi[j + 1] = key;
    }
}

void menuSorting(DataGizi gizi[], int jumlahData) {
    int pil;
    do {
        system("cls");
        cout << "===== MENU URUTKAN DATA  =====\n";
        cout << "1. Nama Makanan (Z-A)\n2. Kalori (Rendah-Tinggi)\n3. Protein (Tinggi-Rendah)\n0. Batal\nPilihan: "; 
        
        try {
            if (!(cin >> pil)) throw invalid_argument("Input harus berupa ANGKA!");
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] EXCEPTION: " << e.what() << "\nTekan Enter..."; cin.get();
            pil = -1; continue;
        }

        if (pil == 1) {
            animasiLoading(); bubbleSortNamaDescending(gizi, jumlahData);
            cout << "\n[!] Data berhasil diurutkan Descending (Z-A)!\n";
        } else if (pil == 2) {
            animasiLoading(); selectionSortKaloriAscending(gizi, jumlahData);
            cout << "\n[!] Data berhasil diurutkan Kalori Ascending!\n";
        } else if (pil == 3) {
            animasiLoading(); insertionSortProteinDescending(gizi, jumlahData);
            cout << "\n[!] Data berhasil diurutkan Protein Descending!\n";
        } else if (pil != 0) {
            cout << "Pilihan tidak valid! Tekan Enter..."; cin.get();
        }
    } while (pil < 0 || pil > 3);
}

void binarySearchNama(DataGizi* gizi, int n, string target) {
    bubbleSortNamaAscending(gizi, n); 
    int low = 0, high = n - 1; bool found = false;
    cout << "\n===== HASIL PENCARIAN NAMA: " << target << " =====\n" << LINE << HEAD << LINE;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (gizi[mid].namaMakanan == target) {
            if (gizi[mid].isConfirmed) { cetakBaris(mid + 1, &gizi[mid]); found = true; }
            break;
        }
        if (gizi[mid].namaMakanan < target) low = mid + 1;
        else high = mid - 1;
    }
    if (!found) cout << "| " << left << setw(97) << "Data tidak ditemukan (Perhatikan Huruf Besar/Kecil)." << " |\n";
    cout << LINE << "\n";
}

void interpolationSearchKalori(DataGizi* gizi, int n, float target) {
    selectionSortKaloriAscending(gizi, n);
    int low = 0, high = n - 1; bool found = false;
    cout << "\n===== HASIL PENCARIAN KALORI: " << target << " kkal =====\n" << LINE << HEAD << LINE;
    while (low <= high && target >= gizi[low].nutrisi.kalori && target <= gizi[high].nutrisi.kalori) {
        if (low == high || gizi[low].nutrisi.kalori == gizi[high].nutrisi.kalori) {
            if (gizi[low].nutrisi.kalori == target && gizi[low].isConfirmed) { cetakBaris(low + 1, &gizi[low]); found = true; }
            break;
        }
        int pos = low + (((target - gizi[low].nutrisi.kalori) * (high - low)) / (gizi[high].nutrisi.kalori - gizi[low].nutrisi.kalori));
        if (gizi[pos].nutrisi.kalori == target) {
            if(gizi[pos].isConfirmed) { cetakBaris(pos + 1, &gizi[pos]); found = true; }
            break;
        }
        if (gizi[pos].nutrisi.kalori < target) low = pos + 1;
        else high = pos - 1;
    }
    if (!found) cout << "| " << left << setw(97) << "Data tidak ditemukan." << " |\n";
    cout << LINE << "\n";
}

void menuSearching(DataGizi* gizi, int jumlahData) {
    int pil;
    do {
        system("cls");
        cout << "===== MENU CARI DATA =====\n1. Cari berdasarkan Nama Makanan\n2. Cari berdasarkan Kalori\n0. Batal\nPilihan: ";
        
        try {
            if (!(cin >> pil)) throw invalid_argument("Input Pilihan harus berupa angka!");
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] ERROR: " << e.what() << "\nTekan Enter..."; cin.get(); 
            pil = -1;
            continue;
        }
        
        if (pil == 1) {
            string cariNama; cout << "Masukkan Nama Makanan (Contoh: Nasi Putih): "; getline(cin, cariNama);
            animasiLoading(); binarySearchNama(gizi, jumlahData, cariNama);
            cout << "Tekan Enter untuk melanjutkan..."; cin.get();
        } else if (pil == 2) {
            float cariKalori; cout << "Masukkan Kalori (Angka, contoh: 260): ";
            try {
                if (!(cin >> cariKalori)) throw invalid_argument("Kalori harus berupa angka desimal/bulat!");
                cin.ignore(1000, '\n');
                animasiLoading(); interpolationSearchKalori(gizi, jumlahData, cariKalori);
            } catch (const exception& e) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << "[!] ERROR: " << e.what() << "\n";
            }
            cout << "Tekan Enter untuk melanjutkan..."; cin.get();
        } else if (pil != 0) {
            cout << "\n[!] Pilihan tidak valid! Masukkan angka menu yang tersedia.\nTekan Enter...";
            cin.get();
        }
    } while (pil != 0);
}

float totalKaloriRekursif(DataGizi gizi[], int jumlahData) {
    if (jumlahData == 0) return 0;
    return (gizi[jumlahData-1].isConfirmed ? gizi[jumlahData-1].nutrisi.kalori : 0) + totalKaloriRekursif(gizi, jumlahData-1);
}

int cariIndex(DataGizi gizi[], int jumlahData, int pilihan, bool confirmed) {
    int currentNo = 1;
    for (int i = 0; i < jumlahData; i++) if (gizi[i].isConfirmed == confirmed && currentNo++ == pilihan) return i;
    return -1;
}

void tambahAtauRequestData(DataGizi gizi[], int& jumlahData, string peminta, bool isConfirmed) {
    if (jumlahData >= 100) { cout << "Kapasitas penuh!\n"; return; }
    cout << "--- " << (isConfirmed ? "TAMBAH DATA" : "REQUEST MAKANAN BARU") << " ---\n";
    cout << "Nama Makanan : "; getline(cin, gizi[jumlahData].namaMakanan);
    cout << "Kategori     : "; getline(cin, gizi[jumlahData].kategori);
    if (isConfirmed) {
        try {
            cout << "Kalori  : "; if(!(cin >> gizi[jumlahData].nutrisi.kalori)) throw invalid_argument("Format harus angka!");
            cout << "Protein : "; if(!(cin >> gizi[jumlahData].nutrisi.protein)) throw invalid_argument("Format harus angka!");
            cout << "Karbo   : "; if(!(cin >> gizi[jumlahData].nutrisi.karbohidrat)) throw invalid_argument("Format harus angka!");
            cout << "Lemak   : "; if(!(cin >> gizi[jumlahData].nutrisi.lemak)) throw invalid_argument("Format harus angka!");
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] BATAL: " << e.what() << " Data gizi gagal ditambahkan.\n"; return;
        }
    } else gizi[jumlahData].nutrisi = {0, 0, 0, 0};
    gizi[jumlahData].isConfirmed = isConfirmed; gizi[jumlahData].peminta = peminta; jumlahData++;
    cout << "\n" << (isConfirmed ? "Data berhasil ditambahkan!" : "Request terkirim ke Admin!") << "\n";
}

void ubahData(DataGizi gizi[], int jumlahData) {
    int pilihan;
    cout << "Nomor yang diubah: "; 
    try {
        if (!(cin >> pilihan)) throw runtime_error("Pilihan harus berupa nomor antrean (angka)!");
        cin.ignore(1000, '\n');
    } catch (const exception& e) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "[!] ERROR: " << e.what() << "\n"; return;
    }
    
    int targetIndex = cariIndex(gizi, jumlahData, pilihan, true);
    if (targetIndex == -1) { cout << "Nomor tidak valid!\n"; return; }
    
    cout << "Nama Baru    : "; getline(cin, gizi[targetIndex].namaMakanan);
    cout << "Kategori     : "; getline(cin, gizi[targetIndex].kategori);
    try {
        cout << "Kalori       : "; if(!(cin >> gizi[targetIndex].nutrisi.kalori)) throw invalid_argument("Error input angka!");
        cout << "Protein      : "; if(!(cin >> gizi[targetIndex].nutrisi.protein)) throw invalid_argument("Error input angka!");
        cout << "Karbo        : "; if(!(cin >> gizi[targetIndex].nutrisi.karbohidrat)) throw invalid_argument("Error input angka!");
        cout << "Lemak        : "; if(!(cin >> gizi[targetIndex].nutrisi.lemak)) throw invalid_argument("Error input angka!");
        cin.ignore(1000, '\n'); cout << "\nData berhasil diperbarui!\n";
    } catch (const exception& e) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "\n[!] BATAL MENGUBAH: " << e.what() << "\n";
    }
}

void hapusData(DataGizi gizi[], int& jumlahData) {
    int pilihan;
    cout << "Nomor yang dihapus: "; 
    try {
        if (!(cin >> pilihan)) throw runtime_error("Input nomor antrean harus berupa angka!");
        cin.ignore(1000, '\n');
    } catch (const exception& e) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "[!] ERROR: " << e.what() << "\n"; return;
    }

    int targetIndex = cariIndex(gizi, jumlahData, pilihan, true);
    if (targetIndex == -1) { cout << "Nomor tidak valid!\n"; return; }
    for (int i = targetIndex; i < jumlahData - 1; i++) gizi[i] = gizi[i + 1];
    jumlahData--; cout << "\nData berhasil dihapus!\n";
}

void konfirmasiRequest(DataGizi gizi[], int jumlahData) {
    const string LINE2 = "+----+----------------------+-----------------+-----------------+\n";
    cout << "===== REQUEST PENGGUNA =====\n" << LINE2;
    cout << "| No | Nama Makanan         | Kategori        | Peminta         |\n" << LINE2;
    bool ada = false; int nomorUrut = 1;
    for (int i = 0; i < jumlahData; i++)
        if (!gizi[i].isConfirmed) {
            cout << "| " << left << setw(2) << nomorUrut++ << " | " << setw(20) << gizi[i].namaMakanan
                 << " | " << setw(15) << gizi[i].kategori << " | " << setw(15) << gizi[i].peminta << " |\n";
            ada = true;
        }
    if (!ada) cout << "| " << left << setw(61) << "Tidak ada request." << " |\n";
    cout << LINE2 << "\n";
    if (!ada) return;
    
    int pilihan;
    cout << "Nomor Request (0=batal): "; 
    try {
        if (!(cin >> pilihan)) throw runtime_error("Nomor request tidak valid (harus angka)!");
        cin.ignore(1000, '\n');
    } catch (const exception& e) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "[!] ERROR: " << e.what() << "\n"; return;
    }
    
    if (pilihan <= 0) return;
    int targetIndex = cariIndex(gizi, jumlahData, pilihan, false);
    if (targetIndex == -1) { cout << "Nomor tidak valid!\n"; return; }
    
    cout << "\n--- LENGKAPI GIZI: " << gizi[targetIndex].namaMakanan << " ---\n";
    try {
        cout << "Kalori  : "; if(!(cin >> gizi[targetIndex].nutrisi.kalori)) throw invalid_argument("Format angka salah!");
        cout << "Protein : "; if(!(cin >> gizi[targetIndex].nutrisi.protein)) throw invalid_argument("Format angka salah!");
        cout << "Karbo   : "; if(!(cin >> gizi[targetIndex].nutrisi.karbohidrat)) throw invalid_argument("Format angka salah!");
        cout << "Lemak   : "; if(!(cin >> gizi[targetIndex].nutrisi.lemak)) throw invalid_argument("Format angka salah!");
        cin.ignore(1000, '\n'); gizi[targetIndex].isConfirmed = true;
        cout << "\nRequest dikonfirmasi!\n";
    } catch (const exception& e) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "\n[!] GAGAL KONFIRMASI: " << e.what() << "\n";
    }
}

void menuAdmin(DataGizi gizi[], int& jumlahData, string inputUsername) {
    string pilihanFilter; int menuPilihan;
    do {
        system("cls");
        cout << "===== DASHBOARD ADMIN =====\n1. Lihat Data\n2. Tambah Data\n3. Ubah Data\n4. Hapus Data\n5. Konfirmasi Request\n6. Urutkan Data\n7. Cari Data\n0. Logout\nPilihan: ";
        
        try {
            if (!(cin >> menuPilihan)) throw runtime_error("Input Menu tidak dikenali. Harap masukkan angka!");
            
            if (menuPilihan < 0 || menuPilihan > 7) throw out_of_range("Pilihan menu di luar jangkauan (0-7)!");
            
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] SYSTEM EXCEPTION: " << e.what() << "\nTekan Enter..."; cin.get();
            menuPilihan = -1; continue;
        }
        
        system("cls");
        if (menuPilihan == 1) {
            cetakTabelGizi(gizi, jumlahData); cout << "=> Total Kalori: " << totalKaloriRekursif(gizi, jumlahData) << " kkal\n\n";
            cout << "Filter Kategori? (y/n): "; cin >> pilihanFilter; cin.ignore(1000, '\n');
            if (pilihanFilter == "y" || pilihanFilter == "Y") {
                cout << "Kategori: "; string kategoriCari; getline(cin, kategoriCari);
                cetakTabelGizi(gizi, jumlahData, kategoriCari);
            }
        }
        else if (menuPilihan == 2) { cetakTabelGizi(gizi, jumlahData); tambahAtauRequestData(gizi, jumlahData, "Admin", true); }
        else if (menuPilihan == 3) { cetakTabelGizi(gizi, jumlahData); ubahData(gizi, jumlahData); }
        else if (menuPilihan == 4) { cetakTabelGizi(gizi, jumlahData); hapusData(gizi, jumlahData); }
        else if (menuPilihan == 5) konfirmasiRequest(gizi, jumlahData);
        else if (menuPilihan == 6) { menuSorting(gizi, jumlahData); if(menuPilihan != 0) cetakTabelGizi(gizi, jumlahData); }
        else if (menuPilihan == 7) menuSearching(gizi, jumlahData);
        
        if (menuPilihan != 0 && menuPilihan != 7) { cout << "\nTekan Enter Untuk Kembali..."; cin.get(); }
    } while (menuPilihan != 0);
}

void menuUser(DataGizi gizi[], int& jumlahData, string inputUsername) {
    int menuPilihan;
    do {
        system("cls");
        cout << "===== USER: " << inputUsername << " =====\n1. Lihat Data\n2. Request Makanan\n3. Urutkan Data\n4. Cari Data\n0. Logout\nPilihan: ";
        
        try {
            if (!(cin >> menuPilihan)) throw invalid_argument("Pilihan Menu harus berupa angka!");
            
            if (menuPilihan < 0 || menuPilihan > 4) throw out_of_range("Pilihan menu di luar jangkauan (0-4)!");
            
            cin.ignore(1000, '\n');
        } catch (const exception& e) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "\n[!] WARNING: " << e.what() << "\nTekan Enter..."; cin.get();
            menuPilihan = -1; continue;
        }
        
        system("cls");
        if (menuPilihan == 1)      cetakTabelGizi(gizi, jumlahData);
        else if (menuPilihan == 2) tambahAtauRequestData(gizi, jumlahData, inputUsername, false);
        else if (menuPilihan == 3) { menuSorting(gizi, jumlahData); if(menuPilihan != 0) cetakTabelGizi(gizi, jumlahData); }
        else if (menuPilihan == 4) menuSearching(gizi, jumlahData);
        
        if (menuPilihan != 0 && menuPilihan != 4) { cout << "\nTekan Enter Untuk Kembali..."; cin.get(); }
    } while (menuPilihan != 0);
}

void menuLogin(DataGizi gizi[], int& jumlahData, AkunUser users[], int jumlahUser) {
    int percobaan = 0, role = 0; bool loginBerhasil = false; string inputUsername, inputPassword;
    while (percobaan < 3 && !loginBerhasil) {
        system("cls"); cout << "=== MENU LOGIN ===\n";
        if (percobaan > 0) cout << "[!] Gagal. Sisa: " << 3 - percobaan << "\n";
        cout << "Username: "; cin >> inputUsername; cout << "Password: "; cin >> inputPassword;
        if (inputUsername == "zaki" && inputPassword == "020") { loginBerhasil = true; role = 1; }
        else for (int i = 0; i < jumlahUser; i++)
            if (users[i].username == inputUsername && users[i].password == inputPassword) { loginBerhasil = true; role = 2; break; }
        if (!loginBerhasil && ++percobaan == 3) { system("cls"); cout << "[!] Gagal 3 kali. Program dihentikan.\n"; exit(0); }
    }
    animasiLoading(); cout << "\nSelamat datang, " << inputUsername << "!\nTekan Enter Untuk Kembali..."; cin.ignore(1000, '\n'); cin.get();
    if (role == 1) menuAdmin(gizi, jumlahData, inputUsername); else menuUser(gizi, jumlahData, inputUsername);
}

void menuRegister(AkunUser users[], int& jumlahUser) {
    system("cls"); string inputBaru; bool isDuplicate;
    if (jumlahUser >= 100) cout << "Kapasitas penuh!\n";
    else {
        cout << "===== REGISTER USER =====\n";
        do {
            isDuplicate = false; cout << "Username: "; cin >> inputBaru;
            if (inputBaru == "zaki") isDuplicate = true;
            for (int i = 0; i < jumlahUser; i++) if (users[i].username == inputBaru) isDuplicate = true;
            if (isDuplicate) cout << "[!] Username sudah dipakai!\n";
        } while (isDuplicate);
        users[jumlahUser].username = inputBaru; cout << "Password: "; cin >> users[jumlahUser].password;
        jumlahUser++; animasiLoading(); cout << "\nRegistrasi berhasil!\n";
    }
    cout << "Tekan Enter Untuk Kembali..."; cin.ignore(1000, '\n'); cin.get();
}