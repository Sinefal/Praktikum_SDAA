#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

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

struct StackNode {
    Film* film;
    StackNode* next;
};

StackNode* watchHistory = nullptr;

struct QueueNode {
    Film* film;
    QueueNode* next;
};

QueueNode* front = nullptr;
QueueNode* rear = nullptr;

void pushWatchHistory(Film* film) {
    StackNode* newNode = new StackNode;
    newNode->film = film;
    newNode->next = watchHistory;
    watchHistory = newNode;
}

void tampilkanWatchHistory() {
    if (watchHistory == nullptr) {
        system("cls");
        cout << "Watch history kosong." << endl;
        return;
    }
    StackNode* temp = watchHistory;
    cout << "=== Watch History ===" << endl;
    while (temp != nullptr) {
        cout << "ID             : " << temp->film->id << endl;
        cout << "Judul          : " << temp->film->judul << endl;
        cout << "Genre          : " << temp->film->genre << endl;
        cout << "Tahun Rilis    : " << temp->film->tahunRilis << endl;
        cout << "------------------------------------------------" << endl;
        temp = temp->next;
    }
}

bool hanyaSpasi(const string& str) {
    for (char c : str) {
        if (!isspace(c))
            return false;
    }
    return true;
}

bool cekGenre(const string& genre) {
    if (genre == "Science Fiction")
        return true;
    if (genre.empty() || genre.find(' ') != string::npos)
        return false;
    for (char c : genre) {
        if (!isalpha(c))
            return false;
    }
    return true;
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

bool cekDuplikat(const string& judul, const string& genre, int tahunRilis) {
    Film* temp = head;
    while (temp != nullptr) {
        if (toLowerCase(temp->judul) == toLowerCase(judul) &&
            toLowerCase(temp->genre) == toLowerCase(genre) &&
            temp->tahunRilis == tahunRilis) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void tambahFilm(const string& judul, const string& genre, int tahunRilis) {
    if (cekDuplikat(judul, genre, tahunRilis)) {
        system("cls");
        cout << "Film dengan judul, genre, dan tahun rilis yang sama sudah ada." << endl;
        return;
    }

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
    system("cls");
    cout << "Film " << newFilm->judul << " berhasil ditambahkan dengan ID " << newFilm->id << endl;
}

void tampilkanFilm() {
    if (head == nullptr) {
        system("cls");
        cout << "Katalog film kosong." << endl;
        return;
    }
    Film* temp = head;
    cout << "=== Daftar Film ===" << endl;
    while (temp != nullptr) {
        cout << "ID             : " << temp->id << endl;
        cout << "Judul          : " << temp->judul << endl;
        cout << "Genre          : " << temp->genre << endl;
        cout << "Tahun Rilis    : " << temp->tahunRilis << endl;
        cout << "------------------------------------------------" << endl;
        temp = temp->next;
    }
}

Film* pilihID(int id) {
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
    Film* film = pilihID(id);
    if (film != nullptr) {
        string judulBaru, genreBaru;
        int tahunRilisBaru;

        cout << "Masukkan judul baru        : ";
        getline(cin, judulBaru);
        if (judulBaru.empty() || hanyaSpasi(judulBaru)) {
            system("cls");
            cout << "Judul tidak boleh kosong atau hanya spasi!" << endl;
            return;
        }

        cout << "Masukkan genre baru        : ";
        getline(cin, genreBaru);
        if (!cekGenre(genreBaru)) {
            system("cls");
            cout << "Genre hanya boleh mengandung huruf dan tidak boleh kosong atau mengandung spasi." << endl;
            return;
        }

        cout << "Masukkan tahun rilis baru  : ";
        while (!(cin >> tahunRilisBaru) || tahunRilisBaru < 1878 || tahunRilisBaru > 2024 || cin.peek() != '\n') {
            cout << "Input invalid. Masukkan tahun rilis (1878-2024): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if (cekDuplikat(judulBaru, genreBaru, tahunRilisBaru)) {
            system("cls");
            cout << "Film dengan judul, genre, dan tahun rilis yang sama sudah ada." << endl;
            return;
        }

        film->judul = judulBaru;
        film->genre = genreBaru;
        film->tahunRilis = tahunRilisBaru;

        system("cls");
        cout << "Film dengan ID " << id << " berhasil diperbarui!" << endl;
    } else {
        system("cls");
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void hapusFilm(int id) {
    if (head == nullptr) {
        system("cls");
        cout << "Katalog film kosong." << endl;
        return;
    }

    if (head->id == id) {
        Film* temp = head;
        head = head->next;
        delete temp;
        system("cls");
        cout << "Film dengan ID " << id << " berhasil dihapus!" << endl;
        return;
    }

    Film* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        system("cls");
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    } else {
        Film* temp = current->next;
        current->next = current->next->next;
        delete temp;
        system("cls");
        cout << "Film dengan ID " << id << " berhasil dihapus!" << endl;
    }
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
    system("cls");
    cout << "Film '" << film->judul << "' telah ditambahkan ke watchlist." << endl;
}

void tampilkanWatchlist() {
    if (front == nullptr) {
        cout << "Watchlist kosong." << endl;
        return;
    }
    QueueNode* temp = front;
    cout << "=== Watchlist ===" << endl;
    while (temp != nullptr) {
        cout << "ID             : " << temp->film->id << endl;
        cout << "Judul          : " << temp->film->judul << endl;
        cout << "Genre          : " << temp->film->genre << endl;
        cout << "Tahun Rilis    : " << temp->film->tahunRilis << endl;
        cout << "------------------------------------------------" << endl;
        temp = temp->next;
    }
}

void tontonFilm() {
    if (front == nullptr) {
        system("cls");
        cout << "Watchlist kosong." << endl;
        return;
    }

    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "Menonton film '" << temp->film->judul << "'..." << endl;

    pushWatchHistory(temp->film);

    delete temp;
}

Film* merge(Film* left, Film* right, const string& mode) {
    if (!left) return right;
    if (!right) return left;

    Film* result = nullptr;

    if (mode == "id") {
        if (left->id <= right->id) {
            result = left;
            result->next = merge(left->next, right, mode);
        } else {
            result = right;
            result->next = merge(left, right->next, mode);
        }
    } else if (mode == "genre") {
        if (left->genre <= right->genre) {
            result = left;
            result->next = merge(left->next, right, mode);
        } else {
            result = right;
            result->next = merge(left, right->next, mode);
        }
    }
    return result;
}

Film* mergeSort(Film* head, const string& mode) {
    if (!head || !head->next) return head;

    Film* mid = head;
    Film* fast = head->next;
    while (fast && fast->next) {
        mid = mid->next;
        fast = fast->next->next;
    }

    Film* right = mid->next;
    mid->next = nullptr;

    Film* left = mergeSort(head, mode);
    right = mergeSort(right, mode);

    return merge(left, right, mode);
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

void shellSortJudul(vector<Film*>& films) {
    int n = films.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Film* temp = films[i];
            int j;
            for (j = i; j >= gap && films[j - gap]->judul > temp->judul; j -= gap) {
                films[j] = films[j - gap];
            }
            films[j] = temp;
        }
    }
}

int partitionTahunRilis(vector<Film*>& films, int low, int high) {
    int pivot = films[high]->tahunRilis;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (films[j]->tahunRilis <= pivot) {
            i++;
            Film* temp = films[i];
            films[i] = films[j];
            films[j] = temp;
        }
    }
    Film* temp = films[i + 1];
    films[i + 1] = films[high];
    films[high] = temp;
    return i + 1;
}

void quickSortTahunRilis(vector<Film*>& films, int low, int high) {
    if (low < high) {
        int pi = partitionTahunRilis(films, low, high);
        quickSortTahunRilis(films, low, pi - 1);
        quickSortTahunRilis(films, pi + 1, high);
    }
}

void mergeGenre(vector<Film*>& films, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Film*> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = films[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = films[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->genre <= R[j]->genre) {
            films[k] = L[i];
            i++;
        } else {
            films[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        films[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        films[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortGenre(vector<Film*>& films, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortGenre(films, left, mid);
        mergeSortGenre(films, mid + 1, right);
        mergeGenre(films, left, mid, right);
    }
}

void sortFilm() {
    int pilihanSort;
    cout << "\n=== Urutkan Film Berdasarkan ===" << endl;
    cout << "[1] ID Film (Merge Sort)" << endl;
    cout << "[2] Tahun Rilis Terbaru (Quick Sort)" << endl;
    cout << "[3] Judul Film A-Z (Shell Sort)" << endl;
    cout << "[0] Kembali ke menu utama" << endl;
    cout << "Pilih opsi: ";
    while (!(cin >> pilihanSort)) {
        cout << "Input invalid. Pilih opsi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    switch (pilihanSort) {
        case 1:
            head = mergeSort(head, "id");
            system("cls");
            cout << "Film telah diurutkan berdasarkan ID secara ascending (Merge Sort)." << endl;
            break;
        case 2: {
            Film* end = head;
            while (end->next != nullptr)
                end = end->next;
            head = quickSortRecur(head, end);
            system("cls");
            cout << "Film telah diurutkan berdasarkan tahun rilis secara descending (Quick Sort)." << endl;
            break;
        }
        case 3: {
            vector<Film*> films;
            Film* temp = head;
            while (temp != nullptr) {
                films.push_back(temp);
                temp = temp->next;
            }
            shellSortJudul(films);
            head = nullptr;
            temp = nullptr;
            for (Film* film : films) {
                film->next = nullptr;
                if (head == nullptr) {
                    head = film;
                    temp = head;
                } else {
                    temp->next = film;
                    temp = temp->next;
                }
            }
            system("cls");
            cout << "Film telah diurutkan berdasarkan judul secara alfabetis (A-Z)." << endl;
            break;
        }
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            cout << "Pilihan tidak valid." << endl;
            break;
    }
}

void FibonacciSearchGenre(const string& genre) {
    vector<Film*> films;
    Film* temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    mergeSortGenre(films, 0, films.size() - 1);

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
    string lowerGenre = toLowerCase(genre);
    bool found = false;
    int index = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        string filmGenre = toLowerCase(films[i]->genre);

        if (filmGenre < lowerGenre) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (filmGenre > lowerGenre) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            index = i;
            found = true;
            break;
        }
    }

    if (!found && fibMMm1 && offset + 1 < n && toLowerCase(films[offset + 1]->genre) == lowerGenre) {
        index = offset + 1;
        found = true;
    }

    if (found) {
        cout << "Film ditemukan:" << endl;

        int left = index - 1;
        while (left >= 0 && toLowerCase(films[left]->genre) == lowerGenre) {
            left--;
        }
        left++;

        int right = index + 1;
        while (right < n && toLowerCase(films[right]->genre) == lowerGenre) {
            right++;
        }

        for (int i = left; i < right; i++) {
            cout << "ID             : " << films[i]->id << endl;
            cout << "Judul          : " << films[i]->judul << endl;
            cout << "Genre          : " << films[i]->genre << endl;
            cout << "Tahun Rilis    : " << films[i]->tahunRilis << endl;
            cout << "------------------------------------------------" << endl;
        }
    } else {
        system("cls");
        cout << "Film dengan genre '" << genre << "' tidak ditemukan." << endl;
    }
}

void JumpSearchTahunRilis(int tahunRilis) {
    vector<Film*> films;
    Film* temp = head;
    while (temp != nullptr) {
        films.push_back(temp);
        temp = temp->next;
    }

    quickSortTahunRilis(films, 0, films.size() - 1);

    int n = films.size();
    int step = sqrt(n);
    int prev = 0;

    while (films[min(step, n) - 1]->tahunRilis < tahunRilis) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            system("cls");
            cout << "Film dengan Tahun Rilis " << tahunRilis << " tidak ditemukan." << endl;
            return;
        }
    }

    while (films[prev]->tahunRilis < tahunRilis) {
        prev++;
        if (prev == min(step, n)) {
            system("cls");
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
    system("cls");
    cout << "Film dengan Tahun Rilis " << tahunRilis << " tidak ditemukan." << endl;
}

void BoyerMooreSearchJudul(const string& judul) {
    string lowerJudul = toLowerCase(judul);
    Film* temp = head;
    bool found = false;

    while (temp != nullptr) {
        string lowerFilmJudul = toLowerCase(temp->judul);
        int n = lowerFilmJudul.size();
        int m = lowerJudul.size();

        int badChar[256];
        for (int i = 0; i < 256; i++)
            badChar[i] = -1;
        for (int i = 0; i < m; i++)
            badChar[(int)lowerJudul[i]] = i;

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && lowerJudul[j] == lowerFilmJudul[s + j])
                j--;
            if (j < 0) {
                cout << "ID             : " << temp->id << endl;
                cout << "Judul          : " << temp->judul << endl;
                cout << "Genre          : " << temp->genre << endl;
                cout << "Tahun Rilis    : " << temp->tahunRilis << endl;
                cout << "------------------------------------------------" << endl;
                found = true;
                break;
            } else {
                s += max(1, j - badChar[(int)lowerFilmJudul[s + j]]);
            }
        }
        temp = temp->next;
    }

    if (!found) {
        system("cls");
        cout << "Film dengan judul '" << judul << "' tidak ditemukan." << endl;
    }
}

void cariFilm() {
    int pilihanSearch;
    cout << "\n=== Cari Film Berdasarkan ===" << endl;
    cout << "[1] Genre (Fibonacci Search)" << endl;
    cout << "[2] Tahun Rilis (Jump Search)" << endl;
    cout << "[3] Judul (Boyer-Moore Search)" << endl;
    cout << "[0] Kembali ke menu utama" << endl;
    cout << "Pilih opsi: ";
    while (!(cin >> pilihanSearch)) {
        cout << "Input invalid. Pilih opsi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    switch (pilihanSearch) {
        case 1: {
            system("cls");
            string genre;
            cout << "Masukkan Genre film: ";
            getline(cin, genre);
            FibonacciSearchGenre(genre);
            break;
        }
        case 2: {
            system("cls");
            int tahunRilis;
            cout << "Masukkan Tahun Rilis film: ";
            while (!(cin >> tahunRilis) || tahunRilis < 1878 || tahunRilis > 2024 || cin.peek() != '\n') {
                cout << "Input invalid. Masukkan tahun rilis (1878-2024): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            JumpSearchTahunRilis(tahunRilis);
            break;
        }
        case 3: {
            system("cls");
            string judul;
            cout << "Masukkan Judul film: ";
            getline(cin, judul);
            BoyerMooreSearchJudul(judul);
            break;
        }
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            cout << "Pilihan tidak valid." << endl;
            break;
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
        cout << "[5] Tambah film ke watchlist" << endl;
        cout << "[6] Tampilkan watchlist" << endl;
        cout << "[7] Tonton film dari watchlist" << endl;
        cout << "[8] Watch history" << endl;
        cout << "[9] Urutkan film" << endl;
        cout << "[10] Cari film" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilih opsi: ";
        while (!(cin >> pilihan)) {
            cout << "Input invalid. Pilih opsi: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (pilihan) {
            case 1: {
                system("cls");
                string judul, genre;
                int tahunRilis;

                cout << "Masukkan judul film        : ";
                getline(cin, judul);
                if (judul.empty() || hanyaSpasi(judul)) {
                    system("cls");
                    cout << "Judul tidak boleh kosong atau hanya spasi!" << endl;
                    break;
                }

                cout << "Masukkan genre film        : ";
                getline(cin, genre);
                if (!cekGenre(genre)) {
                    system("cls");
                    cout << "Genre hanya boleh mengandung huruf dan tidak boleh kosong atau mengandung spasi." << endl;
                    break;
                }

                cout << "Masukkan tahun rilis film  : ";
                while (!(cin >> tahunRilis) || tahunRilis < 1878 || tahunRilis > 2024 || cin.peek() != '\n') {
                    cout << "Input invalid. Masukkan tahun rilis (1878-2024): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();

                tambahFilm(judul, genre, tahunRilis);
                break;
            }
            case 2:
                system("cls");
                tampilkanFilm();
                break;
            case 3: {
                system("cls");
                tampilkanFilm();
                int id;
                cout << "Masukkan ID film yang ingin diubah: ";
                while (!(cin >> id)) {
                    cout << "Input invalid. Masukkan ID film yang ingin diubah: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                ubahFilm(id);
                break;
            }
            case 4: {
                system("cls");
                tampilkanFilm();
                int id;
                cout << "Masukkan ID film yang ingin dihapus: ";
                while (!(cin >> id)) {
                    cout << "Input invalid. Masukkan ID film yang ingin dihapus: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                hapusFilm(id);
                break;
            }
            case 5: {
                system("cls");
                tampilkanFilm();
                int id;
                cout << "Masukkan ID film yang ingin ditambahkan ke watchlist: ";
                while (!(cin >> id)) {
                    cout << "Input invalid. Masukkan ID film yang ingin ditambahkan ke watchlist: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                Film* film = pilihID(id);
                if (film != nullptr) {
                    tambahWatchlist(film);
                } else {
                    system("cls");
                    cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
                }
                break;
            }
            case 6:
                system("cls");
                tampilkanWatchlist();
                break;
            case 7:
                system("cls");
                tontonFilm();
                break;
            case 8:
                system("cls");
                tampilkanWatchHistory();
                break;
            case 9:
                system("cls");
                sortFilm();
                break;
            case 10:
                system("cls");
                cariFilm();
                break;
            case 0:
                system("cls");
                cout << "Terima kasih telah menggunakan program ini." << endl;
                break;
            default:
                system("cls");
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihan != 0);
}

int main() {

    tambahFilm("Interstellar", "Science Fiction", 2014);
    tambahFilm("The Godfather Part II", "Drama", 1974);
    tambahFilm("Blade Runner 2049", "Science Fiction", 2017);
    tambahFilm("The Big Lebowski", "Comedy", 1998);
    tambahFilm("Heat", "Action", 1995);
    tambahFilm("La La Land", "Musical", 2016);
    tambahFilm("Psycho", "Horror", 1960);
    tambahFilm("The Dark Knight", "Action", 2008);
    tambahFilm("Dunkirk", "War", 2017);
    tambahFilm("The Shawshank Redemption", "Drama", 1994);
    tambahFilm("Pulp Fiction", "Crime", 1994);
    tambahFilm("The Social Network", "Biography", 2010);
    tambahFilm("Joker: Folie a Deux", "Musical", 2024);
    tambahFilm("Killers of the Flower Moon", "Drama", 2023);
    tambahFilm("The Batman", "Action", 2022);
    tambahFilm("Ex Machina", "Science Fiction", 2014);
    tambahFilm("The Irishman", "Biography", 2019);
    tambahFilm("Inglourious Basterds", "War", 2009);
    tambahFilm("The Matrix", "Science Fiction", 1999);
    tambahFilm("Goodfellas", "Crime", 1990);
    tambahFilm("The Shining", "Horror", 1980);
    tambahFilm("American Psycho", "Crime", 2000);
    tambahFilm("The Good, the Bad and the Ugly", "Western", 1966);
    tambahFilm("Fight Club", "Drama", 1999);
    tambahFilm("The Prestige", "Mystery", 2006);
    tambahFilm("Se7en", "Crime", 1995);
    tambahFilm("The Silence of the Lambs", "Thriller", 1991);
    tambahFilm("Lawrence of Arabia", "Adventure", 1962);
    tambahFilm("The Witch", "Horror", 2015);
    tambahFilm("Gladiator", "Action", 2000);
    tambahFilm("Call Me by Your Name", "Romance", 2017);
    tambahFilm("The Grand Budapest Hotel", "Comedy", 2014);
    tambahFilm("Revenge of the Sith", "Science Fiction", 2005);
    tambahFilm("Napoleon", "Biography", 1927);
    tambahFilm("Harry Potter and the Prisoner of Azkaban", "Fantasy", 2004);
    tambahFilm("The Lord of the Rings: The Return of the King", "Fantasy", 2003);
    tambahFilm("Nosferatu", "Horror", 1922);
    tambahFilm("Inception", "Science Fiction", 2010);
    tambahFilm("The Dark Knight Rises", "Action", 2012);
    tambahFilm("2001: A Space Odyssey", "Science Fiction", 1968);
    tambahFilm("The Lord of the Rings: The Fellowship of the Ring", "Fantasy", 2001);
    tambahFilm("Seven Samurai", "Action", 1954);
    tambahFilm("Scott Pilgrim vs. the World", "Comedy", 2010);
    tambahFilm("The Departed", "Crime", 2006);
    tambahFilm("Mad Max: Fury Road", "Action", 2015);
    tambahFilm("The Lord of the Rings: The Two Towers", "Fantasy", 2002);
    tambahFilm("Fargo", "Crime", 1996);
    tambahFilm("The Pianist", "Biography", 2002);
    tambahFilm("Her", "Romance", 2013);
    tambahFilm("Saving Private Ryan", "War", 1998);
    tambahFilm("The Truman Show", "Comedy", 1998);
    tambahFilm("Nosferatu", "Horror", 2024);
    tambahFilm("Get Out", "Horror", 2017);
    tambahFilm("The Lion King", "Adventure", 1994);
    tambahFilm("Raiders of the Lost Ark", "Adventure", 1981);
    tambahFilm("Django Unchained", "Western", 2012);
    tambahFilm("Dune", "Science Fiction", 2021);
    tambahFilm("Oppenheimer", "Biography", 2023);
    tambahFilm("The French Dispatch", "Comedy", 2021);
    tambahFilm("Zack Snyder's Justice League", "Action", 2021);

    menu();
    return 0;
}


// Made by:
// B1 - Kelompok 2
// Muhammad Naufal Fahrozi (2309106062)
// Muhammad Asadin Nur (2309106061)
// AHMADYANI (2309106055)