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

// Merge Sort
Film* merge(Film* left, Film* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->tahunRilis <= right->tahunRilis) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Film* mergeSort(Film* head) {
    if (!head || !head->next) return head;

    Film* mid = head;
    Film* fast = head->next;
    while (fast && fast->next) {
        mid = mid->next;
        fast = fast->next->next;
    }

    Film* right = mid->next;
    mid->next = nullptr;

    return merge(mergeSort(head), mergeSort(right));
}

// Quick Sort
Film* partition(Film* head, Film* end, Film** newHead, Film** newEnd) {
    Film* pivot = end;
    Film* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->tahunRilis >= pivot->tahunRilis) {
            if ((*newHead) == nullptr)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;

            Film* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;

    (*newEnd) = tail;
    return pivot;
}

Film* quickSortRecur(Film* head, Film* end) {
    if (!head || head == end)
        return head;

    Film* newHead = nullptr, *newEnd = nullptr;
    Film* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Film* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = newHead;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void sortFilm(bool ascending) {
    if (head == nullptr) {
        cout << "Katalog film kosong, tidak bisa di-sort." << endl;
        return;
    }

    if (ascending) {
        head = mergeSort(head);
        cout << "Film telah di-sort secara ascending (Merge Sort)." << endl;
    } else {
        Film* end = head;
        while (end->next != nullptr)
            end = end->next;

        head = quickSortRecur(head, end);
        cout << "Film telah di-sort secara descending (Quick Sort)." << endl;
    }
}

void menu() {
    int pilihan;
    do {
        cout << "\n=== Menu Utama ===" << endl;
        cout << "[1] Tambah film baru" << endl;
        cout << "[2] Tampilkan list film" << endl;
        cout << "[3] Ubah film" << endl;
        cout << "[4] Hapus film" << endl;
        cout << "[5] Undo penambahan film" << endl;
        cout << "[6] Tambah film ke watchlist" << endl;
        cout << "[7] Tonton film dari watchlist" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                string judul, genre;
                int tahunRilis;
                cout << "Masukkan judul film: ";
                getline(cin, judul);
                cout << "Masukkan genre film: ";
                getline(cin, genre);
                cout << "Masukkan tahun rilis: ";
                cin >> tahunRilis;
                cin.ignore();
                tambahFilm(judul, genre, tahunRilis);
                break;
            }
            case 2:
                tampilkanFilm();

                int pilihanSort;
                cout << "\n[1] Sort Film (Merge Sort Ascending)" << endl;
                cout << "[2] Sort Film (Quick Sort Descending)" << endl;
                cout << "[0] Kembali ke menu utama" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihanSort;
                cin.ignore();

                switch (pilihanSort) {
                    case 1:
                        sortFilm(true);
                        break;
                    case 2:
                        sortFilm(false);
                        break;
                    case 0:
                        cout << "Kembali ke menu utama." << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                        break;
                }
                break;
            case 3: {
                int id;
                cout << "Masukkan ID film yang akan diubah: ";
                cin >> id;
                cin.ignore();
                ubahFilm(id);
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan ID film yang akan dihapus: ";
                cin >> id;
                cin.ignore();
                hapusFilm(id);
                break;
            }
            case 5:
                undoFilm();
                break;
            case 6: {
                int id;
                cout << "Masukkan ID film yang akan ditambahkan ke watchlist: ";
                cin >> id;
                cin.ignore();
                Film* film = cariFilmBerdasarkanID(id);
                if (film != nullptr) {
                    tambahWatchlist(film);
                } else {
                    cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
                }
                break;
            }
            case 7:
                tontonFilm();
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 0);
}

int main() {
    tambahFilm("The Godfather Part II", "Drama", 1974);
    tambahFilm("Blade Runner 2049", "Science Fiction", 2017);
    tambahFilm("Heat", "Action", 1995);
    tambahFilm("La La Land", "Musical", 2016);
    tambahFilm("Psycho", "Horror", 1960);

    menu();
    return 0;
}
