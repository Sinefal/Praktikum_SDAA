#include <iostream>
#include <cmath>
#include <vector> 
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

void cariFilmBerdasarkanID_Fibonacci(int id) {
    vector<Film*> films;
    Film* temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    int n = films.size();
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (films[i]->id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (films[i]->id > id) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << "Film ditemukan: " << endl;
            cout << "ID             : " << films[i]->id << endl;
            cout << "Judul          : " << films[i]->judul << endl;
            cout << "Genre          : " << films[i]->genre << endl;
            cout << "Tahun Rilis    : " << films[i]->tahunRilis << endl;
            return;
        }
    }

    if (fibMMm1 && films[offset + 1]->id == id) {
        cout << "Film ditemukan: " << endl;
        cout << "ID             : " << films[offset + 1]->id << endl;
        cout << "Judul          : " << films[offset + 1]->judul << endl;
        cout << "Genre          : " << films[offset + 1]->genre << endl;
        cout << "Tahun Rilis    : " << films[offset + 1]->tahunRilis << endl;
        return;
    }

    cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
}

void cariFilmBerdasarkanTahunRilis_Jump(int tahunRilis) {
    vector<Film*> films;
    Film* temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    head = mergeSort(head);

    films.clear();
    temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    int n = films.size();
    int step = sqrt(n);
    int prev = 0;

    while (films[min(step, n) - 1]->tahunRilis < tahunRilis) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Film dengan Tahun Rilis " << tahunRilis << " tidak ditemukan." << endl;
            return;
        }
    }

    while (films[prev]->tahunRilis < tahunRilis) {
        prev++;
        if (prev == min(step, n)) {
            cout << "Film dengan Tahun Rilis " << tahunRilis << " tidak ditemukan." << endl;
            return;
        }
    }

    if (films[prev]->tahunRilis == tahunRilis) {
        cout << "Film ditemukan: " << endl;
        while (prev < n && films[prev]->tahunRilis == tahunRilis) {
            cout << "ID             : " << films[prev]->id << endl;
            cout << "Judul          : " << films[prev]->judul << endl;
            cout << "Genre          : " << films[prev]->genre << endl;
            cout << "Tahun Rilis    : " << films[prev]->tahunRilis << endl;
            cout << "------------------------------------------------" << endl;
            prev++;
        }
        return;
    }

    cout << "Film dengan Tahun Rilis " << tahunRilis << " tidak ditemukan." << endl;
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

void cariFilmBerdasarkanJudul_BoyerMoore(const string& judul) {
    string lowerJudul = toLowerCase(judul);
    vector<Film*> films;
    Film* temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    int n = films.size();
    int m = lowerJudul.size();
    vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[(int)lowerJudul[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        string lowerFilmJudul = toLowerCase(films[i]->judul);
        int s = 0;
        while (s <= (int)(lowerFilmJudul.size() - m)) {
            int j = m - 1;
            while (j >= 0 && lowerJudul[j] == lowerFilmJudul[s + j]) {
                j--;
            }
            if (j < 0) {
                cout << "Film ditemukan: " << endl;
                cout << "ID             : " << films[i]->id << endl;
                cout << "Judul          : " << films[i]->judul << endl;
                cout << "Genre          : " << films[i]->genre << endl;
                cout << "Tahun Rilis    : " << films[i]->tahunRilis << endl;
                cout << "------------------------------------------------" << endl;
                break;
            } else {
                s += max(1, j - badChar[(int)lowerFilmJudul[s + j]]);
            }
        }
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
        cout << "[5] Cari film" << endl;
        cout << "[6] Undo penambahan film" << endl;
        cout << "[7] Tambah film ke watchlist" << endl;
        cout << "[8] Tonton film dari watchlist" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                system("cls");
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
                system("cls");
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
                        system("cls");
                        sortFilm(true);
                        break;
                    case 2:
                        system("cls");
                        sortFilm(false);
                        break;
                    case 0:
                        system("cls");
                        cout << "Kembali ke menu utama." << endl;
                        break;
                    default:
                        system("cls");
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                        break;
                }
                break;
            case 3: {
                system("cls");
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
            case 5: {
                system("cls");
                int pilihanSearch;
                cout << "\n=== Cari Film Berdasarkan ===" << endl;
                cout << "[1] ID (Fibonacci Search)" << endl;
                cout << "[2] Tahun Rilis (Jump Search)" << endl;
                cout << "[3] Judul (Boyer-Moore Search)" << endl;
                cout << "[0] Kembali ke menu utama" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihanSearch;
                cin.ignore();

                switch (pilihanSearch) {
                    case 1: {
                        system("cls");
                        int id;
                        cout << "Masukkan ID film: ";
                        cin >> id;
                        cin.ignore();
                        cariFilmBerdasarkanID_Fibonacci(id);
                        break;
                    }
                    case 2: {
                        system("cls");
                        int tahunRilis;
                        cout << "Masukkan Tahun Rilis film: ";
                        cin >> tahunRilis;
                        cin.ignore();
                        cariFilmBerdasarkanTahunRilis_Jump(tahunRilis);
                        break;
                    }
                    case 3: {
                        system("cls");
                        string judul;
                        cout << "Masukkan Judul film: ";
                        getline(cin, judul);
                        cariFilmBerdasarkanJudul_BoyerMoore(judul);
                        break;
                    }
                    case 0:
                        system("cls");
                        cout << "Kembali ke menu utama." << endl;
                        break;
                    default:
                        system("cls");
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                        break;
                }
                break;
            }
            case 6:
                system("cls");
                undoFilm();
                break;
            case 7: {
                system("cls");
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
            case 8:
                system("cls");
                tontonFilm();
                break;
            case 0:
                system("cls");
                cout << "Keluar dari program." << endl;
                break;
            default:
                system("cls");
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
