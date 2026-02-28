#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Fungsi buat ngebersihin layar
void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else

    #endif
}

// Fungsi biar mudah nampilin si garis pemisahnya nanti
void tampilkanGaris() {
    cout << "=================================================" << endl;
}

// Fungsi buat nampilin headernya biar cakep
void tampilkanHeader() {
    tampilkanGaris();
    cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
    cout << "|          Algoritma Pemrograman Dasar          |" << endl;
    tampilkanGaris();
}

// Fungsi untuk proses login
// Mengembalikan true jika login berhasil, false jika gagal 3 kali
bool prosesLogin() {
    string nama;       //untuk nyimpan nama usernya
    string password;   // untuk kita nyimpan si 3 digit nim itu
    int percobaan = 0; // untuk ngitung udah berapa kali login

    // Data login yang valid atau bener
    string namaValid = "syarifah";
    string passwordValid = "007"; // ini 3 digit nim yang dimau

    while (percobaan < 3) {
        bersihkanLayar();
        tampilkanHeader();
        cout << endl;
        cout << "   ===== SELAMAT DATANG DI HALAMAN LOGIN =====    " << endl;
        cout << endl;
        cout << "  Ini percobaan ke-" << (percobaan + 1) << " dari 3 kesempatan percobaan" << endl;
        cout << endl;
        cout << "  Nama     : ";
        cin >> nama;
        cout << "  Password : ";
        cin >> password;

        if (nama == namaValid && password == passwordValid) {
            cout << endl;
            cout << "  Login berhasil! Selamat datang, " << nama << "!" << endl;
            cout << endl;
            tampilkanGaris();
            cout << "  Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            return true;
        } else {
            percobaan++;
            if (percobaan < 3) {
                cout << endl;
                cout << "  Nama atau password salah! Sisa percobaan: " << (3 - percobaan) << endl;
                cout << "  Tekan Enter untuk mencoba lagi...";
                cin.ignore();
                cin.get();
            }
        }
    }

    // Nahh kalau sudah 3 kali salah maka akan dinyatakan gagal yaa
    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "  AKSES DITOLAK!" << endl;
    cout << "  Anda telah gagal login sebanyak 3 kali." << endl;
    cout << "  Program dihentikan." << endl;
    cout << endl;
    tampilkanGaris();
    return false;
}

// Fungsi buat kita konversi dari jam ke menit dan detik
void konversiJam() {
    double inputJam;     // untuk menyimpan nilai jam yang diinput sama user nanti
    double hasilMenit;   // untuk menyimpan hasil konversinya ke menit
    double hasilDetik;   // untuk menyimpan hasil konversinya ke detik

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "   ========= KONVERSI JAM ke MENIT & DETIK ==========   " << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam JAM : ";
    cin >> inputJam;

    // Ini buat rumus konversinya
    hasilMenit = inputJam * 60;
    hasilDetik = inputJam * 3600;

    cout << endl;
    cout << "  -------------- HASIL KONVERSI --------------  " << endl;
    cout << "  " << inputJam << " Jam = " << hasilMenit << " Menit" << endl;
    cout << "  " << inputJam << " Jam = " << hasilDetik << " Detik" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk konversi dari menit ke jam dan detik
void konversiMenit() {
    double inputMenit;   // untuk menyimpan nilai menit yang diinput sama user nanti
    double hasilJam;     // untuk menyimpan hasil konversinya ke jam
    double hasilDetik;   // untuk menyimpan hasil konversinya ke detik

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "   ========= KONVERSI MENIT ke JAM & DETIK ==========   " << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam MENIT : ";
    cin >> inputMenit;

    // Rumus konversinya
    hasilJam   = inputMenit / 60;
    hasilDetik = inputMenit * 60;

    cout << endl;
    cout << "  -------------- HASIL KONVERSI --------------  " << endl;
    cout << "  " << inputMenit << " Menit = " << hasilJam << " Jam" << endl;
    cout << "  " << inputMenit << " Menit = " << hasilDetik << " Detik" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk konversi dari detik ke jam dan menit
void konversiDetik() {
    double inputDetik;   // untuk menyimpan nilai detik yang diinput oleh user nantinya
    double hasilJam;     // untuk menyimpan hasil konversi ke jam
    double hasilMenit;   // untuk menyimpan hasil konversi ke menit

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "   ========= KONVERSI DETIK ke JAM & MENIT ==========   " << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam DETIK : ";
    cin >> inputDetik;

    // Rumus konversinya
    hasilJam   = inputDetik / 3600;
    hasilMenit = inputDetik / 60;

    cout << endl;
    cout << "  -------------- HASIL KONVERSI --------------  " << endl;
    cout << "  " << inputDetik << " Detik = " << hasilJam << " Jam" << endl;
    cout << "  " << inputDetik << " Detik = " << hasilMenit << " Menit" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi buat nampilin menu utama dan ngurusin pilihan user
void tampilkanMenuUtama() {
    string pilihanMenu; // untuk nyimpan pilihan menu dari user
    bool programBerjalan = true; // untuk kontrol looping program 

    while (programBerjalan) {
        bersihkanLayar();
        tampilkanHeader();
        cout << endl;
        cout << "  ================= MENU UTAMA ================  " << endl;
        cout << endl;
        cout << "  1. Konversi Jam    -> Menit dan Detik" << endl;
        cout << "  2. Konversi Menit  -> Jam dan Detik" << endl;
        cout << "  3. Konversi Detik  -> Jam dan Menit" << endl;
        cout << "  4. Keluar" << endl;
        cout << endl;
        tampilkanGaris();
        cout << "  Pilih menu (1-4) : ";
        cin >> pilihanMenu;

        if (pilihanMenu == "1") {
            konversiJam();
        } else if (pilihanMenu == "2") {
            konversiMenit();
        } else if (pilihanMenu == "3") {
            konversiDetik();
        } else if (pilihanMenu == "4") {
            bersihkanLayar();
            tampilkanHeader();
            cout << endl;
            cout << "  Terima kasih sudah menggunakan program ini!" << endl;
            cout << "  Program selesai." << endl;
            cout << endl;
            tampilkanGaris();
            programBerjalan = false;
        } else {
            cout << endl;
            cout << "  Pilihan tidak valid! Masukkan angka 1-4." << endl;
            cout << "  Tekan Enter untuk mencoba lagi...";
            cin.ignore();
            cin.get();
        }
    }
}

int main() {
    bool loginBerhasil; // untuk kita simpan status loginnya

    // Proses loginnya terlebih dahulu
    loginBerhasil = prosesLogin();

    // Jika login sudah berhasil, maka kita tampilkan menu utama
    if (loginBerhasil) {
        tampilkanMenuUtama();
    }

    return 0;
}