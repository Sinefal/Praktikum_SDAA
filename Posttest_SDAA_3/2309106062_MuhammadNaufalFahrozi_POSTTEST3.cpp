#include <iostream>
using namespace std;

struct Film {
    int id;
    string judul;
    string genre;
    int tahunRilis;
    Film* next;
};

Film* head = nullptr;
int nextId = 1;

Film* filmBaru(const string& judul, const string& genre, int tahunRilis) {
    Film* newFilm = new Film;
    newFilm->id = nextId++;
    newFilm->judul = judul;
    newFilm->genre = genre;
    newFilm->tahunRilis = tahunRilis;
    newFilm->next = nullptr;
    return newFilm;
}

void tambahFilm(const string& judul, const string& genre, int tahunRilis) {
    Film* newFilm = filmBaru(judul, genre, tahunRilis);
    if (head == nullptr) {
        head = newFilm;
    } else {
        Film* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newFilm;
    }
    cout << "Film dengan ID " << newFilm->id << " berhasil ditambahkan!" << endl;
}

void tampilkanFilm() {
    if (head == nullptr) {
        cout << "Katalog film kosong." << endl;
    } else {
        Film* temp = head;
        while (temp != nullptr) {

            cout << "ID             : " << temp->id << endl;
            cout << "Judul          : " << temp->judul << endl;
            cout << "Genre          : " << temp->genre << endl;
            cout << "Tahun Rilis    : " << temp->tahunRilis << endl;
            cout << "------------------------------------------------\n";
            temp = temp->next;
        }
    }
}

Film* cariFilmBerdasarkanID(int id) {
    Film* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void ubahFilm(int id) {
    Film* film = cariFilmBerdasarkanID(id);
    if (film != nullptr) {
        cout << "Masukkan judul baru        : ";
        getline(cin, film->judul);
        cout << "Masukkan genre baru        : ";
        getline(cin, film->genre);

        int tahunRilis;
        cout << "Masukkan tahun rilis baru  : ";
        cin >> tahunRilis;
        cin.ignore();

        film->tahunRilis = tahunRilis;
        cout << "Film dengan ID " << id << " berhasil diperbarui!" << endl;
    } else {
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void hapusFilm(int id) {
    if (head == nullptr) {
        cout << "Katalog film kosong." << endl;
        return;
    }

    if (head->id == id) {
        Film* temp = head;
        head = head->next;
        delete temp;
        cout << "Film dengan ID " << id << " berhasil dihapus!" << endl;
        return;
    }

    Film* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    } else {
        Film* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Film dengan ID " << id << " berhasil dihapus!" << endl;
    }
}

void menu() {
    int pilihan;
    string judul, genre;
    int tahunRilis, id;

    do {
        cout << "\n=== Katalog Film ===" << endl;
        cout << "[1] Tambah Film" << endl;
        cout << "[2] Tampilkan Semua Film" << endl;
        cout << "[3] Ubah Film" <<endl;
        cout << "[4] Hapus Film" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan judul film        : ";
                getline(cin, judul);
                cout << "Masukkan genre film        : ";
                getline(cin, genre);
                cout << "Masukkan tahun rilis film  : ";
                cin >> tahunRilis;
                cin.ignore();
                tambahFilm(judul, genre, tahunRilis);
                break;
            case 2:
                tampilkanFilm();
                break;
            case 3:
                tampilkanFilm();
                cout << "Masukkan ID film yang ingin diubah: ";
                cin >> id;
                cin.ignore();
                ubahFilm(id);
                break;
            case 4:
                tampilkanFilm();
                cout << "Masukkan ID film yang ingin dihapus: ";
                cin >> id;
                cin.ignore();
                hapusFilm(id);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}