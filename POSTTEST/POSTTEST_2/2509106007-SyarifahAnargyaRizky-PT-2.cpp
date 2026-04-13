#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_PRODUK = 100; // kapasitas maksimal array produknya
const int MAX_USER   = 50;

struct Kategori { // nested struct buat kategori produknya
    string namaKategori;
};

struct Produk {
    int      idProduk;
    string   namaProduk;
    Kategori kategori; // nested struct di sini
    int      hargaProduk;
    int      stokProduk;
};

struct Pengguna { // struct buat multiuser
    string username;
    string password;
    string role; // sebagai admin atau user
};

Produk   daftarProduk[MAX_PRODUK];
int      jumlahProduk  = 0;
int      idBerikutnya  = 1;

Pengguna daftarPengguna[MAX_USER];
int      jumlahPengguna = 0;

int main() {

    // cuma ada akun admin yeah, tar regist sendiri usernya
    daftarPengguna[0].username = "syarifah";
    daftarPengguna[0].password = "2509106007";
    daftarPengguna[0].role     = "admin";
    jumlahPengguna = 1;

    string usernameAktif = "";
    string roleAktif     = "";
    int    pilihanAwal;

    do { // menu awalnya
        cout << "\n=====================================================" << endl;
        cout << "| SELAMAT DATANG DI TOKO PERLENGKAPAN KUCING WHINGKY |" << endl;
        cout << "======================================================" << endl;
        cout << "1. Login"   << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar"  << endl;
        cout << "Pilih menu (1-3): ";
        cin  >> pilihanAwal;
        cin.ignore(1000, '\n');

        if (pilihanAwal == 1) { // kita masuk ke proses login

            cout << "\n-------- LOGIN --------" << endl;

            string usernameInput, passwordInput;
            int  kesempatan = 0;
            bool loginOK    = false;

            do { // maksimal 3 kali percobaan disini, kalau gagal ya semua program berhenti
                kesempatan++;
                cout << "Username : ";
                getline(cin, usernameInput);
                cout << "Password : ";
                getline(cin, passwordInput);

                for (int indeks = 0; indeks < jumlahPengguna; indeks++) {
                    if (usernameInput == daftarPengguna[indeks].username &&
                        passwordInput == daftarPengguna[indeks].password) {
                        loginOK       = true;
                        usernameAktif = daftarPengguna[indeks].username;
                        roleAktif     = daftarPengguna[indeks].role;
                    }
                }

                if (!loginOK) {
                    cout << " Username atau password anda salah! Sisa percobaan: " << (3 - kesempatan) << "x" << endl;
                }

            } while (!loginOK && kesempatan < 3);

            if (!loginOK) {
                cout << "\n Login gagal 3 kali berturut-turut, program akan dihentikan." << endl;
                return 0;
            }

            cout << "\nSelamat datang, " << usernameAktif << "!" << endl;

            // cek role-nya admin atau user biasa
            if (roleAktif == "admin") {
                int pilihanAdmin;
                do {
                    cout << "\n=== MENU ADMIN ===" << endl;
                    cout << "1. Lihat Semua Produk" << endl;
                    cout << "2. Tambah Produk"      << endl;
                    cout << "3. Update Produk"      << endl;
                    cout << "4. Hapus Produk"       << endl;
                    cout << "5. Cari Produk"        << endl;
                    cout << "6. Logout"             << endl;
                    cout << "Pilih menu (1-6): ";
                    cin  >> pilihanAdmin;
                    cin.ignore(1000, '\n');

                    switch (pilihanAdmin) {

                        case 1: { // lihat semua produk dalam bentuk tabel
                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            if (jumlahProduk == 0) {
                                cout << "|                   Belum ada produk yang tersedia                    |" << endl;
                            } else {
                                for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                    cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                         << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                         << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                         << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                         << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                         << " |"  << endl;
                                }
                            }
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            break;
                        }

                        case 2: { // tambah produk baru ke daftar
                            cout << "\n--- TAMBAH PRODUK BARU ---" << endl;
                            if (jumlahProduk >= MAX_PRODUK) {
                                cout << " Kapasitas produk sudah penuh!" << endl;
                                break;
                            }

                            int posisiBaru = jumlahProduk;
                            daftarProduk[posisiBaru].idProduk = idBerikutnya++;

                            cout << "Nama Produk  : ";
                            getline(cin, daftarProduk[posisiBaru].namaProduk);
                            cout << "Kategori     : ";
                            getline(cin, daftarProduk[posisiBaru].kategori.namaKategori);
                            cout << "Harga (Rp)   : ";
                            cin  >> daftarProduk[posisiBaru].hargaProduk;
                            cin.ignore(1000, '\n');

                            do {
                                cout << "Stok         : ";
                                cin  >> daftarProduk[posisiBaru].stokProduk;
                                cin.ignore(1000, '\n');
                                if (daftarProduk[posisiBaru].stokProduk < 0)
                                    cout << " Stok tidak boleh negatif!" << endl;
                            } while (daftarProduk[posisiBaru].stokProduk < 0);

                            jumlahProduk++;
                            cout << "\n Produk '" << daftarProduk[posisiBaru].namaProduk
                                 << "' berhasil ditambahkan! (ID: " << daftarProduk[posisiBaru].idProduk << ")" << endl;
                            break;
                        }

                        case 3: { // update data produk yang sudah ada
                            cout << "\n--- UPDATE PRODUK ---" << endl;
                            if (jumlahProduk == 0) {
                                cout << " Belum ada produk." << endl;
                                break;
                            }

                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                     << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                     << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                     << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                     << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                     << " |"  << endl;
                            }
                            cout << "|====|===========================|==================|============|=======|" << endl;

                            cout << "ID produk yang ingin diupdate: ";
                            int idUpdate;
                            cin  >> idUpdate;
                            cin.ignore(1000, '\n');

                            bool ketemu = false;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                if (daftarProduk[indeks].idProduk == idUpdate) {
                                    ketemu = true;
                                    cout << "Produk ditemukan: " << daftarProduk[indeks].namaProduk << endl;
                                    cout << "1. Nama"     << endl;
                                    cout << "2. Kategori" << endl;
                                    cout << "3. Harga"    << endl;
                                    cout << "4. Stok"     << endl;
                                    cout << "Pilihan (1-4): ";
                                    int pilihan;
                                    cin  >> pilihan;
                                    cin.ignore(1000, '\n');

                                    if (pilihan == 1) {
                                        cout << "Nama baru: ";
                                        getline(cin, daftarProduk[indeks].namaProduk);
                                        cout << " Nama berhasil diupdate!" << endl;
                                    } else if (pilihan == 2) {
                                        cout << "Kategori baru: ";
                                        getline(cin, daftarProduk[indeks].kategori.namaKategori);
                                        cout << " Kategori berhasil diupdate!" << endl;
                                    } else if (pilihan == 3) {
                                        cout << "Harga baru (Rp): ";
                                        cin  >> daftarProduk[indeks].hargaProduk;
                                        cin.ignore(1000, '\n');
                                        cout << " Harga berhasil diupdate!" << endl;
                                    } else if (pilihan == 4) {
                                        int stokBaru;
                                        do {
                                            cout << "Stok baru: ";
                                            cin  >> stokBaru;
                                            cin.ignore(1000, '\n');
                                            if (stokBaru < 0)
                                                cout << " Stok tidak boleh negatif!" << endl;
                                        } while (stokBaru < 0);
                                        daftarProduk[indeks].stokProduk = stokBaru;
                                        cout << " Stok berhasil diupdate!" << endl;
                                    } else {
                                        cout << " Pilihan tidak valid!" << endl;
                                    }
                                    break;
                                }
                            }
                            if (!ketemu)
                                cout << " Produk dengan ID " << idUpdate << " tidak ditemukan!" << endl;
                            break;
                        }

                        case 4: { // hapus produk dari daftar
                            cout << "\n--- HAPUS PRODUK ---" << endl;
                            if (jumlahProduk == 0) {
                                cout << " Belum ada produk." << endl;
                                break;
                            }

                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                     << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                     << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                     << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                     << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                     << " |"  << endl;
                            }
                            cout << "|====|===========================|==================|============|=======|" << endl;

                            cout << "ID produk yang ingin dihapus: ";
                            int  idHapus;
                            cin  >> idHapus;
                            cin.ignore(1000, '\n');

                            bool ketemu     = false;
                            int  posisiHapus = -1;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                if (daftarProduk[indeks].idProduk == idHapus) {
                                    ketemu      = true;
                                    posisiHapus = indeks;
                                    break;
                                }
                            }

                            if (ketemu) {
                                cout << "Yakin ingin menghapus '" << daftarProduk[posisiHapus].namaProduk << "'? (y/n): ";
                                string konfirmasi;
                                getline(cin, konfirmasi);
                                if (konfirmasi == "y" || konfirmasi == "Y") {
                                    // geser array ke kiri supaya tidak ada celah kosongnya
                                    for (int indeks = posisiHapus; indeks < jumlahProduk - 1; indeks++) {
                                        daftarProduk[indeks] = daftarProduk[indeks + 1];
                                    }
                                    jumlahProduk--;
                                    cout << " Produk berhasil dihapus!" << endl;
                                } else {
                                    cout << " Penghapusan dibatalkan." << endl;
                                }
                            } else {
                                cout << " Produk dengan ID " << idHapus << " tidak ditemukan!" << endl;
                            }
                            break;
                        }

                        case 5: { // cari produk berdasarkan nama
                            cout << "\n--- CARI PRODUK ---" << endl;
                            cout << "Kata kunci: ";
                            string keyword;
                            getline(cin, keyword);

                            // ubah keyword jadi huruf kecil semua biar pencarian tidak case-sensitive
                            for (int posisiHuruf = 0; keyword[posisiHuruf] != '\0'; posisiHuruf++)
                                if (keyword[posisiHuruf] >= 'A' && keyword[posisiHuruf] <= 'Z')
                                    keyword[posisiHuruf] += 32;

                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;

                            bool ditemukan = false;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {

                                string namaCek = daftarProduk[indeks].namaProduk;
                                for (int posisiHuruf = 0; namaCek[posisiHuruf] != '\0'; posisiHuruf++)
                                    if (namaCek[posisiHuruf] >= 'A' && namaCek[posisiHuruf] <= 'Z')
                                        namaCek[posisiHuruf] += 32;

                                // cari keyword di dalam nama produk secara manual
                                bool cocok       = false;
                                int  panjangKw   = 0; // buat panjang keyword
                                int  panjangNama = 0; // buat panjang nama produk
                                for (int posisiHuruf = 0; keyword[posisiHuruf] != '\0'; posisiHuruf++) panjangKw++;
                                for (int posisiHuruf = 0; namaCek[posisiHuruf]  != '\0'; posisiHuruf++) panjangNama++;

                                for (int posisiMulai = 0; posisiMulai <= panjangNama - panjangKw && !cocok; posisiMulai++) {
                                    bool sama = true;
                                    for (int offset = 0; offset < panjangKw && sama; offset++) {
                                        if (namaCek[posisiMulai + offset] != keyword[offset]) sama = false;
                                    }
                                    if (sama) cocok = true;
                                }

                                if (cocok) {
                                    ditemukan = true;
                                    cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                         << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                         << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                         << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                         << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                         << " |"  << endl;
                                }
                            }
                            if (!ditemukan)
                                cout << "|                Produk yang anda cari tidak ditemukan!                |" << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            break;
                        }

                        case 6: { // logout dari akun admin
                            cout << "\nLogout berhasil. Sampai jumpa, " << usernameAktif << "!" << endl;
                            usernameAktif = "";
                            roleAktif     = "";
                            break;
                        }

                        default:
                            cout << " Pilihan tidak valid!" << endl;
                            break;
                    }
                } while (pilihanAdmin != 6);
            }

            else { // masuk ke menu user biasa
                int pilihanUser;
                do {
                    cout << "\n=== MENU PELANGGAN ===" << endl;
                    cout << "1. Lihat Semua Produk" << endl;
                    cout << "2. Cari Produk"        << endl;
                    cout << "3. Beli Produk"        << endl;
                    cout << "4. Logout"             << endl;
                    cout << "Pilih menu (1-4): ";
                    cin  >> pilihanUser;
                    cin.ignore(1000, '\n');

                    switch (pilihanUser) {

                        case 1: { // lihat semua produk yang tersedia
                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            if (jumlahProduk == 0) {
                                cout << "| Belum ada produk.                                                    |" << endl;
                            } else {
                                for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                    cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                         << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                         << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                         << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                         << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                         << " |"  << endl;
                                }
                            }
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            break;
                        }

                        case 2: { // cari produk berdasarkan kata kunci
                            cout << "\n--- CARI PRODUK ---" << endl;
                            cout << "Kata kunci nama produk: ";
                            string keyword;
                            getline(cin, keyword);

                            for (int posisiHuruf = 0; keyword[posisiHuruf] != '\0'; posisiHuruf++)
                                if (keyword[posisiHuruf] >= 'A' && keyword[posisiHuruf] <= 'Z')
                                    keyword[posisiHuruf] += 32;

                            cout << "\n";
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            cout << "| "  << left << setw(3)  << "ID"
                                 << "| "  << setw(25) << "Nama Produk"
                                 << " | " << setw(16) << "Kategori"
                                 << " | " << setw(10) << "Harga"
                                 << " | " << setw(5)  << "Stok"
                                 << " |"  << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;

                            bool ditemukan = false;
                            for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                string namaCek = daftarProduk[indeks].namaProduk;
                                for (int posisiHuruf = 0; namaCek[posisiHuruf] != '\0'; posisiHuruf++)
                                    if (namaCek[posisiHuruf] >= 'A' && namaCek[posisiHuruf] <= 'Z')
                                        namaCek[posisiHuruf] += 32;

                                bool cocok       = false;
                                int  panjangKw   = 0; // panjang keyword
                                int  panjangNama = 0; // panjang nama produk
                                for (int posisiHuruf = 0; keyword[posisiHuruf] != '\0'; posisiHuruf++) panjangKw++;
                                for (int posisiHuruf = 0; namaCek[posisiHuruf]  != '\0'; posisiHuruf++) panjangNama++;

                                for (int posisiMulai = 0; posisiMulai <= panjangNama - panjangKw && !cocok; posisiMulai++) {
                                    bool sama = true;
                                    for (int offset = 0; offset < panjangKw && sama; offset++) {
                                        if (namaCek[posisiMulai + offset] != keyword[offset]) sama = false;
                                    }
                                    if (sama) cocok = true;
                                }

                                if (cocok) {
                                    ditemukan = true;
                                    cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                         << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                         << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                         << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                         << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                         << " |"  << endl;
                                }
                            }
                            if (!ditemukan)
                                cout << "|                Produk yang anda cari tidak ditemukan!                |" << endl;
                            cout << "|====|===========================|==================|============|=======|" << endl;
                            break;
                        }

                        case 3: { // beli produk, bisa pilih lebih dari satu sekaligus
                            cout << "\n--- BELI PRODUK ---" << endl;

                            if (jumlahProduk == 0) {
                                cout << " Belum ada produk tersedia." << endl;
                                break;
                            }

                            // array buat nyimpan id dan jumlah produk yang mau dibeli
                            int  idKeranjang[MAX_PRODUK];
                            int  jumlahKeranjang[MAX_PRODUK];
                            int  isiKeranjang   = 0;
                            bool selesaiBelanja = false;

                            do { // looping sampai user pilih checkout
                                cout << "\n";
                                cout << "|====|===========================|==================|============|=======|" << endl;
                                cout << "| "  << left << setw(3)  << "ID"
                                     << "| "  << setw(25) << "Nama Produk"
                                     << " | " << setw(16) << "Kategori"
                                     << " | " << setw(10) << "Harga"
                                     << " | " << setw(5)  << "Stok"
                                     << " |"  << endl;
                                cout << "|====|===========================|==================|============|=======|" << endl;
                                for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                    cout << "| "  << left  << setw(3)  << daftarProduk[indeks].idProduk
                                         << "| "  << setw(25) << daftarProduk[indeks].namaProduk
                                         << " | " << setw(16) << daftarProduk[indeks].kategori.namaKategori
                                         << " |"  << right << setw(11) << ("Rp " + to_string(daftarProduk[indeks].hargaProduk))
                                         << " |"  << setw(6)  << daftarProduk[indeks].stokProduk
                                         << " |"  << endl;
                                }
                                cout << "|====|===========================|==================|============|=======|" << endl;

                                // tampilkan isi keranjang kalau sudah ada yang dipilih
                                if (isiKeranjang > 0) {
                                    cout << "\nKeranjang (" << isiKeranjang << " item):" << endl;
                                    for (int posisiKeranjang = 0; posisiKeranjang < isiKeranjang; posisiKeranjang++) {
                                        for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                            if (daftarProduk[indeks].idProduk == idKeranjang[posisiKeranjang]) {
                                                cout << "  - " << daftarProduk[indeks].namaProduk
                                                     << " x"  << jumlahKeranjang[posisiKeranjang]
                                                     << " = Rp " << (daftarProduk[indeks].hargaProduk * jumlahKeranjang[posisiKeranjang])
                                                     << endl;
                                            }
                                        }
                                    }
                                }

                                cout << "\nInput ID produk (input 0 untuk selesai dan checkout keranjang belanja): ";
                                int idBeli;
                                cin  >> idBeli;
                                cin.ignore(1000, '\n');

                                if (idBeli == 0) {
                                    selesaiBelanja = true;

                                } else {
                                    bool ketemu = false;
                                    for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                        if (daftarProduk[indeks].idProduk == idBeli) {
                                            ketemu = true;

                                            if (daftarProduk[indeks].stokProduk == 0) {
                                                cout << " Stok produk ini sudah habis!" << endl;
                                                break;
                                            }

                                            cout << " Produk : " << daftarProduk[indeks].namaProduk << endl;
                                            cout << " Stok   : " << daftarProduk[indeks].stokProduk << endl;
                                            cout << " Harga  : Rp " << daftarProduk[indeks].hargaProduk << endl;

                                            int jumlahBeli;
                                            do {
                                                cout << " Jumlah : ";
                                                cin  >> jumlahBeli;
                                                cin.ignore(1000, '\n');
                                                if (jumlahBeli <= 0)
                                                    cout << " Jumlah harus lebih dari 0!" << endl;
                                                else if (jumlahBeli > daftarProduk[indeks].stokProduk) {
                                                    cout << " Stok tidak cukup! Tersedia: "
                                                         << daftarProduk[indeks].stokProduk << endl;
                                                    jumlahBeli = 0;
                                                }
                                            } while (jumlahBeli <= 0);

                                            // cek kalau produk ini sudah ada di keranjang sebelumnya
                                            bool sudahDiKeranjang = false;
                                            for (int posisiKeranjang = 0; posisiKeranjang < isiKeranjang; posisiKeranjang++) {
                                                if (idKeranjang[posisiKeranjang] == idBeli) {
                                                    int totalNanti = jumlahKeranjang[posisiKeranjang] + jumlahBeli;
                                                    if (totalNanti > daftarProduk[indeks].stokProduk) {
                                                        cout << " Total melebihi stok! Maks yang bisa ditambah: "
                                                             << (daftarProduk[indeks].stokProduk - jumlahKeranjang[posisiKeranjang])
                                                             << endl;
                                                    } else {
                                                        jumlahKeranjang[posisiKeranjang] = totalNanti;
                                                        cout << " Jumlah diperbarui di keranjang!" << endl;
                                                    }
                                                    sudahDiKeranjang = true;
                                                    break;
                                                }
                                            }

                                            // kalau belum ada, tambahkan sebagai item baru
                                            if (!sudahDiKeranjang) {
                                                idKeranjang[isiKeranjang]     = idBeli;
                                                jumlahKeranjang[isiKeranjang] = jumlahBeli;
                                                isiKeranjang++;
                                                cout << " Ditambahkan ke keranjang!" << endl;
                                            }
                                            break;
                                        }
                                    }
                                    if (!ketemu)
                                        cout << " Produk dengan ID " << idBeli << " tidak ditemukan!" << endl;
                                }

                            } while (!selesaiBelanja);

                            // kalau keranjang masih kosong pas checkout, batalkan saja
                            if (isiKeranjang == 0) {
                                cout << "\n Keranjang kosong, pembelian dibatalkan." << endl;
                                break;
                            }

                            // hitung total belanja dari semua item di keranjang
                            int totalBelanja = 0;
                            for (int posisiKeranjang = 0; posisiKeranjang < isiKeranjang; posisiKeranjang++) {
                                for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                    if (daftarProduk[indeks].idProduk == idKeranjang[posisiKeranjang]) {
                                        totalBelanja += daftarProduk[indeks].hargaProduk * jumlahKeranjang[posisiKeranjang];
                                    }
                                }
                            }

                            // tampilkan struk pembelian
                            cout << "\n========== STRUK PEMBELIAN ==========" << endl;
                            cout << "Pembeli  : " << usernameAktif << endl;
                            cout << "-------------------------------------" << endl;
                            for (int posisiKeranjang = 0; posisiKeranjang < isiKeranjang; posisiKeranjang++) {
                                for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                    if (daftarProduk[indeks].idProduk == idKeranjang[posisiKeranjang]) {
                                        cout << "Produk   : " << daftarProduk[indeks].namaProduk << endl;
                                        cout << "Jumlah   : " << jumlahKeranjang[posisiKeranjang] << endl;
                                        cout << "Subtotal : Rp " << (daftarProduk[indeks].hargaProduk * jumlahKeranjang[posisiKeranjang]) << endl;
                                        cout << "-------------------------------------" << endl;
                                    }
                                }
                            }
                            cout << "TOTAL    : Rp " << totalBelanja << endl;
                            cout << "=====================================" << endl;

                            cout << "Konfirmasi pembelian? (y/n): ";
                            string konfirmasi;
                            getline(cin, konfirmasi);

                            if (konfirmasi == "y" || konfirmasi == "Y") {
                                // kurangi stok semua produk yang ada di keranjang
                                for (int posisiKeranjang = 0; posisiKeranjang < isiKeranjang; posisiKeranjang++) {
                                    for (int indeks = 0; indeks < jumlahProduk; indeks++) {
                                        if (daftarProduk[indeks].idProduk == idKeranjang[posisiKeranjang]) {
                                            daftarProduk[indeks].stokProduk -= jumlahKeranjang[posisiKeranjang];
                                        }
                                    }
                                }
                                cout << " Pembelian berhasil! Terima kasih, " << usernameAktif << "!" << endl;
                            } else {
                                cout << " Pembelian dibatalkan." << endl;
                            }
                            break;
                        }

                        case 4: { // logout dari akun user
                            cout << "\nLogout berhasil. Sampai jumpa, " << usernameAktif << "!" << endl;
                            usernameAktif = "";
                            roleAktif     = "";
                            break;
                        }

                        default:
                            cout << " Pilihan tidak valid!" << endl;
                            break;
                    }
                } while (pilihanUser != 4);
            }
        }

        else if (pilihanAwal == 2) { // menu register untuk buat akun baru
            cout << "\n--- REGISTER AKUN BARU ---" << endl;

            if (jumlahPengguna >= MAX_USER) {
                cout << " Kapasitas pengguna sudah penuh!" << endl;
            } else {
                string usernameBaru, passwordBaru;
                cout << "Username : ";
                getline(cin, usernameBaru);

                // cek dulu apakah username sudah dipakai orang lain
                bool sudahAda = false;
                for (int indeks = 0; indeks < jumlahPengguna; indeks++) {
                    if (daftarPengguna[indeks].username == usernameBaru) {
                        sudahAda = true;
                        break;
                    }
                }

                if (sudahAda) {
                    cout << " Username '" << usernameBaru << "' sudah digunakan!" << endl;
                } else {
                    cout << "Password : ";
                    getline(cin, passwordBaru);
                    daftarPengguna[jumlahPengguna].username = usernameBaru;
                    daftarPengguna[jumlahPengguna].password = passwordBaru;
                    daftarPengguna[jumlahPengguna].role     = "user";
                    jumlahPengguna++;
                    cout << "\n Registrasi berhasil! Akun '" << usernameBaru << "' dibuat. Silakan login!" << endl;
                }
            }
        }

        else if (pilihanAwal == 3) { // keluar dari program
            cout << "\nTerima kasih telah mengunjungi Toko Whingky!" << endl;
        }

        else {
            cout << " Pilihan tidak valid! Masukkan 1, 2, atau 3." << endl;
        }

    } while (pilihanAwal != 3);

    return 0;
}