#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>   // buat exception handling 
#include "toko.h"      // user-defined library yang toko.h ituu
using namespace std;

Produk   daftarProduk[MAX_PRODUK]; // variabel global array produknya
int      jumlahProduk = 0;
int      idBerikutnya = 1;

Pengguna daftarPengguna[MAX_USER]; // variabel global array penggunanya
int      jumlahPengguna = 0;

void cetakTabelProduk();

int  hitungTotalBelanja(int idKeranjang[], int jumlahKeranjang[], int isiKeranjang, int indeks);

int  cariProduk(int idCari);        // buat nyari berdasarkan ID pakai binary search
void cariProduk(string keyword);    // buat nyari berdasarkan keyword nama pakai linear search

bool cekLogin(string usernameInput, string passwordInput, string &usernameAktif, string &roleAktif); // & digunakan sebagai parameter referensi
void prosesRegister();

void lihatSemuaProduk();
void tambahProduk();
void updateProduk();
void hapusProduk();
void cariProdukAdmin();

void selectionSortNama();      // sorting nama A-Z pakai yang Selection Sort
void bubbleSortHargaDesc();    // sorting harga termahal pakai yang Bubble Sort
void insertionSortStokAsc();   // sorting stok tersedikit pakai yang Insertion Sort
void sortingProduk();          // menu pemilihan metode sorting

void menuAdmin(string usernameAktif);
void beliProduk(string usernameAktif);
void menuUser(string usernameAktif);

void cetakTabelProduk() { // prosedur buat nyetak tabelnya biar rapi
    cetakHeaderTabel();
    if (jumlahProduk == 0) {
        cout << "| Belum ada produk yang tersedia saat ini.                             |" << endl;
    } else {
        for (int i = 0; i < jumlahProduk; i++) {
            cetakBarisProduk(&daftarProduk[i]); // kirim alamat elemen arraynya pakai &
            if (i < jumlahProduk - 1) cetakGarisBaris();
        }
    }
    cetakGaris();
}

int hitungTotalBelanja(int idKeranjang[], int jumlahKeranjang[], int isiKeranjang, int indeks) {
    if (indeks >= isiKeranjang) return 0;

    int subtotal = 0; // kita cari harga produknya berdasarkan id yang adadi keranjang
    for (int j = 0; j < jumlahProduk; j++) {
        if (daftarProduk[j].idProduk == idKeranjang[indeks]) {
            subtotal = daftarProduk[j].hargaProduk * jumlahKeranjang[indeks];
            break;
        }
    }
    return subtotal + hitungTotalBelanja(idKeranjang, jumlahKeranjang, isiKeranjang, indeks + 1); // subtotal item ini ditambah total semua item setelahnya
}

int cariProduk(int idCari) { // ini buat nyari berdasarkan ID pakai Binary Search, return indeks atau -1 kalau gak ketemu
    if (idCari < 1)
        throw out_of_range("ID produk tidak valid (harus >= 1)!"); // throw kalau ID nya gak masuk akal
    int low  = 0;
    int high = jumlahProduk - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // hitung indeks tengah, cara ini buat hindari integer overflow

        if (daftarProduk[mid].idProduk == idCari) {
            return mid; // kalau ketemu, langsung return indeksnya
        } else if (daftarProduk[mid].idProduk < idCari) {
            low = mid + 1; // id yang dicari ada di sebelah kanan, geser low ke kanan
        } else {
            high = mid - 1; // id yang dicari ada di sebelah kiri, geser high ke kiri
        }
    }
    return -1; // ini kalau gak ketemu sama sekali
}

void cariProdukLinear(Produk *arrProduk, int jumlah, string keyword) { // pakai pointer ke array produk sebagai parameter, ini linear search buat cari berdasarkan keyword nama
    validasiStringKosong(keyword, "Kata kunci"); // throw kalau keyword nya kosong

    for (int j = 0; keyword[j] != '\0'; j++) // ubah keyword ke huruf kecil semua biar gak sensitive
        if (keyword[j] >= 'A' && keyword[j] <= 'Z') keyword[j] += 32;

    cetakHeaderTabel();
    bool adaHasil = false;

    for (int i = 0; i < jumlah; i++) { // linear search, periksa satu-satu dari awal sampai akhir
        string namaCek = (arrProduk + i)->namaProduk; // akses elemen array lewat pointer pakai aritmatika pointer
        for (int j = 0; namaCek[j] != '\0'; j++) // ubah nama produk ke lowercase biar bisa kita bandingkan
            if (namaCek[j] >= 'A' && namaCek[j] <= 'Z') namaCek[j] += 32;

        int panjangKw = 0, panjangNm = 0; // hitung panjang keyword dan panjang nama produknya
        for (int j = 0; keyword[j] != '\0'; j++) panjangKw++;
        for (int j = 0; namaCek[j] != '\0'; j++) panjangNm++;

        bool cocok = false; // cek apakah keyword ada di dalam nama produk
        for (int j = 0; j <= panjangNm - panjangKw && !cocok; j++) {
            bool sama = true;
            for (int k = 0; k < panjangKw && sama; k++)
                if (namaCek[j + k] != keyword[k]) sama = false;
            if (sama) cocok = true;
        }

        if (cocok) {
            cetakBarisProduk(arrProduk + i); // kirim pointernya ke elemen yang cocok pakai aritmatika pointer
            adaHasil = true;
        }
    }

    if (!adaHasil)
        cout << "| Produk yang anda cari tidak ditemukan.                               |" << endl;
    cetakGaris();
}

void cariProduk(string keyword) { // ini buat manggil linear search dengan pointer, biar pemanggilan dari luar tetap sama
    cariProdukLinear(daftarProduk, jumlahProduk, keyword); // kirim array daftarProduk sebagai pointer
}

bool cekLogin(string usernameInput, string passwordInput, string &usernameAktif, string &roleAktif) {
    for (int i = 0; i < jumlahPengguna; i++) {
        if (usernameInput == daftarPengguna[i].username &&
            passwordInput == daftarPengguna[i].password) {
            usernameAktif = daftarPengguna[i].username;
            roleAktif     = daftarPengguna[i].role;
            return true;
        }
    }
    return false;
}

void prosesRegister() { // prosedur buat daftar akun baru, nanti ini otomatis jadi role "user"
    cout << "\n--- REGISTER AKUN BARU ---" << endl;

    try { 
        if (jumlahPengguna >= MAX_USER)
            throw length_error("Kapasitas pengguna sudah penuh!"); // throw kalau array penggunanya udah penuh
        string usernameBaru, passwordBaru;
        cout << "Username : ";
        getline(cin, usernameBaru);
        validasiStringKosong(usernameBaru, "Username"); // throw kalau usernamenya kosong

        bool sudahAda = false; // cek dulu apakah usernamenya ini sudah dipakaikah belum
        for (int i = 0; i < jumlahPengguna; i++) {
            if (daftarPengguna[i].username == usernameBaru) {
                sudahAda = true;
                break;
            }
        }

        if (sudahAda)
            throw runtime_error("Username '" + usernameBaru + "' sudah digunakan!"); // throw kalau username nya ternyata duplikat

        cout << "Password : ";
        getline(cin, passwordBaru);
        validasiPassword(passwordBaru); // throw kalau passwordnya kurang dari 4 karakter

        daftarPengguna[jumlahPengguna].username = usernameBaru;
        daftarPengguna[jumlahPengguna].password = passwordBaru;
        daftarPengguna[jumlahPengguna].role     = "user";
        jumlahPengguna++;

        cout << "[+] Registrasi anda berhasil! Silahkan login." << endl;

    } catch (const length_error& e) {
        cout << "[!] Error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "[!] Input tidak valid: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "[!] Gagal register: " << e.what() << endl;
    }
}

void lihatSemuaProduk() { // prosedur buat nampilin semua produk 
    cout << "\n--- DAFTAR SEMUA PRODUK ---" << endl;
    cetakTabelProduk();
}

void tambahProduk() { // prosedur buat tambah produk baru ke array daftarProduk
    cout << "\n--- TAMBAH PRODUK BARU ---" << endl;

    try { 
        if (jumlahProduk >= MAX_PRODUK)
            throw length_error("Kapasitas produk sudah penuh!"); // throw kalau array produknya udah penuh

        int indeksBaru = jumlahProduk;
        daftarProduk[indeksBaru].idProduk = idBerikutnya++;

        string namaProdukBaru, kategoriProdukBaru;
        cout << "Nama Produk : ";
        getline(cin, namaProdukBaru);
        validasiStringKosong(namaProdukBaru, "Nama Produk"); // throw kalau namanya kosong 

        cout << "Kategori    : ";
        getline(cin, kategoriProdukBaru);
        validasiStringKosong(kategoriProdukBaru, "Kategori"); // throw kalau kategorinya kosong

        daftarProduk[indeksBaru].namaProduk            = namaProdukBaru;
        daftarProduk[indeksBaru].kategori.namaKategori = kategoriProdukBaru;

        cout << "Harga (Rp)  : ";
        int hargaBaru = inputAngkaAman();
        validasiHarga(hargaBaru); // throw kalau harganya <= 0 
        daftarProduk[indeksBaru].hargaProduk = hargaBaru;

        int stokBaru;
        do { // stok nya tidak boleh negatif, kalau salah ya suruh input ulang pembelinya
            cout << "Stok        : ";
            stokBaru = inputAngkaAman();
            try {
                validasiStok(stokBaru); // throw kalau stoknya negatif 
            } catch (const invalid_argument& e) {
                cout << "[!] " << e.what() << " Tolong input ulang." << endl;
                stokBaru = -1; // paksa loop ulang pokoknya
            }
        } while (stokBaru < 0);
        daftarProduk[indeksBaru].stokProduk = stokBaru;

        jumlahProduk++;
        cout << "[+] Produk berhasil ditambahkan dengan ID: "
             << daftarProduk[indeksBaru].idProduk << endl;

    } catch (const length_error& e) {
        cout << "[!] Error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "[!] Input tidak valid: " << e.what() << endl;
        idBerikutnya--; // kembalikan counter ID nya karena produknya kan gagal ditambahkan
    }
}

void updateProduk() { // prosedur update salah satu field produk berdasarkan ID nya
    cout << "\n--- UPDATE PRODUK ---" << endl;
    cetakTabelProduk();

    if (jumlahProduk == 0) return;

    try { // 
        cout << "ID produk yang ingin diupdate: ";
        int idUpdate = inputAngkaAman();

        int indeks = cariProduk(idUpdate); // pakai binary search untuk cari berdasarkan ID nya
        if (indeks == -1)
            throw runtime_error("Produk dengan ID " + to_string(idUpdate) + " tidak ditemukan!"); // throw kalau produknya gak ketemu 

        cout << "Produk ditemukan: " << daftarProduk[indeks].namaProduk << endl;
        cout << " 1. Nama" << endl;
        cout << " 2. Kategori" << endl;
        cout << " 3. Harga" << endl;
        cout << " 4. Stok" << endl;
        cout << "Field yang ingin diupdate (1-4): ";
        int pilihanField = inputAngkaAman();

        if (pilihanField == 1) {
            string namaBaru;
            cout << "Nama baru: ";
            getline(cin, namaBaru);
            validasiStringKosong(namaBaru, "Nama"); // throw kalau namanya kosong
            daftarProduk[indeks].namaProduk = namaBaru;
            cout << "[+] Nama berhasil diupdate." << endl;
        } else if (pilihanField == 2) {
            string kategoriBaru;
            cout << "Kategori baru: ";
            getline(cin, kategoriBaru);
            validasiStringKosong(kategoriBaru, "Kategori"); // throw kalau kategorinya kosong
            daftarProduk[indeks].kategori.namaKategori = kategoriBaru;
            cout << "[+] Kategori berhasil diupdate." << endl;
        } else if (pilihanField == 3) {
            cout << "Harga baru (Rp): ";
            int hargaBaru = inputAngkaAman();
            validasiHarga(hargaBaru); // throw kalau harganya <= 0 (baru - modul 8)
            daftarProduk[indeks].hargaProduk = hargaBaru;
            cout << "[+] Harga berhasil diupdate." << endl;
        } else if (pilihanField == 4) {
            int stokBaru;
            do {
                cout << "Stok baru: ";
                stokBaru = inputAngkaAman();
                try {
                    validasiStok(stokBaru); // throw kalau stoknya negatif
                } catch (const invalid_argument& e) {
                    cout << "[!] " << e.what() << endl;
                    stokBaru = -1;
                }
            } while (stokBaru < 0);
            daftarProduk[indeks].stokProduk = stokBaru;
            cout << "[+] Stok berhasil diupdate." << endl;
        } else {
            throw invalid_argument("Pilihan field tidak valid (harus 1-4)!"); // throw kalau pilihannya gak valid
        }

    } catch (const out_of_range& e) {
        cout << "[!] Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "[!] Error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "[!] Input tidak valid: " << e.what() << endl;
    }
}

void hapusProduk() { // prosedur hapus produk berdasarkan ID nya
    cout << "\n--- HAPUS PRODUK ---" << endl;
    cetakTabelProduk();

    if (jumlahProduk == 0) return;

    try { 
        cout << "ID produk yang ingin dihapus: ";
        int idHapus = inputAngkaAman();

        int indeks = cariProduk(idHapus);
        if (indeks == -1)
            throw runtime_error("Produk dengan ID " + to_string(idHapus) + " tidak ditemukan!"); // throw kalau produknya gak ketemu 
        cout << "Yakin mau hapus '" << daftarProduk[indeks].namaProduk << "'? (y/n): ";
        string konfirmasi;
        getline(cin, konfirmasi);

        if (konfirmasi == "y" || konfirmasi == "Y") {
            for (int i = indeks; i < jumlahProduk - 1; i++) { // geser semua elemen ke kiri mulai dari posisi yang dihapus
                daftarProduk[i] = daftarProduk[i + 1];
            }
            jumlahProduk--;
            cout << "[+] Produk berhasil dihapus." << endl;
        } else {
            cout << "[-] Penghapusan telah berhasil dibatalkan." << endl;
        }

    } catch (const out_of_range& e) {
        cout << "[!] Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "[!] Error: " << e.what() << endl;
    }
}

void cariProdukAdmin() { // prosedur buat cari produk di menu admin
    cout << "\n--- CARI PRODUK ---" << endl;
    cout << "Kata kunci: ";
    string keyword;
    getline(cin, keyword);
    try {
        cariProduk(keyword); // panggil overload stringnya yang pakai linear search
    } catch (const invalid_argument& e) {
        cout << "[!] " << e.what() << endl;
    }
}

// Selection Sort buat ngurutin nama produk ascending (A ke Z)
void selectionSortNama() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int indeksMin = i; // kita anggap elemen sekarang yang paling kecil dulu
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (daftarProduk[j].namaProduk < daftarProduk[indeksMin].namaProduk)
                indeksMin = j; // trus kita simpan indeks yang namanya lebih kecil
        }
        if (indeksMin != i) { // kalau ketemu yang lebih kecil baru kita tukar
            Produk temp             = daftarProduk[i];
            daftarProduk[i]         = daftarProduk[indeksMin];
            daftarProduk[indeksMin] = temp;
        }
    }
}

// Bubble Sort buat ngurutin harga descending (dari yang termahal ke yang termurah)
void bubbleSortHargaDesc() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (daftarProduk[j].hargaProduk < daftarProduk[j + 1].hargaProduk) { // kalau yang kiri lebih kecil dari kanan, ya kita tukar
                Produk temp         = daftarProduk[j];
                daftarProduk[j]     = daftarProduk[j + 1];
                daftarProduk[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // kalau tidak ada yang ditukar ya berarti sudah urut
    }
}

// Insertion Sort buat ngurutin stok ascending (dari stok dikit ke banyak)
// untuk metodenya bebas dipilih biar admin bisa lihat produk yang stoknya mau habis duluan
void insertionSortStokAsc() {
    for (int i = 1; i < jumlahProduk; i++) {
        Produk kunci = daftarProduk[i]; // ambil elemen yang sekarang sebagai kunci
        int j = i - 1;
        while (j >= 0 && daftarProduk[j].stokProduk > kunci.stokProduk) { // geser elemen yang stoknya lebih besar ke kanan
            daftarProduk[j + 1] = daftarProduk[j];
            j--;
        }
        daftarProduk[j + 1] = kunci; // sisipkan key nya di posisi yang benar
    }
}

void sortingProduk() { // prosedur menu sorting produk, ntar dipanggil dari menuAdmin
    cout << "\n--- SORTING PRODUK ---" << endl;
    if (jumlahProduk == 0) {
        cout << "Belum ada produk untuk diurutkan." << endl;
        return;
    }
    cout << " 1. Urutkan Nama Produk A-Z    " << endl; // ini pakai yang selection sort
    cout << " 2. Urutkan Harga Termahal     " << endl; // ini pakai yang bubble sort
    cout << " 3. Urutkan Stok Tersedikit    " << endl; // yang ini make insertion sort
    cout << "Pilih metode sorting (1-3): ";

    try {
        int pilihanSort = inputAngkaAman();

        if (pilihanSort == 1) {
            selectionSortNama();
            cout << "[+] Produk berhasil diurutkan berdasarkan nama (A-Z)!" << endl;
            cetakTabelProduk();
        } else if (pilihanSort == 2) {
            bubbleSortHargaDesc();
            cout << "[+] Produk berhasil diurutkan berdasarkan harga (termahal ke termurah)!" << endl;
            cetakTabelProduk();
        } else if (pilihanSort == 3) {
            insertionSortStokAsc();
            cout << "[+] Produk berhasil diurutkan berdasarkan stok (tersedikit ke terbanyak)!" << endl;
            cetakTabelProduk();
        } else {
            throw invalid_argument("Pilihan sorting tidak valid (harus pilih 1-3)!"); // throw kalau pilihan gak valid 
        }

    } catch (const invalid_argument& e) {
        cout << "[!] " << e.what() << endl;
    }
}

void menuAdmin(string usernameAktif) { // prosedur menu admin, nanti looping terus sampai admin pilih logout
    int pilihanAdmin;
    do {
        cout << "\n|==================================================|" << endl;
        cout << "|                    MENU ADMIN                    |" << endl;
        cout << "|==================================================|" << endl;
        cout << "| 1. Lihat Semua Produk                            |" << endl;
        cout << "| 2. Tambah Produk                                 |" << endl;
        cout << "| 3. Update Produk                                 |" << endl;
        cout << "| 4. Hapus Produk                                  |" << endl;
        cout << "| 5. Cari Produk                                   |" << endl;
        cout << "| 6. Sorting Produk                                |" << endl;
        cout << "| 7. Logout                                        |" << endl;
        cout << "|==================================================|" << endl;
        cout << "Pilih menu (1-7): ";
        pilihanAdmin = inputAngkaAman(); // biar gak infinite loop

        switch (pilihanAdmin) {
            case 1: lihatSemuaProduk(); break;
            case 2: tambahProduk();     break;
            case 3: updateProduk();     break;
            case 4: hapusProduk();      break;
            case 5: cariProdukAdmin();  break;
            case 6: sortingProduk();    break;
            case 7:
                cout << "Logout berhasil. Sampai jumpa, " << usernameAktif << "!" << endl;
                break;
            default:
                cout << "[!] Pilihan anda tidak valid." << endl;
                break;
        }
    } while (pilihanAdmin != 7);
}

void beliProduk(string usernameAktif) { // prosedur proses belanjanya si pembeli
    cout << "\n--- BELI PRODUK ---" << endl;

    if (jumlahProduk == 0) {
        cout << "Belum ada produk tersedia." << endl;
        return;
    }

    int  idKeranjang[MAX_PRODUK];
    int  jumlahKeranjang[MAX_PRODUK];
    int  isiKeranjang   = 0;
    bool selesaiBelanja = false;

    do {
        cetakTabelProduk();

        if (isiKeranjang > 0) { // tampilkan isi keranjang kalau sudah ada barangnya
            cout << "\n  Keranjang kamu (" << isiKeranjang << " item):" << endl;
            for (int i = 0; i < isiKeranjang; i++) {
                int indeks = cariProduk(idKeranjang[i]);
                if (indeks != -1) {
                    cout << "  - " << daftarProduk[indeks].namaProduk
                         << " x" << jumlahKeranjang[i]
                         << " = Rp " << (daftarProduk[indeks].hargaProduk * jumlahKeranjang[i])
                         << endl;
                }
            }
        }

        cout << "ID produk yang ingin dibeli (0 = checkout): ";
        int idBeli = inputAngkaAman();

        if (idBeli == 0) {
            selesaiBelanja = true;
        } else {
            try { 
                int indeks = cariProduk(idBeli); // throw out_of_range kalau ID negatif

                if (indeks == -1)
                    throw runtime_error("Produk tidak ditemukan."); // throw kalau produknya gak ketemu 
                if (daftarProduk[indeks].stokProduk == 0)
                    throw runtime_error("Stok produk ini habis."); // throw kalau stoknya udah habis 

                cout << "  Produk : " << daftarProduk[indeks].namaProduk << endl;
                cout << "  Stok   : " << daftarProduk[indeks].stokProduk << endl;
                cout << "  Harga  : Rp " << daftarProduk[indeks].hargaProduk << endl;

                int jumlahBeli; // input jumlah beli, gak boleh lebih dari stok yaa
                do {
                    cout << "  Jumlah : ";
                    jumlahBeli = inputAngkaAman();
                    try {
                        if (jumlahBeli <= 0)
                            throw invalid_argument("Jumlah harus lebih dari 0!"); // throw kalau jumlah gak valid
                        if (jumlahBeli > daftarProduk[indeks].stokProduk)
                            throw out_of_range("Stok tidak cukup. Tersedia: " +
                                               to_string(daftarProduk[indeks].stokProduk)); // throw kalau melebihi stok
                    } catch (const invalid_argument& e) {
                        cout << "[!] " << e.what() << endl;
                        jumlahBeli = 0;
                    } catch (const out_of_range& e) {
                        cout << "[!] " << e.what() << endl;
                        jumlahBeli = 0;
                    }
                } while (jumlahBeli <= 0);

                bool sudahDiKeranjang = false; // kita cek apakah produknya sudah ada di keranjang
                for (int k = 0; k < isiKeranjang; k++) {
                    if (idKeranjang[k] == idBeli) {
                        int totalNanti = jumlahKeranjang[k] + jumlahBeli;
                        if (totalNanti > daftarProduk[indeks].stokProduk)
                            throw out_of_range("Total melebihi stok. Maksimal tambah: " +
                                               to_string(daftarProduk[indeks].stokProduk - jumlahKeranjang[k])); // throw kalau total keranjang melebihi stok 
                        jumlahKeranjang[k] = totalNanti;
                        cout << "Jumlah di keranjang diperbarui." << endl;
                        sudahDiKeranjang = true;
                        break;
                    }
                }

                if (!sudahDiKeranjang) { // kalau belum ada di keranjang, nanti kita tambahkan sebagai item baru
                    idKeranjang[isiKeranjang]     = idBeli;
                    jumlahKeranjang[isiKeranjang] = jumlahBeli;
                    isiKeranjang++;
                    cout << "Produk ditambahkan ke keranjang." << endl;
                }

            } catch (const out_of_range& e) {
                cout << "[!] Error: " << e.what() << endl;
            } catch (const runtime_error& e) {
                cout << "[!] Error: " << e.what() << endl;
            }
        }
    } while (!selesaiBelanja);

    if (isiKeranjang == 0) {
        cout << "Keranjang kosong, pembelian dibatalkan." << endl;
        return;
    }

    int totalBelanja = hitungTotalBelanja(idKeranjang, jumlahKeranjang, isiKeranjang, 0); // hitung total belanjaannya pakai fungsi rekursif
    const int LEBAR_STRUK = 48;
    auto cetakBarisStruk = [&](string label, string nilai) {
        string isi = label + nilai;
        cout << "| " << left << setw(LEBAR_STRUK) << isi << " |" << endl;
    };

    cout << "\n|" << string(LEBAR_STRUK + 2, '=') << "|" << endl;
    string judul = "STRUK PEMBELIAN";
    int padding  = (LEBAR_STRUK - (int)judul.size()) / 2;
    cout << "|" << string(padding, ' ') << judul
         << string(LEBAR_STRUK - padding - (int)judul.size(), ' ') << " |" << endl;
    cout << "|" << string(LEBAR_STRUK + 2, '=') << "|" << endl;

    cetakBarisStruk("Pembeli : ", usernameAktif);
    cout << "|" << string(LEBAR_STRUK + 2, '-') << "|" << endl;

    for (int i = 0; i < isiKeranjang; i++) {
        int indeks = cariProduk(idKeranjang[i]);
        if (indeks != -1) {
            cetakBarisStruk("Produk   : ", daftarProduk[indeks].namaProduk);
            cetakBarisStruk("Jumlah   : ", to_string(jumlahKeranjang[i]));
            cetakBarisStruk("Subtotal : ", "Rp " + to_string(daftarProduk[indeks].hargaProduk * jumlahKeranjang[i]));
            cout << "|" << string(LEBAR_STRUK + 2, '-') << "|" << endl;
        }
    }

    cetakBarisStruk("TOTAL    : ", "Rp " + to_string(totalBelanja));
    cout << "|" << string(LEBAR_STRUK + 2, '=') << "|" << endl;

    cout << "Konfirmasi pembelian? (y/n): ";
    string konfirmasi;
    getline(cin, konfirmasi);

    if (konfirmasi == "y" || konfirmasi == "Y") {
        for (int i = 0; i < isiKeranjang; i++) { // tar kita kurangi stok semua produk yang ada di keranjang
            int indeks = cariProduk(idKeranjang[i]);
            if (indeks != -1)
                daftarProduk[indeks].stokProduk -= jumlahKeranjang[i];
        }
        cout << "Pembelian berhasil! Terima kasih, " << usernameAktif << "!" << endl;
    } else {
        cout << "Pembelian dibatalkan." << endl;
    }
}

void menuUser(string usernameAktif) { // prosedur menu user, nanti looping sampai si pembeli pilih logout
    int pilihanUser;
    do {
        cout << "\n|==================================================|" << endl;
        cout << "|                  MENU PELANGGAN                  |" << endl;
        cout << "|==================================================|" << endl;
        cout << "| 1. Lihat Semua Produk                            |" << endl;
        cout << "| 2. Cari Produk                                   |" << endl;
        cout << "| 3. Beli Produk                                   |" << endl;
        cout << "| 4. Logout                                        |" << endl;
        cout << "|==================================================|" << endl;
        cout << "Pilih menu (1-4): ";
        pilihanUser = inputAngkaAman(); // biar gak infinite loop

        switch (pilihanUser) {
            case 1:
                lihatSemuaProduk();
                break;
            case 2: {
                cout << "\n--- CARI PRODUK ---" << endl;
                cout << "Kata kunci: ";
                string keyword;
                getline(cin, keyword);
                try {
                    cariProduk(keyword); // panggil overload stringnya yang pakai linear search
                } catch (const invalid_argument& e) {
                    cout << "[!] " << e.what() << endl;
                }
                break;
            }
            case 3:
                beliProduk(usernameAktif);
                break;
            case 4:
                cout << "Logout berhasil. Sampai jumpa, " << usernameAktif << "!" << endl;
                break;
            default:
                cout << "[!] Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihanUser != 4);
}

int main() { // ini main nya
    daftarPengguna[0] = {"syarifah", "2509106007", "admin"}; // adminnya itu ya saya sendiri dan pass nya itu nim saya
    jumlahPengguna = 1;
    jumlahProduk   = 0; // produk awalnya kosong
    idBerikutnya   = 1;

    string usernameAktif = "";
    string roleAktif     = "";
    int    pilihanAwal;

    do {
        cout << "\n|============================================================|" << endl;
        cout << "|     SELAMAT DATANG DI TOKO PERLENGKAPAN KUCING WHINGKY     |" << endl;
        cout << "|============================================================|" << endl;
        cout << "| 1. Login                                                   |" << endl;
        cout << "| 2. Register                                                |" << endl;
        cout << "| 3. Keluar                                                  |" << endl;
        cout << "|============================================================|" << endl;
        cout << "Pilih menu (1-3): ";
        pilihanAwal = inputAngkaAman(); // biar gak infinite loop lagi

        if (pilihanAwal == 1) {
            cout << "\n--- LOGIN ---" << endl;

            int  kesempatan = 0;
            bool loginOK    = false;

            do { // maksimal 3 kali percobaan ya buat loginnya
                kesempatan++;
                string usernameInput, passwordInput;
                cout << "Username : ";
                getline(cin, usernameInput);
                cout << "Password : ";
                getline(cin, passwordInput);

                loginOK = cekLogin(usernameInput, passwordInput, usernameAktif, roleAktif); // cekLogin pakai & untuk ubah nilai usernameAktif dan roleAktif langsung

                if (!loginOK)
                    cout << "Username/password anda salah, Sisa kesempatan mencoba: " << (3 - kesempatan) << "x" << endl;

            } while (!loginOK && kesempatan < 3);

            if (!loginOK) {
                cout << "Anda telah gagal login sebanyak 3 kali. Program otomatis dihentikan." << endl;
                return 0;
            }

            cout << "Login berhasil! Selamat datang, " << usernameAktif << "!" << endl;

            if (roleAktif == "admin") {
                menuAdmin(usernameAktif);
            } else {
                menuUser(usernameAktif);
            }

        } else if (pilihanAwal == 2) {
            prosesRegister();

        } else if (pilihanAwal == 3) {
            cout << "\n|==============================================|" << endl;
            cout << "| Terima kasih telah mengunjungi Toko Whingky! |" << endl;
            cout << "|==============================================|" << endl;

        } else {
            cout << "Pilihan anda tidak valid, silahkan masukkan pilihan 1, 2, atau 3." << endl;
        }

    } while (pilihanAwal != 3);

    return 0;
}