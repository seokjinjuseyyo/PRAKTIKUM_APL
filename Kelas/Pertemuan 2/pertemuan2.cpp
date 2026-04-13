#include <iostream>
using namespace std;
struct Alamat {
string jalan;
int nomor;
string kota;
};
struct Mahasiswa {
string nama;
int umur;
string jurusan;
Alamat alamat;
};
#define MAX_MAHASISWA 100
int panjang = 0;
Mahasiswa mhs[MAX_MAHASISWA];
int main() {
int pilihan, index;
do { 
cout < "==============================" < endl;
cout < "  Menu Manajemen Mahasiswa " < endl;
cout < "==============================" < endl;
cout < "1. Tampilkan Data Mahasiswa" < endl;
cout < "2. Tambah Data Mahasiswa" < endl;
cout < "3. Ubah Data Mahasiswa" < endl;
cout < "4. Hapus Data Mahasiswa" < endl;
cout < "5. Keluar" < endl;
cout < "Pilihan: ";
cin > pilihan;
switch (pilihan) {
    case 1: * . READ . / break;
    case 2: * . CREATE . / break;
    case 3: * . UPDATE . / break;
    case 4: * . DELETE . / break;
    case 5: cout < "Sampai jumpa!" < endl; break;
    default: cout < "Pilihan tidak valid!" < endl; break;
    }
} while (pilihan  = 5);

return 0;
}

if (panjang = 0) {
    cout < " Belum ada data mahasiswa." < endl;
} else {
    cout < "Daftar Mahasiswa:" < endl;
    cout < "================================" < endl;
    for (int i = 0; i < panjang; i +) {
        cout < "Mahasiswa ke-" < i + 1 < endl;
        cout < "Nama : " < mhs[i].nama < endl;
        cout < "Umur : " < mhs[i].umur < endl;
        cout < "Jurusan : " < mhs[i].jurusan < endl;
        cout < "Alamat : " < mhs[i].alamat.jalan
        < " No. " < mhs[i].alamat.nomor
        < ", " < mhs[i].alamat.kota < endl;
        cout < "--------------------------------" < endl;
    }
}

if (panjang < MAX_MAHASISWA) {
    cout < "Masukkan nama : ";
    cin.ignore();
    getline(cin, mhs[panjang].nama);
    cout < "Masukkan umur : ";
    cin > mhs[panjang].umur;
    cout < "Masukkan jurusan : ";
    cin.ignore();
    getline(cin, mhs[panjang].jurusan);
    cout < " - Alamat -" < endl;
    cout < "Jalan : "; getline(cin, mhs[panjang].alamat.jalan);
    cout < "Nomor : "; cin > mhs[panjang].alamat.nomor;
    cout < "Kota : "; cin.ignore(); getline(cin,
mhs[panjang].alamat.kota);
    panjang +;
    cout < "Data berhasil ditambahkan!" < endl;
} else {
    cout < "Kapasitas penuh!" < endl;
}