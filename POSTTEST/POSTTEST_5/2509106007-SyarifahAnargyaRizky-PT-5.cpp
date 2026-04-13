#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_PRODUK = 100; // kapasitas maksimal array buat produk
const int MAX_USER   = 50;  // kapasitas maksimal array buat pengguna

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

Produk   daftarProduk[MAX_PRODUK]; // variabel global array produknya
int      jumlahProduk = 0;
int      idBerikutnya = 1;

Pengguna daftarPengguna[MAX_USER]; // variabel global array penggunanya
int      jumlahPengguna = 0;

void cetakGaris();
void cetakGarisBaris();
void cetakHeaderTabel();
void cetakBarisProduk(Produk *produkPtr); // pakai pointer ke struct Produk
void cetakTabelProduk();

int  hitungTotalBelanja(int idKeranjang[], int jumlahKeranjang[], int isiKeranjang, int indeks);

int  cariProduk(int idCari);        // buat nyari berdasarkan ID
void cariProduk(string keyword);    // buat nyari berdasarkan keyword nama

bool cekLogin(string usernameInput, string passwordInput, string &usernameAktif, string &roleAktif); // & sebagai parameter referensi
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

const int LEBAR_ID    = 4;  // lebar kolom ID
const int LEBAR_NAMA  = 25; // lebar kolom Nama Produk
const int LEBAR_KAT   = 16; // lebar kolom Kategori
const int LEBAR_HARGA = 10; // lebar kolom Harga
const int LEBAR_STOK  = 5;  // lebar kolom Stok

int inputAngka() { // biar gak infinity loop kalau input bukan angka
    int nilai;
    while (!(cin >> nilai)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid, masukkan angka: ";
    }
    cin.ignore(1000, '\n');
    return nilai;
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

void cetakBarisProduk(Produk *produkPtr) { // * sebagai parameter fungsi 
    string namaTampil = produkPtr->namaProduk; // akses field pakai arrow operator karena pointer
    if ((int)namaTampil.size() > LEBAR_NAMA)
        namaTampil = namaTampil.substr(0, LEBAR_NAMA);

    string katTampil = produkPtr->kategori.namaKategori; // akses nested struct lewat pointer
    if ((int)katTampil.size() > LEBAR_KAT)
        katTampil = katTampil.substr(0, LEBAR_KAT);

    string hargaStr = "Rp " + to_string(produkPtr->hargaProduk); // akses harganya lewat pointer

    cout << "| " << left << setw(LEBAR_ID)        << produkPtr->idProduk
         << " | " << left << setw(LEBAR_NAMA)      << namaTampil
         << " | " << left << setw(LEBAR_KAT)       << katTampil
         << " | " << left << setw(LEBAR_HARGA + 3) << hargaStr
         << " | " << left << setw(LEBAR_STOK)      << produkPtr->stokProduk
         << " |" << endl;
}

void cetakTabelProduk() { // prosedur buat nyetak tabelnya biar rapi
    cetakHeaderTabel();
    if (jumlahProduk == 0) {
        cout << "| Belum ada produk yang tersedia.                                      |" << endl;
    } else {
        for (int i = 0; i < jumlahProduk; i++) {
            cetakBarisProduk(&daftarProduk[i]); // kirim alamat elemen array pakai &
            if (i < jumlahProduk - 1) cetakGarisBaris();
        }
    }
    cetakGaris();
}

int hitungTotalBelanja(int idKeranjang[], int jumlahKeranjang[], int isiKeranjang, int indeks) {
    if (indeks >= isiKeranjang) return 0; 

    int subtotal = 0; // kita cari harga produk berdasarkan id di keranjang
    for (int j = 0; j < jumlahProduk; j++) {
        if (daftarProduk[j].idProduk == idKeranjang[indeks]) {
            subtotal = daftarProduk[j].hargaProduk * jumlahKeranjang[indeks];
            break;
        }
    }
    return subtotal + hitungTotalBelanja(idKeranjang, jumlahKeranjang, isiKeranjang, indeks + 1); // subtotal item ini ditambah total semua item setelahnya
}

int cariProduk(int idCari) { // ini buat kita nyari berdasarkan ID, return indeks atau -1 kalau gak ketemu nantinya
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].idProduk == idCari) return i;
    }
    return -1;
}

void cariProduk(string keyword) { // ini buat nyari berdasarkan keyword nama produk
    for (int j = 0; keyword[j] != '\0'; j++) // ubah keyword ke huruf kecil semua biar gak sensitive
        if (keyword[j] >= 'A' && keyword[j] <= 'Z') keyword[j] += 32;

    cetakHeaderTabel();
    bool adaHasil = false;

    for (int i = 0; i < jumlahProduk; i++) {
        string namaCek = daftarProduk[i].namaProduk; // ubah nama produk ke lowercase biar bisa kita bandingkan
        for (int j = 0; namaCek[j] != '\0'; j++)
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
            cetakBarisProduk(&daftarProduk[i]); // kirim alamat pakai &
            adaHasil = true;
        }
    }

    if (!adaHasil)
        cout << "| Produk yang anda cari tidak ditemukan.                               |" << endl;
    cetakGaris();
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

    if (jumlahPengguna >= MAX_USER) {
        cout << "Kapasitas pengguna sudah penuh!" << endl;
        return;
    }

    string usernameBaru, passwordBaru;
    cout << "Username : ";
    getline(cin, usernameBaru);

    bool sudahAda = false; // cek dulu apakah username sudah dipakaikah belum
    for (int i = 0; i < jumlahPengguna; i++) {
        if (daftarPengguna[i].username == usernameBaru) {
            sudahAda = true;
            break;
        }
    }

    if (sudahAda) {
        cout << "Username sudah digunakan, coba cari username yang lain yah." << endl;
        return;
    }

    cout << "Password : ";
    getline(cin, passwordBaru);

    daftarPengguna[jumlahPengguna].username = usernameBaru;
    daftarPengguna[jumlahPengguna].password = passwordBaru;
    daftarPengguna[jumlahPengguna].role     = "user";
    jumlahPengguna++;

    cout << "Registrasi anda berhasil! Silahkan login." << endl;
}

void lihatSemuaProduk() { // prosedur buat nampilin semua produk dalam bentuk tabel
    cout << "\n--- DAFTAR SEMUA PRODUK ---" << endl;
    cetakTabelProduk();
}

void tambahProduk() { // prosedur buat tambah produk baru ke array daftarProduk
    cout << "\n--- TAMBAH PRODUK BARU ---" << endl;

    if (jumlahProduk >= MAX_PRODUK) {
        cout << "Kapasitas produk sudah penuh." << endl;
        return;
    }

    int indeksBaru = jumlahProduk;
    daftarProduk[indeksBaru].idProduk = idBerikutnya++;

    cout << "Nama Produk : ";
    getline(cin, daftarProduk[indeksBaru].namaProduk);
    cout << "Kategori    : ";
    getline(cin, daftarProduk[indeksBaru].kategori.namaKategori);
    cout << "Harga (Rp)  : ";
    daftarProduk[indeksBaru].hargaProduk = inputAngka();

    do { // stok tidak boleh negatif, kalau salah suruh input ulang pembelinya
        cout << "Stok        : ";
        daftarProduk[indeksBaru].stokProduk = inputAngka();
        if (daftarProduk[indeksBaru].stokProduk < 0)
            cout << "Stok tidak boleh negatif, masukkan ulang." << endl;
    } while (daftarProduk[indeksBaru].stokProduk < 0);

    jumlahProduk++;
    cout << "Produk berhasil ditambahkan dengan ID: " << daftarProduk[indeksBaru].idProduk << endl;
}

void updateProduk() { // prosedur update salah satu field produk berdasarkan ID nya
    cout << "\n--- UPDATE PRODUK ---" << endl;
    cetakTabelProduk();

    if (jumlahProduk == 0) return;

    cout << "ID produk yang ingin diupdate: ";
    int idUpdate = inputAngka();

    int indeks = cariProduk(idUpdate); // pakai overload int untuk cari berdasarkan ID nya
    if (indeks == -1) {
        cout << "Produk dengan ID " << idUpdate << " tidak ditemukan." << endl;
        return;
    }

    cout << "Produk ditemukan: " << daftarProduk[indeks].namaProduk << endl;
    cout << " 1. Nama" << endl;
    cout << " 2. Kategori" << endl;
    cout << " 3. Harga" << endl;
    cout << " 4. Stok" << endl;
    cout << "Field yang ingin diupdate (1-4): ";
    int pilihanField = inputAngka();

    if (pilihanField == 1) {
        cout << "Nama baru: ";
        getline(cin, daftarProduk[indeks].namaProduk);
        cout << "Nama berhasil diupdate." << endl;
    } else if (pilihanField == 2) {
        cout << "Kategori baru: ";
        getline(cin, daftarProduk[indeks].kategori.namaKategori);
        cout << "Kategori berhasil diupdate." << endl;
    } else if (pilihanField == 3) {
        cout << "Harga baru (Rp): ";
        daftarProduk[indeks].hargaProduk = inputAngka();
        cout << "Harga berhasil diupdate." << endl;
    } else if (pilihanField == 4) {
        int stokBaru;
        do {
            cout << "Stok baru: ";
            stokBaru = inputAngka();
            if (stokBaru < 0) cout << "Stok tidak boleh negatif." << endl;
        } while (stokBaru < 0);
        daftarProduk[indeks].stokProduk = stokBaru;
        cout << "Stok berhasil diupdate." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

void hapusProduk() { // prosedur hapus produk berdasarkan ID nya
    cout << "\n--- HAPUS PRODUK ---" << endl;
    cetakTabelProduk();

    if (jumlahProduk == 0) return;

    cout << "ID produk yang ingin dihapus: ";
    int idHapus = inputAngka();

    int indeks = cariProduk(idHapus);
    if (indeks == -1) {
        cout << "Produk dengan ID " << idHapus << " tidak ditemukan." << endl;
        return;
    }

    cout << "Yakin hapus '" << daftarProduk[indeks].namaProduk << "'? (y/n): ";
    string konfirmasi;
    getline(cin, konfirmasi);

    if (konfirmasi == "y" || konfirmasi == "Y") {
        for (int i = indeks; i < jumlahProduk - 1; i++) { // geser semua elemen ke kiritrus  mulai dari posisi yang dihapus
            daftarProduk[i] = daftarProduk[i + 1];
        }
        jumlahProduk--;
        cout << "Produk berhasil dihapus." << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}

void cariProdukAdmin() { // prosedur buat cari produk di menu admin
    cout << "\n--- CARI PRODUK ---" << endl;
    cout << "Kata kunci: ";
    string keyword;
    getline(cin, keyword);
    cariProduk(keyword); // panggil overload stringnya
}

// Selection Sort buat ngurutin nama produk ascending (A ke Z)
void selectionSortNama() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int indeksMin = i; // anggap elemen sekarang yang paling kecil dulu
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (daftarProduk[j].namaProduk < daftarProduk[indeksMin].namaProduk)
                indeksMin = j; // simpan indeks yang namanya lebih kecil
        }
        if (indeksMin != i) { // kalau ketemu yang lebih kecil baru ditukar
            Produk temp          = daftarProduk[i];
            daftarProduk[i]      = daftarProduk[indeksMin];
            daftarProduk[indeksMin] = temp;
        }
    }
}

// Bubble Sort buat ngurutin harga descending (dari yang termahal ke termurah)
void bubbleSortHargaDesc() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (daftarProduk[j].hargaProduk < daftarProduk[j + 1].hargaProduk) { // kalau kiri lebih kecil dari kanan, ya kita tukar
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
        Produk key = daftarProduk[i]; // ambil elemen yang sekarang sebagai kunci
        int j = i - 1;
        while (j >= 0 && daftarProduk[j].stokProduk > key.stokProduk) { // geser elemen yang stoknya lebih besar ke kanan
            daftarProduk[j + 1] = daftarProduk[j];
            j--;
        }
        daftarProduk[j + 1] = key; // sisipkan key nya di posisi yang benar
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
    int pilihanSort = inputAngka();

    if (pilihanSort == 1) {
        selectionSortNama();
        cout << "Produk berhasil diurutkan berdasarkan nama (A-Z)!" << endl;
        cetakTabelProduk();
    } else if (pilihanSort == 2) {
        bubbleSortHargaDesc();
        cout << "Produk berhasil diurutkan berdasarkan harga (termahal ke termurah)!" << endl;
        cetakTabelProduk();
    } else if (pilihanSort == 3) {
        insertionSortStokAsc();
        cout << "Produk berhasil diurutkan berdasarkan stok (tersedikit ke terbanyak)!" << endl;
        cetakTabelProduk();
    } else {
        cout << "Pilihan tidak valid." << endl;
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
        pilihanAdmin = inputAngka(); // biar gak infinite loop

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
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihanAdmin != 7);
}

void beliProduk(string usernameAktif) { // prosedur proses belanjanya user
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
        int idBeli = inputAngka(); 

        if (idBeli == 0) {
            selesaiBelanja = true;
        } else {
            int indeks = cariProduk(idBeli);

            if (indeks == -1) {
                cout << "Produk tidak ditemukan." << endl;
            } else if (daftarProduk[indeks].stokProduk == 0) {
                cout << "Stok produk ini habis." << endl;
            } else {
                cout << "  Produk : " << daftarProduk[indeks].namaProduk << endl;
                cout << "  Stok   : " << daftarProduk[indeks].stokProduk << endl;
                cout << "  Harga  : Rp " << daftarProduk[indeks].hargaProduk << endl;

                int jumlahBeli; // input jumlah beli, gak boleh lebih dari stok
                do {
                    cout << "  Jumlah : ";
                    jumlahBeli = inputAngka(); 
                    if (jumlahBeli <= 0)
                        cout << "Jumlah harus lebih dari 0." << endl;
                    else if (jumlahBeli > daftarProduk[indeks].stokProduk) {
                        cout << "Stok tidak cukup. Tersedia: " << daftarProduk[indeks].stokProduk << endl;
                        jumlahBeli = 0;
                    }
                } while (jumlahBeli <= 0);

                bool sudahDiKeranjang = false; // kita cek apakah produknya sudah ada di keranjang
                for (int k = 0; k < isiKeranjang; k++) {
                    if (idKeranjang[k] == idBeli) {
                        int totalNanti = jumlahKeranjang[k] + jumlahBeli;
                        if (totalNanti > daftarProduk[indeks].stokProduk) {
                            cout << "Total melebihi stok. Maksimal tambah: "
                                 << (daftarProduk[indeks].stokProduk - jumlahKeranjang[k]) << endl;
                        } else {
                            jumlahKeranjang[k] = totalNanti;
                            cout << "Jumlah di keranjang diperbarui." << endl;
                        }
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
    string judul  = "STRUK PEMBELIAN";
    int padding = (LEBAR_STRUK - (int)judul.size()) / 2;
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
        pilihanUser = inputAngka(); // biar gak infinite loop

        switch (pilihanUser) {
            case 1:
                lihatSemuaProduk();
                break;
            case 2: {
                cout << "\n--- CARI PRODUK ---" << endl;
                cout << "Kata kunci: ";
                string keyword;
                getline(cin, keyword);
                cariProduk(keyword); // panggil overload stringnya
                break;
            }
            case 3:
                beliProduk(usernameAktif);
                break;
            case 4:
                cout << "Logout berhasil. Sampai jumpa, " << usernameAktif << "!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
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
        pilihanAwal = inputAngka(); // biar gak infinite loop lagi

        if (pilihanAwal == 1) {
            cout << "\n--- LOGIN ---" << endl;

            int  kesempatan = 0;
            bool loginOK    = false;

            do { // maksimal 3 kali percobaan loginnya
                kesempatan++;
                string usernameInput, passwordInput;
                cout << "Username : ";
                getline(cin, usernameInput);
                cout << "Password : ";
                getline(cin, passwordInput);

                loginOK = cekLogin(usernameInput, passwordInput, usernameAktif, roleAktif); // cekLogin pakai & untuk ubah nilai usernameAktif dan roleAktif langsung

                if (!loginOK)
                    cout << "Username/password anda salah. Sisa kesempatan: " << (3 - kesempatan) << "x" << endl;

            } while (!loginOK && kesempatan < 3);

            if (!loginOK) {
                cout << "Login gagal 3 kali. Program dihentikan." << endl;
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
            cout << "Pilihan tidak valid, silahkan masukkan pilihan 1, 2, atau 3." << endl;
        }

    } while (pilihanAwal != 3);

    return 0;
}