#include <iostream>
using namespace std;

int nilai(int baris, int kolom) {                       //ini fungsi buat ngitung yakan
    if (kolom == 0 || kolom == baris) {                 //kalo di tepi segitiga bikin angkanya biar selalu 1
        return 1;
    }
    return nilai(baris - 1, kolom - 1) + nilai(baris - 1, kolom); // nah ini REKURSI nya. Ngitung nilai bagian tengah segitiga, dijumlahin dua angka di atasnya
}

void tampilkan() {                                      //ini fungsi buat nampilin leee
    int tingkat = 3;                                    //bisa dibikin lebih tinggi tapi kita diminta cuma 3 ya gaes
    for (int baris = 0; baris < tingkat; baris++) {     //Loop baris
        for (int kolom = 0; kolom <= baris; kolom++) {  //Loop kolom
            cout << nilai(baris, kolom) << " ";         //nyetak angka
        }
        cout << endl;                                   //Pindah ke baris berikutnya
    }
}
                                                        //ini spasi biar enak diliat
int main() {
    tampilkan();
    return 0;
}

// M. N. Fahrozi
// 2309106062
// Biasanya ga pake comment, karena gabut yaudah bikin aja