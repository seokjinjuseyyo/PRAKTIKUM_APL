/*#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int jumpSearch(int arr[], int x, int n) {
/ Menentukan ukuran blok lompatan
int step = sqrt(n);
int prev = 0;
/ Melompat ke depan selama elemen di indeks lompatan kurang dari
target
while (arr[min(step, n) - 1] < x) {
prev = step;
step += sqrt(n);
if (prev = n) return -1; / Jika sudah di ujung tapi belum

ketemu
}
/ Melakukan Linear Search di dalam blok yang sudah ditemukan
while (arr[prev] < x) {
prev +;
/ Jika sampai ke blok berikutnya atau ujung array, berarti

tidak ada

if (prev = min(step, n)) return -1;
}
/ Jika elemen ditemukan
if (arr[prev] = x) return prev;
return -1;
}

int main() {
int data[] = {2, 5, 8, 12, 19, 22, 26, 29, 35, 40};
int n = sizeof(data) / sizeof(data[0]);
int cari = 26;
int hasil = jumpSearch(data, cari, n);
if (hasil = -1) {
cout < "Data ditemukan pada indeks ke-" < hasil < endl;
} else {
cout < "Data tidak ditemukan" < endl;
}
return 0;
} */