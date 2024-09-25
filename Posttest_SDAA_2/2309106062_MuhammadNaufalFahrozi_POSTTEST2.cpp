#include <iostream>
#include <string>
using namespace std;

struct Film {                   // Struct untuk menyimpan informasi film
    string judul;
    string genre;
    int tahunRilis;
};

const int MAX_FILM = 100;       // Array statis dengan kapasitas maksimum 100 film
Film daftarFilm[MAX_FILM];
int jumlahFilm = 20;            // Sudah ada 20 film dummy di awal

                                // Fungsi untuk membersihkan input stream jika terjadi kesalahan input
void clearInput() {
    cin.clear(); 
    cin.ignore();
}

void tambahFilm(const string& judul, const string& genre, int tahunRilis) {
    if (jumlahFilm < MAX_FILM) {
        Film* ptr = &daftarFilm[jumlahFilm];                                    // Pointer menunjuk ke elemen baru
        ptr->judul = judul;
        ptr->genre = genre;
        ptr->tahunRilis = tahunRilis;
        jumlahFilm++;
        cout << "Film berhasil ditambahkan!" << endl;
    } else {
        cout << "Katalog penuh, tidak dapat menambahkan film baru." << endl;
    }
}

void tampilkanFilm() {
    if (jumlahFilm == 0) {
        cout << "Katalog film kosong." << endl;
    } else {
        Film* ptr = daftarFilm;                                                 // Pointer untuk menunjuk ke array daftarFilm
        for (int i = 0; i < jumlahFilm; i++) {
            cout << "Judul: " << (ptr + i)->judul << ", Genre: " << (ptr + i)->genre << ", Tahun Rilis: " << (ptr + i)->tahunRilis << endl;
        }
    }
}

void updateFilm(const string& judul) {
    Film* ptr = daftarFilm;                                                     // Pointer untuk menunjuk ke array daftarFilm
    for (int i = 0; i < jumlahFilm; i++) {
        if ((ptr + i)->judul == judul) {
            cout << "Masukkan judul baru: ";
            getline(cin, (ptr + i)->judul); 
            cout << "Masukkan genre baru: ";
            getline(cin, (ptr + i)->genre);  

            int tahunRilis;
            cout << "Masukkan tahun rilis baru: ";
            while (!(cin >> tahunRilis)) {
                cout << "Input tidak valid. Masukkan angka untuk tahun rilis: ";
                clearInput();
            }
            (ptr + i)->tahunRilis = tahunRilis;

            cout << "Film berhasil diperbarui!" << endl;
            clearInput(); 
            return;
        }
    }
    cout << "Film tidak ditemukan." << endl;
}

void hapusFilm(const string& judul) {
    Film* ptr = daftarFilm;                                                     // Pointer untuk menunjuk ke array daftarFilm
    for (int i = 0; i < jumlahFilm; i++) {
        if ((ptr + i)->judul == judul) {
            for (int j = i; j < jumlahFilm - 1; j++) {
                *(ptr + j) = *(ptr + j + 1);
            }
            jumlahFilm--;
            cout << "Film berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Film tidak ditemukan." << endl;
}

void arrayFilmStatis() {
    Film* ptr = daftarFilm;                                                 // Pointer untuk menunjuk ke array daftarFilm
    (ptr + 0)->judul = "The Shawshank Redemption"; (ptr + 0)->genre = "Drama"; (ptr + 0)->tahunRilis = 1994;
    (ptr + 1)->judul = "The Godfather"; (ptr + 1)->genre = "Crime"; (ptr + 1)->tahunRilis = 1972;
    (ptr + 2)->judul = "The Dark Knight"; (ptr + 2)->genre = "Action"; (ptr + 2)->tahunRilis = 2008;
    (ptr + 3)->judul = "The Godfather: Part II"; (ptr + 3)->genre = "Crime"; (ptr + 3)->tahunRilis = 1974;
    (ptr + 4)->judul = "12 Angry Men"; (ptr + 4)->genre = "Drama"; (ptr + 4)->tahunRilis = 1957;
    (ptr + 5)->judul = "Schindler's List"; (ptr + 5)->genre = "Biography"; (ptr + 5)->tahunRilis = 1993;
    (ptr + 6)->judul = "The Lord of the Rings: The Return of the King"; (ptr + 6)->genre = "Adventure"; (ptr + 6)->tahunRilis = 2003;
    (ptr + 7)->judul = "Pulp Fiction"; (ptr + 7)->genre = "Crime"; (ptr + 7)->tahunRilis = 1994;
    (ptr + 8)->judul = "The Good, the Bad and the Ugly"; (ptr + 8)->genre = "Western"; (ptr + 8)->tahunRilis = 1966;
    (ptr + 9)->judul = "The Lord of the Rings: The Fellowship of the Ring"; (ptr + 9)->genre = "Adventure"; (ptr + 9)->tahunRilis = 2001;
    (ptr + 10)->judul = "Fight Club"; (ptr + 10)->genre = "Drama"; (ptr + 10)->tahunRilis = 1999;
    (ptr + 11)->judul = "Forrest Gump"; (ptr + 11)->genre = "Drama"; (ptr + 11)->tahunRilis = 1994;
    (ptr + 12)->judul = "Inception"; (ptr + 12)->genre = "Action"; (ptr + 12)->tahunRilis = 2010;
    (ptr + 13)->judul = "The Lord of the Rings: The Two Towers"; (ptr + 13)->genre = "Adventure"; (ptr + 13)->tahunRilis = 2002;
    (ptr + 14)->judul = "Star Wars: Episode V - The Empire Strikes Back"; (ptr + 14)->genre = "Action"; (ptr + 14)->tahunRilis = 1980;
    (ptr + 15)->judul = "The Matrix"; (ptr + 15)->genre = "Sci-Fi"; (ptr + 15)->tahunRilis = 1999;
    (ptr + 16)->judul = "Goodfellas"; (ptr + 16)->genre = "Crime"; (ptr + 16)->tahunRilis = 1990;
    (ptr + 17)->judul = "One Flew Over the Cuckoo's Nest"; (ptr + 17)->genre = "Drama"; (ptr + 17)->tahunRilis = 1975;
    (ptr + 18)->judul = "Se7en"; (ptr + 18)->genre = "Crime"; (ptr + 18)->tahunRilis = 1995;
    (ptr + 19)->judul = "The Silence of the Lambs"; (ptr + 19)->genre = "Crime"; (ptr + 19)->tahunRilis = 1991;
}

void menu() {
    int pilihan;
    string judul, genre;
    int tahunRilis;

    do {
        cout << "\n=== Katalog Film ===" << endl;
        cout << "1. Tambah Film" << endl;
        cout << "2. Tampilkan Semua Film" << endl;
        cout << "3. Update Film" <<endl;
        cout << "4. Hapus Film" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi: ";

        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 5) {
            cout << "Input tidak valid. Pilih angka antara 1 hingga 5: ";
            clearInput();
        }
        clearInput(); 

        switch (pilihan) {
            case 1:
                if (jumlahFilm < MAX_FILM) {
                    cout << "Masukkan judul film: ";
                    getline(cin, judul);
                    cout << "Masukkan genre film: ";
                    getline(cin, genre); 
                    cout << "Masukkan tahun rilis film: ";
                    while (!(cin >> tahunRilis)) {
                        cout << "Input tidak valid. Masukkan angka untuk tahun rilis: ";
                        clearInput();
                    }
                    tambahFilm(judul, genre, tahunRilis);
                } else {
                    cout << "Katalog film sudah penuh." << endl;
                }
                clearInput(); 
                break;
            case 2:
                tampilkanFilm();
                break;
            case 3:
                cout << "Masukkan judul film yang ingin diupdate: ";
                getline(cin, judul); 
                updateFilm(judul);
                break;
            case 4:
                cout << "Masukkan judul film yang ingin dihapus: ";
                getline(cin, judul); 
                hapusFilm(judul);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
        }
    } while (pilihan != 5);
}

int main() {
    arrayFilmStatis();
    menu();
    return 0;
}
