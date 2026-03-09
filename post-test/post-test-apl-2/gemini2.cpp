/*
 * SISTEM INFORMASI MANAJEMEN DATA GIZI
 * Algoritma Pemrograman Lanjut 2025 - Informatika Unmul
 *
 * Posttest:
 *   [v] Sistem Login  : username (Nama) + password (NIM), maks 3x, pakai struct
 *   [v] Menu Utama    : looping hingga pilih Keluar
 *   [v] CRUD          : Tambah, Lihat, Ubah, Hapus data
 *   [v] Array of Struct untuk menyimpan data CRUD
 *   [v] POIN+ Tabel   : data ditampilkan dalam format tabel
 *   [v] POIN+ Nested Struct : InfoNutrisi di dalam DataMakanan
 *   [v] POIN+ Multiuser     : Register & Login, peran admin/user
 *
 * Modul 1 & 2 only:
 *   - Tipe data : int, float, bool, char, string
 *   - Kolektif  : array 1D, array of struct
 *   - Struct, nested struct
 *   - Percabangan: if / else if / else
 *   - Perulangan : while, for
 *   - I/O        : cout, cin, getline
 *   - #include <iomanip> untuk setw/left (format tabel)
 *   - #include <cstdlib> untuk system("cls")
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

// ===== KONSTANTA =====
const int MAKS_MAKANAN  = 50;
const int MAKS_PENGGUNA = 20;
const int MAKS_REQUEST  = 30;

// ===== STRUCT =====

struct InfoNutrisi {          // << NESTED STRUCT (dipakai di dalam DataMakanan)
    float kalori;
    float protein;
    float karbohidrat;
    float lemak;
    float serat;
};

struct DataMakanan {
    string nama_makanan;
    string kategori;
    InfoNutrisi nutrisi;      // << penggunaan nested struct
};

struct DataPengguna {
    string nama_pengguna;
    string nim_pengguna;
    string peran_pengguna;
};

struct RequestMakanan {
    string nama_makanan_diminta;
    string catatan_request;
    string nama_peminta;
    bool   sudah_dikonfirmasi;
};

// ===== VARIABEL GLOBAL =====

DataMakanan    daftar_makanan[MAKS_MAKANAN];    // array of struct
DataPengguna   daftar_pengguna[MAKS_PENGGUNA];  // array of struct
RequestMakanan daftar_request[MAKS_REQUEST];    // array of struct
DataPengguna   pengguna_aktif;

int jumlah_makanan  = 0;
int jumlah_pengguna = 0;
int jumlah_request  = 0;

// =============================================================
// MAIN
// =============================================================
int main() {

    // ===== INISIALISASI DATA AWAL =====

    daftar_pengguna[0].nama_pengguna  = "admin";
    daftar_pengguna[0].nim_pengguna   = "0000";
    daftar_pengguna[0].peran_pengguna = "admin";
    jumlah_pengguna = 1;

    daftar_makanan[0].nama_makanan        = "Nasi Putih";
    daftar_makanan[0].kategori            = "Makanan Pokok";
    daftar_makanan[0].nutrisi.kalori      = 130.0;
    daftar_makanan[0].nutrisi.protein     = 2.7;
    daftar_makanan[0].nutrisi.karbohidrat = 28.2;
    daftar_makanan[0].nutrisi.lemak       = 0.3;
    daftar_makanan[0].nutrisi.serat       = 0.4;

    daftar_makanan[1].nama_makanan        = "Ayam Goreng";
    daftar_makanan[1].kategori            = "Lauk Pauk";
    daftar_makanan[1].nutrisi.kalori      = 260.0;
    daftar_makanan[1].nutrisi.protein     = 27.3;
    daftar_makanan[1].nutrisi.karbohidrat = 1.8;
    daftar_makanan[1].nutrisi.lemak       = 16.8;
    daftar_makanan[1].nutrisi.serat       = 0.0;

    daftar_makanan[2].nama_makanan        = "Bayam Rebus";
    daftar_makanan[2].kategori            = "Sayuran";
    daftar_makanan[2].nutrisi.kalori      = 23.0;
    daftar_makanan[2].nutrisi.protein     = 2.9;
    daftar_makanan[2].nutrisi.karbohidrat = 3.6;
    daftar_makanan[2].nutrisi.lemak       = 0.4;
    daftar_makanan[2].nutrisi.serat       = 2.2;

    daftar_makanan[3].nama_makanan        = "Telur Rebus";
    daftar_makanan[3].kategori            = "Lauk Pauk";
    daftar_makanan[3].nutrisi.kalori      = 155.0;
    daftar_makanan[3].nutrisi.protein     = 13.0;
    daftar_makanan[3].nutrisi.karbohidrat = 1.1;
    daftar_makanan[3].nutrisi.lemak       = 10.6;
    daftar_makanan[3].nutrisi.serat       = 0.0;
    jumlah_makanan = 4;

    // ===================================================
    // MENU UTAMA  (loop hingga pilih 0 = Keluar)
    // ===================================================
    int  pilihan;
    bool berjalan = true;

    while (berjalan) {

        system("cls");
        cout << "==================================================" << endl;
        cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
        cout << "       Algoritma Pemrograman Lanjut 2025         " << endl;
        cout << "==================================================" << endl;
        cout << "  >> SELAMAT DATANG" << endl;
        cout << "==================================================" << endl;
        cout << "  1. Login" << endl;
        cout << "  2. Register" << endl;
        cout << "  0. Keluar" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "  Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        // ===================================================
        // PILIHAN 1 : LOGIN
        // ===================================================
        if (pilihan == 1) {

            bool login_berhasil = false;
            int  percobaan      = 0;

            // Maks 3 kali percobaan login
            while (percobaan < 3 && !login_berhasil) {

                string nama, nim;
                system("cls");
                cout << "==================================================" << endl;
                cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
                cout << "==================================================" << endl;
                cout << "  >> LOGIN  (Percobaan " << percobaan + 1 << " dari 3)" << endl;
                cout << "==================================================" << endl;
                cout << "  Nama (username) : ";
                getline(cin, nama);
                cout << "  NIM  (password) : ";
                getline(cin, nim);

                for (int i = 0; i < jumlah_pengguna; i++) {
                    if (daftar_pengguna[i].nama_pengguna == nama &&
                        daftar_pengguna[i].nim_pengguna  == nim) {
                        pengguna_aktif = daftar_pengguna[i];
                        login_berhasil = true;
                    }
                }

                if (!login_berhasil) {
                    percobaan++;
                    if (percobaan < 3) {
                        cout << "\n  [!] Nama atau NIM salah, coba lagi." << endl;
                        cout << "  Tekan Enter untuk melanjutkan...";
                        cin.get();
                    } else {
                        cout << "\n  [X] Gagal login 3 kali. Kembali ke menu utama." << endl;
                        cout << "  Tekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                }
            }

            if (login_berhasil) {
                cout << "\n  [+] Selamat datang, " << pengguna_aktif.nama_pengguna
                     << "! (" << pengguna_aktif.peran_pengguna << ")" << endl;
                cout << "  Tekan Enter untuk melanjutkan...";
                cin.get();

                // ===================================================
                // MENU ADMIN
                // ===================================================
                if (pengguna_aktif.peran_pengguna == "admin") {

                    int  p_admin;
                    bool admin_aktif = true;

                    while (admin_aktif) {

                        system("cls");
                        cout << "==================================================" << endl;
                        cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
                        cout << "==================================================" << endl;
                        cout << "  >> MENU ADMIN  |  User: " << pengguna_aktif.nama_pengguna << endl;
                        cout << "==================================================" << endl;
                        cout << "  1. Lihat  Data Makanan" << endl;
                        cout << "  2. Tambah Data Makanan" << endl;
                        cout << "  3. Ubah   Data Makanan" << endl;
                        cout << "  4. Hapus  Data Makanan" << endl;
                        cout << "  5. Kelola Request Pengguna" << endl;
                        cout << "  0. Logout" << endl;
                        cout << "--------------------------------------------------" << endl;
                        cout << "  Pilihan: ";
                        cin >> p_admin;
                        cin.ignore();

                        // -----------------------------------------------
                        // ADMIN 1 : LIHAT DATA MAKANAN (TABEL PENUH)
                        // -----------------------------------------------
                        if (p_admin == 1) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> DATA MAKANAN & INFORMASI GIZI" << endl;
                            cout << "     (* Nilai nutrisi per 100 gram)" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_makanan == 0) {
                                cout << "  Belum ada data makanan." << endl;
                            } else {
                                string g = "+-----+----------------------+----------------+----------+----------+----------+----------+---------+";
                                cout << g << endl;
                                cout << "| "
                                     << left << setw(3)  << "No"        << " | "
                                     << setw(20) << "Nama Makanan"      << " | "
                                     << setw(14) << "Kategori"          << " | "
                                     << setw(8)  << "Kalori"            << " | "
                                     << setw(8)  << "Protein"           << " | "
                                     << setw(8)  << "Karbo"             << " | "
                                     << setw(8)  << "Lemak"             << " | "
                                     << setw(7)  << "Serat"             << " |" << endl;
                                cout << "| "
                                     << setw(3)  << ""   << " | "
                                     << setw(20) << ""   << " | "
                                     << setw(14) << ""   << " | "
                                     << setw(8)  << "(kkal)" << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(7)  << "(gr)"   << " |" << endl;
                                cout << g << endl;

                                cout << fixed << setprecision(1);
                                for (int i = 0; i < jumlah_makanan; i++) {
                                    cout << "| "
                                         << left << setw(3)  << i + 1                                  << " | "
                                         << setw(20) << daftar_makanan[i].nama_makanan                 << " | "
                                         << setw(14) << daftar_makanan[i].kategori                     << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.kalori               << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.protein              << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.karbohidrat          << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.lemak                << " | "
                                         << setw(7)  << daftar_makanan[i].nutrisi.serat                << " |" << endl;
                                }
                                cout << g << endl;
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // ADMIN 2 : TAMBAH DATA MAKANAN
                        // -----------------------------------------------
                        else if (p_admin == 2) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> TAMBAH DATA MAKANAN" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_makanan >= MAKS_MAKANAN) {
                                cout << "  [!] Kapasitas makanan sudah penuh!" << endl;
                            } else {
                                DataMakanan baru;
                                cout << "  Nama Makanan : ";
                                getline(cin, baru.nama_makanan);
                                cout << "  Kategori     : ";
                                getline(cin, baru.kategori);
                                cout << "\n  -- Nutrisi per 100 gram --" << endl;
                                cout << "  Kalori      (kkal) : "; cin >> baru.nutrisi.kalori;
                                cout << "  Protein     (gr)   : "; cin >> baru.nutrisi.protein;
                                cout << "  Karbohidrat (gr)   : "; cin >> baru.nutrisi.karbohidrat;
                                cout << "  Lemak       (gr)   : "; cin >> baru.nutrisi.lemak;
                                cout << "  Serat       (gr)   : "; cin >> baru.nutrisi.serat;
                                cin.ignore();

                                daftar_makanan[jumlah_makanan] = baru;
                                jumlah_makanan++;
                                cout << "\n  [+] Data berhasil ditambahkan!" << endl;
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // ADMIN 3 : UBAH DATA MAKANAN
                        // -----------------------------------------------
                        else if (p_admin == 3) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> UBAH DATA MAKANAN" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_makanan == 0) {
                                cout << "  Belum ada data makanan." << endl;
                            } else {
                                // Tabel ringkas: No | Nama | Kategori
                                string g2 = "+-----+----------------------+----------------+";
                                cout << g2 << endl;
                                cout << "| " << left << setw(3) << "No" << " | "
                                     << setw(20) << "Nama Makanan"       << " | "
                                     << setw(14) << "Kategori"           << " |" << endl;
                                cout << g2 << endl;
                                for (int i = 0; i < jumlah_makanan; i++) {
                                    cout << "| " << left << setw(3) << i + 1                        << " | "
                                         << setw(20) << daftar_makanan[i].nama_makanan              << " | "
                                         << setw(14) << daftar_makanan[i].kategori                  << " |" << endl;
                                }
                                cout << g2 << endl;

                                int nomor;
                                cout << "\n  Nomor yang diubah: ";
                                cin >> nomor;
                                cin.ignore();

                                if (nomor >= 1 && nomor <= jumlah_makanan) {
                                    string input;
                                    float  val;

                                    cout << "\n  Nama baru     [" << daftar_makanan[nomor-1].nama_makanan << "] (Enter = skip): ";
                                    getline(cin, input);
                                    if (input != "") daftar_makanan[nomor-1].nama_makanan = input;

                                    cout << "  Kategori baru [" << daftar_makanan[nomor-1].kategori << "] (Enter = skip): ";
                                    getline(cin, input);
                                    if (input != "") daftar_makanan[nomor-1].kategori = input;

                                    cout << "\n  Nutrisi baru (isi 0 atau kurang = lewati):" << endl;
                                    cout << fixed << setprecision(1);

                                    cout << "  Kalori      [" << daftar_makanan[nomor-1].nutrisi.kalori      << "] : "; cin >> val;
                                    if (val > 0) daftar_makanan[nomor-1].nutrisi.kalori = val;

                                    cout << "  Protein     [" << daftar_makanan[nomor-1].nutrisi.protein     << "] : "; cin >> val;
                                    if (val > 0) daftar_makanan[nomor-1].nutrisi.protein = val;

                                    cout << "  Karbohidrat [" << daftar_makanan[nomor-1].nutrisi.karbohidrat << "] : "; cin >> val;
                                    if (val > 0) daftar_makanan[nomor-1].nutrisi.karbohidrat = val;

                                    cout << "  Lemak       [" << daftar_makanan[nomor-1].nutrisi.lemak       << "] : "; cin >> val;
                                    if (val > 0) daftar_makanan[nomor-1].nutrisi.lemak = val;

                                    cout << "  Serat       [" << daftar_makanan[nomor-1].nutrisi.serat       << "] : "; cin >> val;
                                    if (val > 0) daftar_makanan[nomor-1].nutrisi.serat = val;

                                    cin.ignore();
                                    cout << "\n  [+] Data berhasil diubah!" << endl;
                                } else {
                                    cout << "  [!] Nomor tidak valid!" << endl;
                                }
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // ADMIN 4 : HAPUS DATA MAKANAN
                        // -----------------------------------------------
                        else if (p_admin == 4) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> HAPUS DATA MAKANAN" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_makanan == 0) {
                                cout << "  Belum ada data makanan." << endl;
                            } else {
                                // Tabel ringkas: No | Nama | Kategori
                                string g2 = "+-----+----------------------+----------------+";
                                cout << g2 << endl;
                                cout << "| " << left << setw(3) << "No" << " | "
                                     << setw(20) << "Nama Makanan"       << " | "
                                     << setw(14) << "Kategori"           << " |" << endl;
                                cout << g2 << endl;
                                for (int i = 0; i < jumlah_makanan; i++) {
                                    cout << "| " << left << setw(3) << i + 1                        << " | "
                                         << setw(20) << daftar_makanan[i].nama_makanan              << " | "
                                         << setw(14) << daftar_makanan[i].kategori                  << " |" << endl;
                                }
                                cout << g2 << endl;

                                int nomor;
                                cout << "\n  Nomor yang dihapus: ";
                                cin >> nomor;
                                cin.ignore();

                                if (nomor >= 1 && nomor <= jumlah_makanan) {
                                    char konfirmasi;
                                    cout << "  Yakin hapus \"" << daftar_makanan[nomor-1].nama_makanan << "\"? (y/n): ";
                                    cin >> konfirmasi;
                                    cin.ignore();

                                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                                        // Geser elemen ke kiri (delete array - Modul 2)
                                        for (int i = nomor - 1; i < jumlah_makanan - 1; i++) {
                                            daftar_makanan[i] = daftar_makanan[i + 1];
                                        }
                                        jumlah_makanan--;
                                        cout << "\n  [+] Data berhasil dihapus!" << endl;
                                    } else {
                                        cout << "\n  [-] Penghapusan dibatalkan." << endl;
                                    }
                                } else {
                                    cout << "  [!] Nomor tidak valid!" << endl;
                                }
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // ADMIN 5 : KELOLA REQUEST (TABEL)
                        // -----------------------------------------------
                        else if (p_admin == 5) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> MANAJEMEN REQUEST PENGGUNA" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_request == 0) {
                                cout << "  Belum ada request dari pengguna." << endl;
                                cout << "\n  Tekan Enter untuk melanjutkan...";
                                cin.get();
                            } else {
                                string gr = "+-----+----------------------+------------------+----------------------+";
                                cout << gr << endl;
                                cout << "| " << left << setw(3) << "No" << " | "
                                     << setw(20) << "Nama Makanan"       << " | "
                                     << setw(16) << "Peminta"            << " | "
                                     << setw(20) << "Status"             << " |" << endl;
                                cout << gr << endl;
                                for (int i = 0; i < jumlah_request; i++) {
                                    string status = daftar_request[i].sudah_dikonfirmasi
                                                    ? "Dikonfirmasi" : "Menunggu...";
                                    cout << "| " << left << setw(3) << i + 1                                  << " | "
                                         << setw(20) << daftar_request[i].nama_makanan_diminta               << " | "
                                         << setw(16) << daftar_request[i].nama_peminta                       << " | "
                                         << setw(20) << status                                               << " |" << endl;
                                }
                                cout << gr << endl;

                                int nomor;
                                cout << "\n  Nomor request (0 = batal): ";
                                cin >> nomor;
                                cin.ignore();

                                if (nomor >= 1 && nomor <= jumlah_request) {
                                    if (daftar_request[nomor-1].sudah_dikonfirmasi) {
                                        cout << "  [!] Request ini sudah dikonfirmasi." << endl;
                                    } else {
                                        cout << "\n  Makanan : " << daftar_request[nomor-1].nama_makanan_diminta << endl;
                                        cout << "  Catatan : " << daftar_request[nomor-1].catatan_request       << endl;
                                        cout << "  Dari    : " << daftar_request[nomor-1].nama_peminta          << endl;
                                        cout << "\n  1. Konfirmasi + tambah data gizi" << endl;
                                        cout << "  2. Konfirmasi saja" << endl;
                                        cout << "  0. Batal" << endl;
                                        cout << "  Pilihan: ";

                                        int sub;
                                        cin >> sub;
                                        cin.ignore();

                                        if (sub == 1 && jumlah_makanan < MAKS_MAKANAN) {
                                            DataMakanan baru;
                                            baru.nama_makanan = daftar_request[nomor-1].nama_makanan_diminta;
                                            cout << "  Kategori : ";
                                            getline(cin, baru.kategori);
                                            cout << "\n  -- Nutrisi per 100 gram --" << endl;
                                            cout << "  Kalori      (kkal) : "; cin >> baru.nutrisi.kalori;
                                            cout << "  Protein     (gr)   : "; cin >> baru.nutrisi.protein;
                                            cout << "  Karbohidrat (gr)   : "; cin >> baru.nutrisi.karbohidrat;
                                            cout << "  Lemak       (gr)   : "; cin >> baru.nutrisi.lemak;
                                            cout << "  Serat       (gr)   : "; cin >> baru.nutrisi.serat;
                                            cin.ignore();

                                            daftar_makanan[jumlah_makanan] = baru;
                                            jumlah_makanan++;
                                            daftar_request[nomor-1].sudah_dikonfirmasi = true;
                                            cout << "\n  [+] Data ditambahkan dan request dikonfirmasi!" << endl;

                                        } else if (sub == 2) {
                                            daftar_request[nomor-1].sudah_dikonfirmasi = true;
                                            cout << "\n  [+] Request dikonfirmasi!" << endl;
                                        }
                                    }
                                }
                                cout << "\n  Tekan Enter untuk melanjutkan...";
                                cin.get();
                            }
                        }

                        // -----------------------------------------------
                        // ADMIN 0 : LOGOUT
                        // -----------------------------------------------
                        else if (p_admin == 0) {
                            admin_aktif = false;
                            cout << "\n  Logout berhasil! Sampai jumpa, "
                                 << pengguna_aktif.nama_pengguna << "." << endl;
                            cout << "  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        } else {
                            cout << "\n  [!] Pilihan tidak valid!" << endl;
                            cout << "  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                    } // end while admin_aktif

                } // end if admin

                // ===================================================
                // MENU USER
                // ===================================================
                else {

                    int  p_user;
                    bool user_aktif = true;

                    while (user_aktif) {

                        system("cls");
                        cout << "==================================================" << endl;
                        cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
                        cout << "==================================================" << endl;
                        cout << "  >> MENU USER  |  User: " << pengguna_aktif.nama_pengguna << endl;
                        cout << "==================================================" << endl;
                        cout << "  1. Lihat Informasi Gizi Makanan" << endl;
                        cout << "  2. Request Tambah Data Makanan" << endl;
                        cout << "  3. Status Request Saya" << endl;
                        cout << "  0. Logout" << endl;
                        cout << "--------------------------------------------------" << endl;
                        cout << "  Pilihan: ";
                        cin >> p_user;
                        cin.ignore();

                        // -----------------------------------------------
                        // USER 1 : LIHAT INFORMASI GIZI (TABEL PENUH)
                        // -----------------------------------------------
                        if (p_user == 1) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> INFORMASI GIZI MAKANAN" << endl;
                            cout << "     (* Nilai nutrisi per 100 gram)" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_makanan == 0) {
                                cout << "  Belum ada data makanan." << endl;
                            } else {
                                string g = "+-----+----------------------+----------------+----------+----------+----------+----------+---------+";
                                cout << g << endl;
                                cout << "| "
                                     << left << setw(3)  << "No"        << " | "
                                     << setw(20) << "Nama Makanan"      << " | "
                                     << setw(14) << "Kategori"          << " | "
                                     << setw(8)  << "Kalori"            << " | "
                                     << setw(8)  << "Protein"           << " | "
                                     << setw(8)  << "Karbo"             << " | "
                                     << setw(8)  << "Lemak"             << " | "
                                     << setw(7)  << "Serat"             << " |" << endl;
                                cout << "| "
                                     << setw(3)  << ""   << " | "
                                     << setw(20) << ""   << " | "
                                     << setw(14) << ""   << " | "
                                     << setw(8)  << "(kkal)" << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(8)  << "(gr)"   << " | "
                                     << setw(7)  << "(gr)"   << " |" << endl;
                                cout << g << endl;

                                cout << fixed << setprecision(1);
                                for (int i = 0; i < jumlah_makanan; i++) {
                                    cout << "| "
                                         << left << setw(3)  << i + 1                                  << " | "
                                         << setw(20) << daftar_makanan[i].nama_makanan                 << " | "
                                         << setw(14) << daftar_makanan[i].kategori                     << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.kalori               << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.protein              << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.karbohidrat          << " | "
                                         << setw(8)  << daftar_makanan[i].nutrisi.lemak                << " | "
                                         << setw(7)  << daftar_makanan[i].nutrisi.serat                << " |" << endl;
                                }
                                cout << g << endl;
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // USER 2 : KIRIM REQUEST
                        // -----------------------------------------------
                        else if (p_user == 2) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> REQUEST TAMBAH DATA MAKANAN" << endl;
                            cout << "==================================================" << endl;

                            if (jumlah_request >= MAKS_REQUEST) {
                                cout << "  [!] Kapasitas request sudah penuh." << endl;
                            } else {
                                RequestMakanan req;
                                req.nama_peminta       = pengguna_aktif.nama_pengguna;
                                req.sudah_dikonfirmasi = false;

                                cout << "  Nama makanan yang ingin ditambahkan: ";
                                getline(cin, req.nama_makanan_diminta);
                                cout << "  Catatan (opsional)                 : ";
                                getline(cin, req.catatan_request);

                                daftar_request[jumlah_request] = req;
                                jumlah_request++;
                                cout << "\n  [+] Request terkirim! Tunggu konfirmasi admin." << endl;
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // USER 3 : STATUS REQUEST (TABEL)
                        // -----------------------------------------------
                        else if (p_user == 3) {

                            system("cls");
                            cout << "==================================================" << endl;
                            cout << "  >> STATUS REQUEST SAYA" << endl;
                            cout << "==================================================" << endl;

                            string gr = "+-----+----------------------+------------------------------+";
                            cout << gr << endl;
                            cout << "| " << left << setw(3) << "No" << " | "
                                 << setw(20) << "Nama Makanan"       << " | "
                                 << setw(28) << "Status"             << " |" << endl;
                            cout << gr << endl;

                            bool ada = false;
                            int  no  = 1;
                            for (int i = 0; i < jumlah_request; i++) {
                                if (daftar_request[i].nama_peminta == pengguna_aktif.nama_pengguna) {
                                    ada = true;
                                    string status = daftar_request[i].sudah_dikonfirmasi
                                                    ? "Sudah dikonfirmasi admin"
                                                    : "Menunggu konfirmasi admin...";
                                    cout << "| " << left << setw(3) << no                                       << " | "
                                         << setw(20) << daftar_request[i].nama_makanan_diminta                  << " | "
                                         << setw(28) << status                                                  << " |" << endl;
                                    no++;
                                }
                            }
                            cout << gr << endl;

                            if (!ada) {
                                cout << "\n  Kamu belum mengirim request apapun." << endl;
                            }
                            cout << "\n  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                        // -----------------------------------------------
                        // USER 0 : LOGOUT
                        // -----------------------------------------------
                        else if (p_user == 0) {
                            user_aktif = false;
                            cout << "\n  Logout berhasil! Sampai jumpa, "
                                 << pengguna_aktif.nama_pengguna << "." << endl;
                            cout << "  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        } else {
                            cout << "\n  [!] Pilihan tidak valid!" << endl;
                            cout << "  Tekan Enter untuk melanjutkan...";
                            cin.get();
                        }

                    } // end while user_aktif

                } // end else user

            } // end if login_berhasil

        } // end pilihan 1

        // ===================================================
        // PILIHAN 2 : REGISTER
        // ===================================================
        else if (pilihan == 2) {

            system("cls");
            cout << "==================================================" << endl;
            cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
            cout << "==================================================" << endl;
            cout << "  >> REGISTRASI AKUN BARU" << endl;
            cout << "==================================================" << endl;

            if (jumlah_pengguna >= MAKS_PENGGUNA) {
                cout << "  [!] Kapasitas pengguna sudah penuh!" << endl;
            } else {
                string nama, nim;
                cout << "  Nama (username) : ";
                getline(cin, nama);

                bool nama_sudah_ada = false;
                for (int i = 0; i < jumlah_pengguna; i++) {
                    if (daftar_pengguna[i].nama_pengguna == nama) {
                        nama_sudah_ada = true;
                    }
                }

                if (nama == "") {
                    cout << "  [!] Nama tidak boleh kosong!" << endl;
                } else if (nama_sudah_ada) {
                    cout << "  [!] Nama sudah digunakan, pilih nama lain." << endl;
                } else {
                    cout << "  NIM  (password) : ";
                    getline(cin, nim);
                    if (nim == "") {
                        cout << "  [!] NIM tidak boleh kosong!" << endl;
                    } else {
                        daftar_pengguna[jumlah_pengguna].nama_pengguna  = nama;
                        daftar_pengguna[jumlah_pengguna].nim_pengguna   = nim;
                        daftar_pengguna[jumlah_pengguna].peran_pengguna = "user";
                        jumlah_pengguna++;
                        cout << "\n  [+] Registrasi berhasil! Silakan login." << endl;
                    }
                }
            }
            cout << "\n  Tekan Enter untuk melanjutkan...";
            cin.get();
        }

        // ===================================================
        // PILIHAN 0 : KELUAR
        // ===================================================
        else if (pilihan == 0) {
            berjalan = false;
            system("cls");
            cout << "==================================================" << endl;
            cout << "     SISTEM INFORMASI MANAJEMEN DATA GIZI        " << endl;
            cout << "==================================================" << endl;
            cout << "  Terima kasih telah menggunakan program ini!" << endl;
            cout << "  Program selesai." << endl;
            cout << "==================================================" << endl;
        } else {
            cout << "\n  [!] Pilihan tidak valid!" << endl;
            cout << "  Tekan Enter untuk melanjutkan...";
            cin.get();
        }

    } // end while berjalan

    return 0;
}