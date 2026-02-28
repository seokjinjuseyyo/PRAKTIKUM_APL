#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Fungsi buat ngebersihin layar
void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi biar mudah nampilin si garis pemisahnya 
void tampilkanGaris() {
    cout << "=================================================" << endl;
}

// Fungsi buat nampilin headernya biar cakep
void tampilkanHeader() {
    tampilkanGaris();
    cout << "|        PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
    cout << "|          Algoritma Pemrograman Dasar          |" << endl;
    tampilkanGaris();
}

// Fungsi untuk proses login
// Mengembalikan true jika login berhasil, false jika gagal 3 kali
bool prosesLogin() {
    string nama;       //untuk nyimpan nama usernya
    string password;   // variabel untuk menyimpan password (3 digit terakhir NIM)
    int percobaan = 0; // variabel untuk menghitung percobaan login

    // Data login yang valid
    string namaValid = "syarifah";
    string passwordValid = "007"; // 3 digit terakhir NIM 2509106007

    while (percobaan < 3) {
        bersihkanLayar();
        tampilkanHeader();
        cout << endl;
        cout << "  ===== HALAMAN LOGIN =====" << endl;
        cout << endl;
        cout << "  Percobaan ke-" << (percobaan + 1) << " dari 3" << endl;
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

    // Jika sudah 3 kali gagal
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

// Fungsi untuk konversi jam ke menit dan detik
void konversiJam() {
    double inputJam;     // variabel untuk menyimpan nilai jam yang diinput
    double hasilMenit;   // variabel untuk menyimpan hasil konversi ke menit
    double hasilDetik;   // variabel untuk menyimpan hasil konversi ke detik

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "  ===== KONVERSI JAM ke MENIT & DETIK =====" << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam JAM : ";
    cin >> inputJam;

    // Rumus konversi
    hasilMenit = inputJam * 60;
    hasilDetik = inputJam * 3600;

    cout << endl;
    cout << "  ----- HASIL KONVERSI -----" << endl;
    cout << "  " << inputJam << " Jam = " << hasilMenit << " Menit" << endl;
    cout << "  " << inputJam << " Jam = " << hasilDetik << " Detik" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk konversi menit ke jam dan detik
void konversiMenit() {
    double inputMenit;   // variabel untuk menyimpan nilai menit yang diinput
    double hasilJam;     // variabel untuk menyimpan hasil konversi ke jam
    double hasilDetik;   // variabel untuk menyimpan hasil konversi ke detik

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "  ===== KONVERSI MENIT ke JAM & DETIK =====" << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam MENIT : ";
    cin >> inputMenit;

    // Rumus konversi
    hasilJam   = inputMenit / 60;
    hasilDetik = inputMenit * 60;

    cout << endl;
    cout << "  ----- HASIL KONVERSI -----" << endl;
    cout << "  " << inputMenit << " Menit = " << hasilJam << " Jam" << endl;
    cout << "  " << inputMenit << " Menit = " << hasilDetik << " Detik" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk konversi detik ke jam dan menit
void konversiDetik() {
    double inputDetik;   // variabel untuk menyimpan nilai detik yang diinput
    double hasilJam;     // variabel untuk menyimpan hasil konversi ke jam
    double hasilMenit;   // variabel untuk menyimpan hasil konversi ke menit

    bersihkanLayar();
    tampilkanHeader();
    cout << endl;
    cout << "  ===== KONVERSI DETIK ke JAM & MENIT =====" << endl;
    cout << endl;
    cout << "  Masukkan nilai waktu dalam DETIK : ";
    cin >> inputDetik;

    // Rumus konversi
    hasilJam   = inputDetik / 3600;
    hasilMenit = inputDetik / 60;

    cout << endl;
    cout << "  ----- HASIL KONVERSI -----" << endl;
    cout << "  " << inputDetik << " Detik = " << hasilJam << " Jam" << endl;
    cout << "  " << inputDetik << " Detik = " << hasilMenit << " Menit" << endl;
    cout << endl;
    tampilkanGaris();
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk menampilkan menu utama dan menangani pilihan user
void tampilkanMenuUtama() {
    string pilihanMenu; // variabel untuk menyimpan pilihan menu dari user
    bool programBerjalan = true; // variabel untuk mengontrol looping program

    while (programBerjalan) {
        bersihkanLayar();
        tampilkanHeader();
        cout << endl;
        cout << "  ===== MENU UTAMA =====" << endl;
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