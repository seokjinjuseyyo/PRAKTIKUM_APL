/*#include <iostream>
using namespace std;

/ prosedur ini menerima nilai dari variable gajiSaya
void cobaUbahGaji(int gajiSaya) {
gajiSaya = 1000000000; / gaji di dalam prosedur
cout < "Gaji pas di dalam fungsi: " < gajiSaya < endl;
}

int main() {
int gajiSaya = 5000000; / gaji di dalam main

cout < "Gaji awal: " < gajiSaya < endl;

cobaUbahGaji(gajiSaya); / kirim ke fungsi

cout < "Gaji setelah fungsi dipanggil: " < gajiSaya < endl;

return 0;
}*/

/*#include <iostream>
using namespace std;

/ perhatikan tanda '&' di sebelah parameter
void tukarsenjata(string &senjata) {
senjata = "Sarung Wadimor"; / langsung ganti isi variabel
aslinya
}

int main() {
string senjatahero = "Kayu Busuk";

cout < "Senjata awal: " < senjatahero < endl;

tukarsenjata(senjatahero); / panggil prosedur

/ variable dalam main akan ikut terubah
cout < "Senjata sekarang: " < senjatahero < endl;

return 0;
}*/

/*#include <iostream>
using namespace std;

/ 'kadarGula' punya nilai default "Normal"
/ parameter default wajib di taruh paling kanan!
void pesankopi(string menu, string kadargula = "Normal") {
cout < "Pesanan: " < menu < " | Gula: " < kadargula < endl;
}

int main() {
/ Kasus 1: pengguna mengirim 1 parameter
pesankopi("Kopi Susu");

/ Kasus 2: pengguna mengirim 2 parameter dan menggantikan
parameter default dari prosedur
pesankopi("Americano", "Less Sugar");

return 0;
}*/

/*#include <iostream>
using namespace std;

/ variabel global
int skorTertinggi = 100;

void cetakSkor() {
/ Fungsi ini akan membaca variabel global skorTertinggi
cout < "Skor Fungsi: " < skorTertinggi < endl;
}

int main() {
cout < "Skor : " < skorTertinggi < endl;

/ Panggil fungsi
cetakSkor();

return 0;
}*/

#include <iostream>
using namespace std;
void calonJuara() {
// variabel lokal, cuma bisa dipakai di dalam fungsi ini
string Team = "RRQ";
cout << "Tim: " << Team << endl;
}
int main() {
calonJuara(); // fungsi berjalan normal
// namun jika kita coba akses Team di sini
// cout << "Tim: " << Team << endl;
// maka akan error karena Team tidak dikenal di sini
return 0;
}

