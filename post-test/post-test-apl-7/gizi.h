#ifndef GIZI_H
#define GIZI_H

#include <iostream>
#include <string>

using namespace std;

struct Nutrisi { float kalori, protein, karbohidrat, lemak; };
struct DataGizi { string namaMakanan, kategori; Nutrisi nutrisi; bool isConfirmed; string peminta; };
struct AkunUser { string username, password; };

extern const string LINE;
extern const string HEAD;

void animasiLoading();
void cetakBaris(int nomorUrut, DataGizi* gizi);
void cetakTabelGizi(DataGizi gizi[], int jumlahData);
void cetakTabelGizi(DataGizi gizi[], int jumlahData, string kategoriCari);
void bubbleSortNamaDescending(DataGizi gizi[], int n);
void bubbleSortNamaAscending(DataGizi gizi[], int n);
void selectionSortKaloriAscending(DataGizi gizi[], int n);
void insertionSortProteinDescending(DataGizi gizi[], int n);
void menuSorting(DataGizi gizi[], int jumlahData);
void binarySearchNama(DataGizi* gizi, int n, string target);
void interpolationSearchKalori(DataGizi* gizi, int n, float target);
void menuSearching(DataGizi* gizi, int jumlahData);
float totalKaloriRekursif(DataGizi gizi[], int jumlahData);
int cariIndex(DataGizi gizi[], int jumlahData, int pilihan, bool confirmed);
void tambahAtauRequestData(DataGizi gizi[], int& jumlahData, string peminta, bool isConfirmed);
void ubahData(DataGizi gizi[], int jumlahData);
void hapusData(DataGizi gizi[], int& jumlahData);
void konfirmasiRequest(DataGizi gizi[], int jumlahData);
void menuAdmin(DataGizi gizi[], int& jumlahData, string inputUsername);
void menuUser(DataGizi gizi[], int& jumlahData, string inputUsername);
void menuLogin(DataGizi gizi[], int& jumlahData, AkunUser users[], int jumlahUser);
void menuRegister(AkunUser users[], int& jumlahUser);

#endif