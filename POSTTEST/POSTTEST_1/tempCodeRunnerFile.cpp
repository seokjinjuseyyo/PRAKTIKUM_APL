#include <iostream>
#include <string>
using namespace std;

int main() {
    // variabel buat login
    string nama;
    string password;
    int percobaan = 0;
    string namaValid = "syarifah";
    string passwordValid = "007";
    bool loginBerhasil = false;

    // ini buat proses login nya 
    while (percobaan < 3) {
        cout << "=================================================" << endl;
        cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
        cout << "|          Algoritma Pemrograman Dasar          |" << endl;
        cout << "=================================================" << endl;
        cout << endl;
        cout << "   ===== SELAMAT DATANG DI HALAMAN LOGIN =====    " << endl;
        cout << endl;
        cout << "  Ini percobaan ke-" << (percobaan + 1) << " dari 3 kesempatan" << endl;
        cout << endl;
        cout << "  Nama     : ";
        cin >> nama;
        cout << "  Password : ";
        cin >> password;

        if (nama == namaValid && password == passwordValid) { // disini diliat bener gak nama sama pass nya 
            cout << endl;
            cout << "  Login berhasil! Selamat datang, " << nama << "!" << endl; 
            cout << endl;
            cout << "=================================================" << endl;
            cout << "  Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            loginBerhasil = true;
            percobaan = 3; // kalau dah sampai 3kali coba kita keluar dari loop
        } else {
            percobaan++;
            if (percobaan < 3) { // kalau belum sampai 3kali ya jalan terus programnya
                cout << endl;
                cout << "  Nama atau passwordnya salah! Sisa percobaan: " << (3 - percobaan) << endl;
                cout << "  Tekan Enter untuk mencoba lagi...";
                cin.ignore();
                cin.get();
            }
        }
    }

    // kalau login nya gagal tar keluar output beserta program yang langsung berhenti
    if (loginBerhasil == false) {
        cout << endl;
        cout << "  AKSES DITOLAK!" << endl;
        cout << "  Anda telah gagal login sebanyak 3 kali" << endl;
        cout << "  Program dihentikan." << endl;
        cout << endl;
        cout << "=================================================" << endl;
        return 0;
    }

    string pilihanMenu;
    bool programBerjalan = true;

    while (programBerjalan) {
        cout << "=================================================" << endl;
        cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
        cout << "|          Algoritma Pemrograman Dasar          |" << endl;
        cout << "=================================================" << endl;
        cout << endl;
        cout << "  ================= MENU UTAMA ================  " << endl;
        cout << endl;
        cout << "  1. Konversi Jam    menjadi Menit dan Detik" << endl;
        cout << "  2. Konversi Menit  menjadi Jam dan Detik" << endl;
        cout << "  3. Konversi Detik  menjadi Jam dan Menit" << endl;
        cout << "  4. Keluar" << endl;
        cout << endl;
        cout << "=================================================" << endl;
        cout << "  Pilihlah menu (1-4) : ";
        cin >> pilihanMenu;

        // pilihan paling awal yaitu 1 untuk konversi dari jam jadi menit dan detik
        if (pilihanMenu == "1") {
            double inputJam;
            double hasilMenit;
            double hasilDetik;
            bool inputValid = false;

            cout << "=================================================" << endl;
            cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
            cout << "|          Algoritma Pemrograman Dasar          |" << endl;
            cout << "=================================================" << endl;
            cout << endl;
            cout << "========= KONVERSI JAM ke MENIT & DETIK =========" << endl;
            cout << endl;

            while (!inputValid) {
                cout << "  Masukkan nilai waktu dalam JAM : ";
                cin >> inputJam;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl;
                    cout << "  ERROR: Input tidak valid! Masukkan angka." << endl;
                    cout << endl;
                } else if (inputJam < 0) {
                    cout << endl;
                    cout << "  ERROR: Waktunya tidak boleh negatif!" << endl;
                    cout << endl;
                } else {
                    inputValid = true;
                }
            }

            hasilMenit = inputJam * 60;
            hasilDetik = inputJam * 3600;

            cout << endl;
            cout << "  -------------- HASIL KONVERSI --------------  " << endl;
            cout << "  " << inputJam << " Jam = " << hasilMenit << " Menit" << endl;
            cout << "  " << inputJam << " Jam = " << hasilDetik << " Detik" << endl;
            cout << endl;
            cout << "=================================================" << endl;
            cout << "  Tekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();

        // pilihan yang ke 2 itu untuk konversi dari menit yang mau diubah ke jam dan detik
        } else if (pilihanMenu == "2") {
            double inputMenit;
            double hasilJam;
            double hasilDetik;
            bool inputValid = false;

            cout << "=================================================" << endl;
            cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
            cout << "|          Algoritma Pemrograman Dasar          |" << endl;
            cout << "=================================================" << endl;
            cout << endl;
            cout << "========= KONVERSI MENIT ke JAM & DETIK =========" << endl;
            cout << endl;

            while (!inputValid) {
                cout << "  Masukkan nilai waktu dalam MENIT : ";
                cin >> inputMenit;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl;
                    cout << "  ERROR: Input tidak valid! Masukkan angka." << endl;
                    cout << endl;
                } else if (inputMenit < 0) {
                    cout << endl;
                    cout << "  ERROR: Waktu tidak boleh negatif!" << endl;
                    cout << endl;
                } else {
                    inputValid = true;
                }
            }

            hasilJam   = inputMenit / 60;
            hasilDetik = inputMenit * 60;

            cout << endl;
            cout << "  -------------- HASIL KONVERSI --------------  " << endl;
            cout << "  " << inputMenit << " Menit = " << hasilJam << " Jam" << endl;
            cout << "  " << inputMenit << " Menit = " << hasilDetik << " Detik" << endl;
            cout << endl;
            cout << "=================================================" << endl;
            cout << "  Tekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();

        // pilihan 3 itu konfersi dari detik kita ubah ke jam dan menit
        } else if (pilihanMenu == "3") {
            double inputDetik;
            double hasilJam;
            double hasilMenit;
            bool inputValid = false;

            cout << "=================================================" << endl;
            cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
            cout << "|          Algoritma Pemrograman Dasar          |" << endl;
            cout << "=================================================" << endl;
            cout << endl;
            cout << "======== konversi detik ke jam dan menit ========" << endl;
            cout << endl;

            while (!inputValid) {
                cout << "  Masukkan nilai waktu dalam DETIK : ";
                cin >> inputDetik;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl;
                    cout << "  ERROR: Input tidak valid! Masukkan angka." << endl;
                    cout << endl;
                } else if (inputDetik < 0) {
                    cout << endl;
                    cout << "  ERROR: Waktunya tidak boleh negatif!" << endl;
                    cout << endl;
                } else {
                    inputValid = true;
                }
            }

            hasilJam   = inputDetik / 3600; 
            hasilMenit = inputDetik / 60;

            cout << endl;
            cout << "  -------------- HASIL KONVERSI --------------  " << endl;
            cout << "  " << inputDetik << " Detik = " << hasilJam << " Jam" << endl;
            cout << "  " << inputDetik << " Detik = " << hasilMenit << " Menit" << endl;
            cout << endl;
            cout << "=================================================" << endl;
            cout << "  Tekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();

        // pilihan ke 4 itu keluar, jadi selesai program nya
        } else if (pilihanMenu == "4") {
            cout << "=================================================" << endl;
            cout << "|         PROGRAM KONVERSI SATUAN WAKTU         |" << endl;
            cout << "|          Algoritma Pemrograman Dasar          |" << endl;
            cout << "=================================================" << endl;
            cout << endl;
            cout << "  Terima kasih sudah karena menggunakan program ini!" << endl;
            cout << "  Program sudah selesai." << endl;
            cout << endl;
            cout << "=================================================" << endl;
            programBerjalan = false;

        // ini output kalau inputan yang dimasukan user itu ngasal
        } else {
            cout << endl;
            cout << "  Pilihan anda tidak valid! Masukkan angka 1-4." << endl;
            cout << "  Tekan Enter untuk mencoba lagi...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}