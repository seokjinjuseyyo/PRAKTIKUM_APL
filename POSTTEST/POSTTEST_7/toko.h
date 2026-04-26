#ifndef TOKO_H
#define TOKO_H
// User-Defined Library buat Program Toko Petshop whingky
// Isinya ada struct, konstantanya, fungsi pembantuna, dan fungsi validasi nya
//  tujuannya ya untuk exception handling 

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>   // buat exception handling kayak invalid_argument, runtime_error, dan kawan kawan
using namespace std;

const int MAX_PRODUK = 100; // kapasitas maksimal array buat produk
const int MAX_USER   = 50;  // kapasitas maksimal array buat pengguna

const int LEBAR_ID    = 4;  // lebar kolom ID nya
const int LEBAR_NAMA  = 25; // lebar kolom Nama Produk nya
const int LEBAR_KAT   = 16; // lebar kolom Kategori nya
const int LEBAR_HARGA = 10; // lebar kolom Harga nya
const int LEBAR_STOK  = 5;  // lebar kolom Stok nya

struct Kategori { // struct buat kategori
    string namaKategori;
};

struct Produk { // struct buat produk
    int      idProduk;
    string   namaProduk;
    Kategori kategori;
    int      hargaProduk;
    int      stokProduk;
};

struct Pengguna { // struct buat pengguna, role yang isinya "admin" atau "user"
    string username;
    string password;
    string role;
};

int inputAngka() { // biar gak infinity loop kalau inputnya ntar bukan angka
    int nilai;
    while (!(cin >> nilai)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Input harus berupa angka bulat!"); // throw kalau inputnya bukan angka 
    }
    cin.ignore(1000, '\n');
    return nilai;
}

int inputAngkaAman() { // kita buat inputAngka() pakai loop retry biar pemanggil ntar gak perlu nulis loop sendiri
    while (true) {
        try {
            return inputAngka();
        } catch (const invalid_argument& e) {
            cout << "[!] " << e.what() << " Coba lagi: ";
        }
    }
}

// fungsi-fungsi validasi buat exception handling
void validasiStringKosong(const string& teks, const string& namaField) { // throw kalau field kosong atau isinya spasi semua
    bool semuaSpasi = true;
    for (char karakter : teks)
        if (karakter != ' ') { semuaSpasi = false; break; }
    if (teks.empty() || semuaSpasi)
        throw invalid_argument("Field '" + namaField + "' tidak boleh kosong!");
}

void validasiHarga(int harga) { // throw kalau harganya <= 0
    if (harga <= 0)
        throw invalid_argument("Harga harus lebih dari 0!");
}

void validasiStok(int stok) { // throw kalau stoknya negatif
    if (stok < 0)
        throw invalid_argument("Stok tidak boleh bernilai negatif!");
}

void validasiPassword(const string& password) { // throw kalau passwordnya nanti kurang dari 4 karakter
    if (password.length() < 4)
        throw invalid_argument("Password minimal 4 karakter!");
}

void cetakGaris() {
    cout << "=";
    for (int i = 0; i < LEBAR_ID + 2;    i++) cout << "=";
    cout << "|";
    for (int i = 0; i < LEBAR_NAMA + 2;  i++) cout << "=";
    cout << "|";
    for (int i = 0; i < LEBAR_KAT + 2;   i++) cout << "=";
    cout << "|";
    for (int i = 0; i < LEBAR_HARGA + 5; i++) cout << "=";
    cout << "|";
    for (int i = 0; i < LEBAR_STOK + 2;  i++) cout << "=";
    cout << "=" << endl;
}

void cetakGarisBaris() {
    cout << "-";
    for (int i = 0; i < LEBAR_ID + 2;    i++) cout << "-";
    cout << "|";
    for (int i = 0; i < LEBAR_NAMA + 2;  i++) cout << "-";
    cout << "|";
    for (int i = 0; i < LEBAR_KAT + 2;   i++) cout << "-";
    cout << "|";
    for (int i = 0; i < LEBAR_HARGA + 5; i++) cout << "-";
    cout << "|";
    for (int i = 0; i < LEBAR_STOK + 2;  i++) cout << "-";
    cout << "-" << endl;
}

void cetakHeaderTabel() { // prosedur buat nyetak baris header kolom tabelnya
    cetakGaris();
    cout << "| " << left << setw(LEBAR_ID)        << "ID"
         << " | " << setw(LEBAR_NAMA)              << "Nama Produk"
         << " | " << setw(LEBAR_KAT)               << "Kategori"
         << " | " << setw(LEBAR_HARGA + 3)         << "Harga"
         << " | " << setw(LEBAR_STOK)              << "Stok"
         << " |" << endl;
    cetakGaris();
}

void cetakBarisProduk(Produk *produkPtr) { // * sebagai parameter fungsinya
    string namaTampil = produkPtr->namaProduk; // kita akses field nya pakai arrow operator karena pointer
    if ((int)namaTampil.size() > LEBAR_NAMA)
        namaTampil = namaTampil.substr(0, LEBAR_NAMA);

    string katTampil = produkPtr->kategori.namaKategori; // akses nested struct lewat pointer
    if ((int)katTampil.size() > LEBAR_KAT)
        katTampil = katTampil.substr(0, LEBAR_KAT);

    string hargaStr = "Rp " + to_string(produkPtr->hargaProduk); // akses harganya lewat pointer jugak

    cout << "| " << left << setw(LEBAR_ID)        << produkPtr->idProduk
         << " | " << left << setw(LEBAR_NAMA)      << namaTampil
         << " | " << left << setw(LEBAR_KAT)       << katTampil
         << " | " << left << setw(LEBAR_HARGA + 3) << hargaStr
         << " | " << left << setw(LEBAR_STOK)      << produkPtr->stokProduk
         << " |" << endl;
}

#endif // TOKO_H