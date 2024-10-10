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

struct Stack {
    Film* film;
    Stack* next;
};
Stack* undoStack = nullptr;

struct QueueNode {
    Film* film;
    QueueNode* next;
};
QueueNode* front = nullptr;
QueueNode* rear = nullptr;

void tambahFilm(const string& judul, const string& genre, int tahunRilis) {
    Film* newFilm = new Film;
    newFilm->id = nextId++;
    newFilm->judul = judul;
    newFilm->genre = genre;
    newFilm->tahunRilis = tahunRilis;
    newFilm->next = nullptr;

    if (head == nullptr) {
        head = newFilm;
    } else {
        Film* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newFilm;
    }

    Stack* newUndo = new Stack;
    newUndo->film = newFilm;
    newUndo->next = undoStack;
    undoStack = newUndo;

    cout << "Film dengan ID " << newFilm->id << " berhasil ditambahkan!" << endl;
}

void tampilkanFilm() {
    if (head == nullptr) {
        cout << "Katalog film kosong." << endl;
        return;
    }
    Film* temp = head;
    while (temp != nullptr) {
        cout << "ID             : " << temp->id << endl;
        cout << "Judul          : " << temp->judul << endl;
        cout << "Genre          : " << temp->genre << endl;
        cout << "Tahun Rilis    : " << temp->tahunRilis << endl;
        cout << "------------------------------------------------" << endl;
        temp = temp->next;
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

// Undo penambahan film terakhir (Stack)
void undoFilm() {
    if (undoStack == nullptr) {
        cout << "Tidak ada film yang bisa di-undo." << endl;
        return;
    }

    Film* toUndo = undoStack->film;
    if (head == toUndo) {
        head = head->next;
    } else {
        Film* temp = head;
        while (temp->next != toUndo) {
            temp = temp->next;
        }
        temp->next = toUndo->next;
    }

    Stack* tempUndo = undoStack;
    undoStack = undoStack->next;
    delete tempUndo;
    delete toUndo;

    cout << "Penambahan film terakhir telah di-undo." << endl;
}

// Menambah film ke Watchlist (Queue)
void tambahWatchlist(Film* film) {
    QueueNode* newQueueNode = new QueueNode;
    newQueueNode->film = film;
    newQueueNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newQueueNode;
    } else {
        rear->next = newQueueNode;
        rear = newQueueNode;
    }
    cout << "Film '" << film->judul << "' telah ditambahkan ke watchlist." << endl;
}

// Menonton film dari Watchlist (Queue)
void tontonFilm() {
    if (front == nullptr) {
        cout << "Watchlist kosong." << endl;
        return;
    }

    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "Menonton film '" << temp->film->judul << "'..." << endl;
    delete temp;
}

void menu() {
    int pilihan;
    string judul, genre;
    int tahunRilis, id;

    do {
        cout << "\n=== Katalog Film ===" << endl;
        cout << "[1] Tambah Film" << endl;
        cout << "[2] Tampilkan List Film" << endl;
        cout << "[3] Ubah Film" << endl;
        cout << "[4] Hapus Film" << endl;
        cout << "[5] Undo Penambahan Film Terakhir" << endl;
        cout << "[6] Tambah Watchlist" << endl;
        cout << "[7] Tonton Watchlist" << endl;
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
            case 5:
                undoFilm();
                break;
            case 6:
                tampilkanFilm();
                cout << "Masukkan ID film untuk ditambahkan ke watchlist: ";
                cin >> id;
                cin.ignore();
                {
                    Film* temp = head;
                    while (temp != nullptr) {
                        if (temp->id == id) {
                            tambahWatchlist(temp);
                            break;
                        }
                        temp = temp->next;
                    }
                    if (temp == nullptr) {
                        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
                    }
                }
                break;
            case 7:
                tontonFilm();
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