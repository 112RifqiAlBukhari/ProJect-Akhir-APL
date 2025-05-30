#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
const int MAX_FILM = 100;

// Warna Output

const string RED = "\033[31m";  
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";                                          
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m";

struct Film {
    int No;
    string Judul;
    string Genre;
    string Deskripsi;
    float rating = 0;
    int jumlah_rating = 0;
};

struct User {
    string username;
    string password;
    int saldo = 0;
    bool premium = false;
    time_t expire = 0; // waktu kedaluwarsa premium
};

vector<User> daftarUser = {
    {"faras", "12345", 200000, true, time(nullptr) + 30 * 24 * 60 * 60},
    {"wawan", "12345", 90000, false, 0}
};

void suscess(string* teks){
    cout  << *teks  << endl;
}

void updateUser(const User &me) {
    for (auto &u : daftarUser) {
        if (u.username == me.username) {
            u = me;
            break;
        }
    }
}

bool isKosongAtauSpasi(const string &s) {
    return s.find_first_not_of(" \t\n\r") == string::npos;
} 


vector<Film> dataFilmNonPremium;
vector<Film> dataFilmPremium;


int isi_film_Non_Premium(Film d[]);
int isi_Film_Premium(Film d[]);

void inisialisasiFilmGlobal() {
    if (!dataFilmNonPremium.empty()) return;
    Film temp[MAX_FILM];
    int jmlNP = isi_film_Non_Premium(temp);
    // isi non-premium
    for (int i = 0; i < jmlNP; i++) dataFilmNonPremium.push_back(temp[i]);
    // salin seluruh non-premium ke premium
    for (int i = 0; i < jmlNP; i++) {
        Film copy = temp[i];
        copy.No = i + 1;
        dataFilmPremium.push_back(copy);
    }
    // lalu tambahkan extra premium
    int totalP = isi_Film_Premium(temp);  // ini mengisi temp[jmlNP..totalP)
    for (int i = jmlNP; i < totalP; i++) {
        temp[i].No = dataFilmPremium.size() + 1;
        dataFilmPremium.push_back(temp[i]);
    }
}



// Utility baca pilihan integer dengan range dan error‑handling
int bacaPilihan(int minO, int maxO) {
    int x;
    while (true) {
        if (!(cin >> x) || x < minO || x > maxO) {
            cout << RED <<"|  Input tidak valid! Masukkan angka " << minO << "-" << maxO << RESET << ": ";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            return x;
        }
    }
}

//— Fungsi login_admin, isi_film_…, tampilan film, tambah/edit/hapus, dll. —
//   (SALIN persis dari kode Anda sebelumnya, tanpa diubah)

bool login_admin(string Syarat_Login[][4], int jumlahData, int percobaan) {
    if (percobaan <= 0) {
        cout << RED << "|  Anda sudah melebihi batas percobaan login.\n" << RESET;
        return false;
    }
    string u, p;
    cout << endl
         << CYAN << "==============================================\n"
         << "|" << RED << "                  LOGIN ADMIN               " << CYAN << "|\n"
         << "==============================================\n";

    // baca username
    cout << "|  Username: ";
    getline(cin, u);

    // baca password
    cout << "|  Password: ";
    getline(cin, p);

    // cek kredensial
    for (int i = 0; i < jumlahData; i++) {
        if (u == Syarat_Login[i][0] && p == Syarat_Login[i][1]) {
            cout << CYAN << "|" << GREEN << "  Login sukses!\n"
                 << CYAN << "==============================================\n"
                 << RESET;
            return true;
        }
    }
    cout << RED << "|  Login gagal!\n" << RESET;
    return login_admin(Syarat_Login, jumlahData, percobaan - 1);
}



int isi_film_Non_Premium(Film d[]) {
    d[0]  = {1,"Despicable Me","Komedi","Film animasi keluarga tentang penjahat yang berubah jadi ayah"};
    d[1]  = {2,"Inside Out","Komedi","Kisah emosi dalam kepala seorang anak perempuan"};
    d[2]  = {3,"Home Alone","Komedi","Anak kecil sendirian melawan pencuri"};
    d[3]  = {4,"Cek Toko Sebelah","Komedi","Drama keluarga tentang warisan toko"};
    d[4]  = {5,"Agak Laen","Komedi","Komedi tentang kejadian tidak biasa"};
    d[5]  = {6,"Avenger","Aksi","Pahlawan super bersatu melawan musuh besar"};
    d[6]  = {7,"Kingsman","Aksi","Agen rahasia Inggris dengan teknologi canggih"};
    d[7]  = {8,"Extraction","Aksi","Misi penyelamatan anak dari gembong narkoba"};
    d[8]  = {9,"The Conjuring","Horor","Kisah nyata pemburu hantu menghadapi iblis"};
    d[9]  = {10,"Annabelle","Horor","Boneka terkutuk yang menebar teror"};
    d[10] = {11,"Pengabdi Setan","Horor","Ibu yang kembali dari kematian"};
    d[11] = {12,"Dilan 1990","Romantis","Cinta remaja SMA di era 90-an"};
    d[12] = {13,"Mariposa","Romantis","Gadis cerdas jatuh cinta dengan pria dingin"};
    return 13;
}

int isi_Film_Premium(Film d[]) {
    int np = isi_film_Non_Premium(d);
    Film extra[] = {
        {0,"How to Make Millions Before Grandma Dies","Komedi","Cucu berpura-pura berbakti demi warisan nenek"},
        {0,"Dune","Romantis","Pewaris takhta berjuang di planet gurun yang kejam"},
        {0,"Hitman","Aksi","Pembunuh bayaran dalam misi penuh rahasia dan bahaya"},
        {0,"La la land","Romantis","Musikal romantis tentang mimpi dan cinta di Hollywood"},
        {0,"Tenggelamnya Kapal Van Der Wijck","Romantis","Cinta tak direstui dalam budaya Minang yang ketat"},
        // … (total 18 elemen sesuai daftar)
    };
    int extraCount = sizeof(extra) / sizeof(extra[0]);
    for (int i = 0; i < extraCount; i++) {
        d[np + i] = extra[i];
        d[np + i].No = np + i + 1;  // ← penomoran berlanjut
    }
    return np + extraCount;
}

void Tampilan_judul(Film d[], int jml, bool isPremium) {
    cout << left;
    cout << CYAN;
    cout << "=====================================================================================================================================\n";
    cout << "| " << (isPremium ? MAGENTA + string("FILM PREMIUM") + CYAN : GREEN + string("FILM NON-PREMIUM") + CYAN)
         << setw(97 - (isPremium ? 13 : 15)) << " |" << endl;
    cout << "=====================================================================================================================================\n";
    cout << "| No  | Judul                                              | Genre     | Deskripsi                                          | Rating |\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------\n";
    cout << RESET;
    for (int i = 0; i < jml; i++) {
        cout << (isPremium ? MAGENTA : YELLOW);
        cout << "| " << setw(3) << d[i].No
             << " | " << setw(50) << d[i].Judul
             << " | " << setw(9) << d[i].Genre
             << " | " << setw(50) << d[i].Deskripsi.substr(0, 46)
             << " | ";
        if (d[i].jumlah_rating > 0)
            cout << setw(6) << fixed << setprecision(1) << d[i].rating * 10 << "%";
        else
            cout << setw(6) << "-";
        cout << " |\n";
    }
    cout << RESET;
    cout << "=====================================================================================================================================\n";
}


Film Tambah_Film(const vector<Film> &dataNP, const vector<Film> &dataP) {
    Film f;

    // Judul
    while (true) {
        cout << CYAN << "| Judul     : " << RESET;
        getline(cin, f.Judul);

        if (isKosongAtauSpasi(f.Judul)) {
            cout << RED << "| Judul tidak boleh kosong atau hanya spasi!\n" << RESET;
            continue;
        }

        // Cek duplikasi judul
        bool ada = false;
        for (const auto &film : dataNP) {
            if (film.Judul == f.Judul) {
                ada = true;
                break;
            }
        }
        for (const auto &film : dataP) {
            if (film.Judul == f.Judul) {
                ada = true;
                break;
            }
        }    

        if (ada) {
            cout << RED << "| Judul sudah tersedia!\n" << RESET;
            continue;
        }

        break;
    }

    // Genre
    cout << YELLOW << "Pilih Genre\n" << RESET;
    cout << MAGENTA << "[1] Komedi   [2] Horor   [3] Romantis   [4] Aksi\n" << RESET;
    cout << CYAN << "| Pilih: " << RESET;
    int g = bacaPilihan(1, 4);
    switch (g) {
        case 1: f.Genre = "Komedi";   break;
        case 2: f.Genre = "Horor";    break;
        case 3: f.Genre = "Romantis"; break;
        case 4: f.Genre = "Aksi";     break;
    }

    // Deskripsi
    while (true) {
        cout << CYAN << "| Deskripsi : " << RESET;
        getline(cin, f.Deskripsi);
        if (isKosongAtauSpasi(f.Deskripsi)) {
            cout << RED << "| Deskripsi tidak boleh kosong atau hanya spasi!\n" << RESET;
        } else if (f.Deskripsi.length() > 45) {
            cout << RED << "| Deskripsi terlalu panjang (maks 45 karakter)\n" << RESET;
        } else {
            break;
        }
    }
    f.rating = 0;
    f.jumlah_rating = 0;
    return f;
}

void edit_Film(Film d[], int jml) {
    cout << CYAN << "| Masukkan No film yang diedit: " << RESET;
    int no = bacaPilihan(1, jml);
    Film &f = d[no - 1];

    string tmp;

    // ===================== JUDUL ======================
    while (true) {
        cout << CYAN << "| Judul (" << YELLOW << f.Judul << CYAN << "): " << RESET;
        getline(cin, tmp);

        // Jika kosong, pertahankan nilai lama
        if (isKosongAtauSpasi(tmp)) {
            cout << RED << "| Judul tidak boleh kosong!\n" << RESET;
            continue;
        }

        // Cek duplikasi, kecuali dirinya sendiri
        bool ada = false;
        for (int i = 0; i < jml; i++) {
            if (i != no - 1 && d[i].Judul == tmp) {
                ada = true;
                break;
            }
        }

        if (ada) {
            cout << RED << "| Judul sudah dipakai film lain!\n" << RESET;
            continue;
        }

        // Lolos semua pengecekan
        f.Judul = tmp;
        break;
    }
    // ===================== GENRE ======================
    cout << CYAN << "| Genre (" << MAGENTA << f.Genre << CYAN << ") - Pilih:\n" << RESET;
    cout << MAGENTA << "   [1] Komedi   [2] Horor   [3] Romantis   [4] Aksi\n" << RESET;
    cout << CYAN << "| Pilih: " << RESET;
    int g = bacaPilihan(1, 4);
    switch (g) {
        case 1: f.Genre = "Komedi";    break;
        case 2: f.Genre = "Horor";     break;
        case 3: f.Genre = "Romantis";  break;
        case 4: f.Genre = "Aksi";      break;
    }
    // ===================== DESKRIPSI ======================
    while (true) {
        cout << CYAN << "| Deskripsi : " << RESET;
        getline(cin, tmp);
        if (isKosongAtauSpasi(tmp)) {
            cout << RED << "| Deskripsi tidak boleh kosong!\n" << RESET;
        } else if (tmp.length() > 45) {
            cout << RED << "| Deskripsi terlalu panjang (maks 45 karakter).\n" << RESET;
        } else {
            f.Deskripsi = tmp;
            break;
        }
    }
    cout << GREEN << "| Film berhasil diupdate!                 |\n" << RESET;
    cout << CYAN << "--------------------------------------------\n" << RESET;
}


void lihat_pengguna() {
    cout << CYAN <<"==================== DAFTAR PENGGUNA ====================\n";
    cout << "| " << setw(20) << "Username" 
         << "| " << setw(10) << "Saldo" 
         << "| " << setw(10) << "Status" << " |\n";
    cout << "---------------------------------------------------------\n";
    for (auto &u : daftarUser) {
        cout << "| " << YELLOW << setw(20) << u.username << RESET
             << "| " << GREEN << "Rp" << setw(8) << u.saldo << RESET
             << "| " << (u.premium ? MAGENTA : CYAN) << setw(10) << (u.premium ? "Premium" : "Free") << RESET << " |\n";
    }
    cout << CYAN << "=========================================================\n\n" << RESET;
}

void Menu_admin(string Syarat_Login[][4], int jumlahData) {
    if (!login_admin(Syarat_Login, jumlahData, 1)) return;
    while (true) {
        cout << CYAN << "==================== MENU ADMIN ====================\n" << RESET;
        cout << "| " << YELLOW << "[1] Lihat Pengguna" << CYAN << "                               |\n" << RESET;
        cout << "| " << YELLOW << "[2] Lihat Semua Film" << CYAN << "                             |\n" << RESET;
        cout << "| " << YELLOW << "[3] Tambah Film Baru" << CYAN << "                             |\n" << RESET;
        cout << "| " << YELLOW << "[4] Edit Film" << CYAN << "                                    |\n" << RESET;
        cout << "| " << YELLOW << "[5] Hapus Film" << CYAN << "                                   |\n" << RESET;
        cout << "| " << YELLOW << "[6] Exit" << CYAN << "                                         |\n" << RESET;
        cout << CYAN << "===================================================\n" << RESET;
        cout << "| Pilihan: "; 
        int pil = bacaPilihan(1,6);
        cout << CYAN << "===================================================\n" << RESET;
        switch (pil) {
            case 1: lihat_pengguna(); break;
            case 2: 
                Tampilan_judul(dataFilmNonPremium.data(),
                           dataFilmNonPremium.size(),
                           false);
                Tampilan_judul(dataFilmPremium.data(),
                           dataFilmPremium.size(),
                           true);
                break;
            case 3: {
                while (true) {
                    cout << MAGENTA << "| 1. Tambah ke Premium saja                        |\n" << RESET;
                    cout << MAGENTA << "| 2. Tambah ke Keduanya (Premium & Non-Premium)    |\n" << RESET;
                    cout << RED     << "| 3. Batal / Kembali                                |\n" << RESET;
                    cout << CYAN    << "---------------------------------------------------\n" << RESET;
                    cout << "| Pilih: ";
                    int opsi = bacaPilihan(1, 3);
                    cout << CYAN << "---------------------------------------------------\n" << RESET;

                    if (opsi == 3) {
                        // batal, langsung kembali ke menu Admin
                        cout << GREEN << "|         Kembali ke menu Admin!                |\n" << RESET;
                        cout << CYAN << "--------------------------------------------------\n" << RESET;
                        break;
                    }

                    // --- Tampilkan film yang sudah ada sesuai opsi ---
                    if (opsi == 1) {
                        // Hanya daftar Premium
                        cout << CYAN << ">> Daftar Film Premium Saat Ini:\n" << RESET;
                        Tampilan_judul(dataFilmPremium.data(),
                                    dataFilmPremium.size(),
                                    true);
                    } else {
                        // Daftar Non-Premium + Premium
                        cout << CYAN << ">> Daftar Film Non-Premium Saat Ini:\n" << RESET;
                        Tampilan_judul(dataFilmNonPremium.data(),
                                    dataFilmNonPremium.size(),
                                    false);
                        cout << CYAN << ">> Daftar Film Premium Saat Ini:\n" << RESET;
                        Tampilan_judul(dataFilmPremium.data(),
                                    dataFilmPremium.size(),
                                    true);
                    }

                    // --- Proses input data film baru ---
                    Film f = Tambah_Film(dataFilmNonPremium, dataFilmPremium);

                    // --- Simpan film baru sesuai opsi ---
                    if (opsi == 1) {
                        // ke Premium saja
                        f.No = dataFilmPremium.size() + 1;
                        dataFilmPremium.push_back(f);
                        cout << GREEN << "| Film berhasil ditambahkan ke Premium!           |\n" << RESET;
                    } else {
                        // ke kedua list
                        f.No = dataFilmNonPremium.size() + 1;
                        dataFilmNonPremium.push_back(f);
                        Film fCopy = f;
                        fCopy.No = dataFilmPremium.size() + 1;
                        dataFilmPremium.push_back(fCopy);
                        cout << GREEN << "| Film berhasil ditambahkan ke Non-Premium & Premium! |\n" << RESET;
                    }

                    // --- Ringkasan data baru ---
                    cout << CYAN << "---------------------------------------------------\n" << RESET;
                    cout << CYAN << "| DATA FILM TERSIMPAN:                            |\n" << RESET;
                    cout << CYAN << "---------------------------------------------------\n" << RESET;
                    cout << "| Judul     : " << YELLOW << f.Judul << RESET << "\n";
                    cout << "| Genre     : " << YELLOW << f.Genre << RESET << "\n";
                    cout << "| Deskripsi : " << YELLOW << f.Deskripsi << RESET << "\n";
                    cout << CYAN << "---------------------------------------------------\n" << RESET;

                  
                    break;
                }
                break;
            }


            case 4: {
                cout << MAGENTA << "| 1. Edit Film Premium             |\n" << RESET;
                cout << MAGENTA << "| 2. Edit Film Non-Premium         |\n" << RESET;
                cout << RED     << "| 3. Batal / Kembali               |\n" << RESET;
                cout << CYAN    << "---------------------------------------------------\n" << RESET;
                cout << "| Pilih: ";
                int s = bacaPilihan(1, 3);
                cout << CYAN    << "---------------------------------------------------\n" << RESET;

                if (s == 3) {
                    // batal, langsung kembali ke menu Admin
                    cout << GREEN << "|         Kembali ke menu Admin!                |\n" << RESET;
                    cout << CYAN << "--------------------------------------------------\n" << RESET;
                    break;
                }

                if (s == 1) {
                    // Edit hanya di daftar premium
                    Tampilan_judul(dataFilmPremium.data(),
                                dataFilmPremium.size(),
                                true);
                    // Edit via array temporer untuk fungsi edit_Film
                    // Sederhananya, kita copy ke buffer lokal:
                    static Film bufP[MAX_FILM];
                    int cntP = dataFilmPremium.size();
                    for (int i = 0; i < cntP; ++i) bufP[i] = dataFilmPremium[i];
                    
                    edit_Film(bufP, cntP);

                    // Setelah edit selesai, salin kembali ke vector
                    for (int i = 0; i < cntP; ++i)
                        dataFilmPremium[i] = bufP[i];

                } else {
                    // Edit hanya di daftar non-premium
                    Tampilan_judul(dataFilmNonPremium.data(),
                                dataFilmNonPremium.size(),
                                false);
                    static Film bufNP[MAX_FILM];
                    int cntNP = dataFilmNonPremium.size();
                    for (int i = 0; i < cntNP; ++i) bufNP[i] = dataFilmNonPremium[i];

                    edit_Film(bufNP, cntNP);

                    for (int i = 0; i < cntNP; ++i)
                        dataFilmNonPremium[i] = bufNP[i];
                }

                cout << CYAN << "-----------------------------------\n" << RESET;
                break;
            }
            case 5: {
                cout << MAGENTA << "| 1. Hapus di Premium saja                       |\n" << RESET;
                cout << MAGENTA << "| 2. Hapus di Non-Premium saja                   |\n" << RESET;
                cout << RED     << "| 3. Batal / Kembali                             |\n" << RESET;
                cout << CYAN << "-------------------------------------------------\n" << RESET;
                cout << "| Pilih: "; 
                int s = bacaPilihan(1, 3);
                cout << CYAN << "-------------------------------------------------\n" << RESET;

                    if (s == 3) {
                        // batal, langsung kembali ke menu Admin
                        cout << GREEN << "|         Kembali ke menu Admin!                |\n" << RESET;
                        cout << CYAN << "-------------------------------------------------\n" << RESET;
                        break;
                    }

                    if (s == 1) {
                        // Tampilkan langsung dari vector
                        Tampilan_judul(dataFilmPremium.data(),
                                    dataFilmPremium.size(),
                                    true);
                        
                        // Pilih no yang akan dihapus
                        cout << CYAN << "| Masukkan No film yang dihapus: " << RESET;
                        int no = bacaPilihan(1, dataFilmPremium.size());
                        
                        // Hapus dari vector
                        dataFilmPremium.erase(dataFilmPremium.begin() + (no - 1));
                        
                        // Perbarui penomoran
                        for (int i = 0; i < dataFilmPremium.size(); ++i)
                            dataFilmPremium[i].No = i + 1;

                        cout << GREEN << "| Film berhasil dihapus dari Premium!           |\n" << RESET;
                    }
                    else {
                        Tampilan_judul(dataFilmNonPremium.data(),
                                    dataFilmNonPremium.size(),
                                    false);
                        cout << CYAN << "| Masukkan No film yang dihapus: " << RESET;
                        int no = bacaPilihan(1, dataFilmNonPremium.size());
                        dataFilmNonPremium.erase(dataFilmNonPremium.begin() + (no - 1));
                        for (int i = 0; i < dataFilmNonPremium.size(); ++i)
                            dataFilmNonPremium[i].No = i + 1;
                        cout << GREEN << "| Film berhasil dihapus dari Non-Premium!       |\n" << RESET;
                    }
                    cout << CYAN << "-------------------------------------------------\n" << RESET;
                    break;
                }
            case 6: 
                cout << GREEN << "| Kembali ke menu utama                           |\n" << RESET
                     << CYAN << "===================================================\n" << RESET;
                return;
        }
    }
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----- User & Film Non‑Premium -----

bool validasiUsername(const string &un) {
    return !isKosongAtauSpasi(un);  
}

bool validasiPassword(const string &pw) {
    return pw.length() > 5; 
}

int cari_film_dengan_judul(const vector<Film>& daftar, const string& keyword) {
    for (int i = 0; i < daftar.size(); ++i) {
        if (daftar[i].Judul.find(keyword) != string::npos) {
            return i;
        }
    }
    return -1;
}


void daftar_user() {
    cout << CYAN << "================== DAFTAR AKUN ==================\n" << RESET;

    string un;
    while (true) {
        cout << CYAN << "| Username: " << RESET;
        getline(cin, un);

        if (!validasiUsername(un)) {
            cout << RED << "| Username tidak boleh kosong atau hanya spasi!\n" << RESET;
            continue;
        }

        // Cek apakah username sudah dipakai (abaikan besar kecil huruf)
        bool sudahAda = false;
        for (auto &x : daftarUser) {
            string a = x.username;
            string b = un;
            transform(a.begin(), a.end(), a.begin(), ::tolower);
            transform(b.begin(), b.end(), b.begin(), ::tolower);

            if (a == b) {
                cout << RED << "| Username sudah digunakan!                    |\n" << RESET;
                sudahAda = true;
                break;
            }
        }

        if (!sudahAda) break;
    }

    string pw;
    while (true) {
        cout << CYAN << "| Password: " << RESET;
        getline(cin, pw);
        if (!validasiPassword(pw)) {
            cout << RED << "| Password harus lebih dari 5 karakter!\n" << RESET;
        } else {
            break;
        }
    }

    daftarUser.push_back({un, pw, 0, false});
    cout << GREEN << "| Akun berhasil dibuat!                           |\n" << RESET;
    cout << CYAN << "==================================================\n\n" << RESET;
}

bool login_user(User &me) {
    cout << CYAN << "=================== LOGIN USER ===================\n" << RESET;
    cout << CYAN << "| Username: " << RESET; string un; getline(cin,un);
    cout << CYAN << "| Password: " << RESET; string pw; getline(cin,pw);
    for (auto &x: daftarUser) {
        if (x.username == un && x.password == pw) {
            me = x;
            cout << GREEN << "| Login sukses!                                  |\n" << RESET;
            cout << CYAN << "==================================================\n\n" << RESET;
            return true;
        }
    }
    cout << RED << "| Login gagal!                                   |\n" << RESET;
    cout << CYAN << "==================================================\n\n" << RESET;
    return false;
}

void lihat_Film_Non_Premium() {
    Film arr[MAX_FILM];
    int j = isi_film_Non_Premium(arr);
    Tampilan_judul(arr,j,false);
}

void tonton_Film_Non_Premium() {
    Tampilan_judul(dataFilmNonPremium.data(), dataFilmNonPremium.size(), false);

    char cari;
    while (true) {
        cout << CYAN << "| Ingin mencari film berdasarkan judul? (y/n): " << RESET;
        string input;
        getline(cin, input);
        // Hanya terima satu karakter y/n, tidak boleh kosong/spasi
        if (input.length() == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
            cari = tolower(input[0]);
            break;
        }
        cout << RED << "| Input tidak valid. Masukkan 'y' atau 'n'.\n" << RESET;
    }

    int index = -1;
    if (cari == 'y') {
        cout << CYAN << "| Masukkan kata kunci judul: " << RESET;
        string keyword;
        getline(cin, keyword);
        if (isKosongAtauSpasi(keyword)) {
            cout << RED << "| Kata kunci tidak boleh kosong!\n" << RESET;
            return;
        }
        index = cari_film_dengan_judul(dataFilmNonPremium, keyword);
        if (index == -1) {
            cout << RED << "| Film tidak ditemukan!\n" << RESET;
            return;
        }
        cout << GREEN << "| Film ditemukan: " << dataFilmNonPremium[index].Judul << "\n" << RESET;
    } else {
        cout << CYAN << "| Masukkan No film yang ingin ditonton: " << RESET;
        int no = bacaPilihan(1, dataFilmNonPremium.size());
        index = no - 1;
    }

    Film &f = dataFilmNonPremium[index];
    cout << GREEN << "| Menonton: " << YELLOW << f.Judul << RESET << "\n";

    char jawab;
    while (true) {
        cout << CYAN << "| Ingin memberi rating? (y/n): " << RESET;
        string input;
        getline(cin, input);
        if (input.length() == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
            jawab = tolower(input[0]);
            break;
        }
        cout << RED << "| Input tidak valid. Masukkan 'y' atau 'n'.\n" << RESET;
    }

    if (jawab == 'y') {
        cout << CYAN << "| Beri rating (1 sampai 10): " << RESET;
        int rt = bacaPilihan(1, 10);
        f.rating = (f.rating * f.jumlah_rating + rt) / (++f.jumlah_rating);
        cout << GREEN << "| Terima kasih! Rating disimpan.\n" << RESET;
    } else {
        cout << YELLOW << "| Tidak memberi rating.\n" << RESET;
    }

    cout << CYAN << "==================================================\n\n" << RESET;
}

void tonton_Film_Premium() {
    // Gabungkan semua film (non-premium + premium, tanpa duplikat judul)
    vector<Film> semua = dataFilmNonPremium;
    for (const auto& f : dataFilmPremium) {
        bool duplikat = false;
        for (const auto& x : semua) {
            if (x.Judul == f.Judul) {
                duplikat = true;
                break;
            }
        }
        if (!duplikat) semua.push_back(f);
    }
    // Perbarui nomor urut
    for (int i = 0; i < semua.size(); ++i) semua[i].No = i + 1;

    Tampilan_judul(semua.data(), semua.size(), true);

    char cari;
    while (true) {
        cout << CYAN << "| Ingin mencari film berdasarkan judul? (y/n): " << RESET;
        string input;
        getline(cin, input);
        if (input.length() == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
            cari = tolower(input[0]);
            break;
        }
        cout << RED << "| Input tidak valid. Masukkan 'y' atau 'n'.\n" << RESET;
    }

    int index = -1;
    if (cari == 'y') {
        cout << CYAN << "| Masukkan kata kunci judul: " << RESET;
        string keyword;
        getline(cin, keyword);
        if (isKosongAtauSpasi(keyword)) {
            cout << RED << "| Kata kunci tidak boleh kosong!\n" << RESET;
            return;
        }
        index = cari_film_dengan_judul(semua, keyword);
        if (index == -1) {
            cout << RED << "| Film tidak ditemukan!\n" << RESET;
            return;
        }
        cout << GREEN << "| Film ditemukan: " << YELLOW << semua[index].Judul << RESET << "\n";
    } else {
        cout << CYAN << "| Masukkan No film yang ingin ditonton: " << RESET;
        int no = bacaPilihan(1, semua.size());
        index = no - 1;
    }

    Film &f = semua[index];
    cout << GREEN << "| Menonton: " << YELLOW << f.Judul << RESET << "\n";

    char jawab;
    while (true) {
        cout << CYAN << "| Ingin memberi rating? (y/n): " << RESET;
        string input;
        getline(cin, input);
        if (input.length() == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
            jawab = tolower(input[0]);
            break;
        }
        cout << RED << "| Input tidak valid. Masukkan 'y' atau 'n'.\n" << RESET;
    }

    if (jawab == 'y') {
        cout << CYAN << "| Beri rating (1 sampai 10): " << RESET;
        int rt = bacaPilihan(1, 10);

        // Update rating di sumber data aslinya (non-premium dan premium)
        bool updated = false;
        for (auto& film : dataFilmNonPremium) {
            if (film.Judul == f.Judul) {
                film.rating = (film.rating * film.jumlah_rating + rt) / (++film.jumlah_rating);
                updated = true;
            }
        }
        for (auto& film : dataFilmPremium) {
            if (film.Judul == f.Judul) {
                film.rating = (film.rating * film.jumlah_rating + rt) / (++film.jumlah_rating);
                updated = true;
            }
        }
        cout << GREEN << "| Terima kasih! Rating disimpan.\n" << RESET;
    } else {
        cout << YELLOW << "| Tidak memberi rating.\n" << RESET;
    }

    cout << CYAN << "==================================================\n\n" << RESET;
}

void tampilkan_Film_Terlaris(Film d[], int jml) {
    vector<Film> v(d, d + jml);

    // Urutkan dari rating besar ke kecil (descending)
    sort(v.begin(), v.end(), [](const Film &a, const Film &b) {
        return a.rating > b.rating;
    });

    cout << left;
    cout << CYAN << "=================================================================================\n";
    cout << "| " << setw(4) << "No"
         << "| " << setw(30) << "Judul Film"
         << "| " << setw(20) << "Genre"
         << "| " << setw(20) << "Rating (%)"
         << "|\n";
    cout << "=================================================================================\n" << RESET;

    // Tampilkan semua film, yang sudah dirating akan otomatis di atas
    for (const auto &f : v) {
        if (f.jumlah_rating > 0)
            cout << GREEN;
        else
            cout << YELLOW;
        cout << "| " << setw(4) << f.No
             << "| " << setw(30) << f.Judul
             << "| " << setw(20) << f.Genre
             << "| ";
        if (f.jumlah_rating > 0)
            cout << setw(14) << fixed << setprecision(1) << f.rating * 10 << "%";
        else
            cout << setw(14) << "-";
        cout << "|\n";
        cout << RESET;
    }

    cout << CYAN << "=================================================================================\n\n" << RESET;
}

void tampilkan_Semua_Film_Terlaris() {
    vector<Film> semua = dataFilmNonPremium;
    // Gabungkan film premium yang belum ada di non-premium (hindari duplikat judul)
    for (const auto& f : dataFilmPremium) {
        bool duplikat = false;
        for (const auto& x : semua) {
            if (x.Judul == f.Judul) {
                duplikat = true;
                break;
            }
        }
        if (!duplikat) semua.push_back(f);
    }

    // Urutkan dari rating tertinggi ke terendah
    sort(semua.begin(), semua.end(), [](const Film &a, const Film &b) {
        return a.rating > b.rating;
    });

    // Lebar kolom
    const int wNo = 4;
    const int wJudul = 40;
    const int wGenre = 12;
    const int wRating = 12;

    // Header
    cout << MAGENTA
         << string(wNo + wJudul + wGenre + wRating + 13, '=') << RESET << endl;
    cout << CYAN << "| "
         << setw(wNo) << left << "No"
         << " | " << setw(wJudul) << left << "Judul"
         << " | " << setw(wGenre) << left << "Genre"
         << " | " << setw(wRating) << left << "Rating (%)"
         << " |" << RESET << endl;
    cout << CYAN
         << "|" << string(wNo + 2, '-')
         << "|" << string(wJudul + 2, '-')
         << "|" << string(wGenre + 2, '-')
         << "|" << string(wRating + 2, '-')
         << "|" << RESET << endl;

    // Isi tabel
    for (const auto &f : semua) {
        cout << (f.jumlah_rating > 0 ? GREEN : YELLOW);
        cout << "| " << setw(wNo) << left << f.No
             << " | " << setw(wJudul) << left << f.Judul.substr(0, wJudul)
             << " | " << setw(wGenre) << left << f.Genre.substr(0, wGenre)
             << " | ";
        if (f.jumlah_rating > 0)
            cout << setw(wRating - 1) << right << fixed << setprecision(1) << f.rating * 10 << "%";
        else
            cout << setw(wRating - 1) << right << "-";
        cout << " |" << RESET << endl;
    }

    cout << MAGENTA
         << string(wNo + wJudul + wGenre + wRating + 13, '=') << RESET << endl << endl;
}



void isi_saldo(User &me) {
    cout << CYAN << "================== ISI SALDO ====================\n" << RESET;
    cout << "| Saldo saat ini: " << GREEN << "Rp" << me.saldo << RESET << "\n";
    cout << "| Tambah (max 1.000.000): " << YELLOW << "Rp";

    long long x;
    cin >> x;
    cout << RESET;

    if (cin.fail() || x <= 0 || x > 1000000) {
        cin.clear(); // reset error state
        cin.ignore(10000, '\n'); // buang input yang salah
        cout << RED << "| Input invalid atau melebihi batas!\n" << RESET;
    } else if (me.saldo + x > 1000000) {
        cout << RED << "| Total saldo tidak boleh lebih dari Rp1.000.000!\n" << RESET;
    } else {
        me.saldo += static_cast<int>(x);
        cout << GREEN << "| Saldo baru: Rp" << me.saldo << RESET << "\n";
    }

    cout << CYAN << "=================================================\n\n" << RESET;
    updateUser(me);
}

void tampilkan_semua_film_mode_premium() {
    vector<Film> semua = dataFilmNonPremium;

    for (const auto& f : dataFilmPremium) {
        bool duplikat = false;
        for (const auto& x : semua) {
            if (x.Judul == f.Judul) {
                duplikat = true;
                break;
            }
        }
        if (!duplikat) semua.push_back(f);
    }

    for (int i = 0; i < semua.size(); ++i) {
        semua[i].No = i + 1;
    }

    cout << MAGENTA << "===================== SEMUA FILM (PREMIUM) =====================\n" << RESET;
    Tampilan_judul(semua.data(), semua.size(), true);
}


// Menu user terpisah
void menu_user(User &me);

void menu_user_luar() {
    while (true) {
        cout << CYAN << "=============== MENU USER ===============" << RESET << endl;
        cout << "| " << YELLOW << "[1] Daftar Akun" << CYAN << "                       |\n" << RESET;
        cout << "| " << YELLOW << "[2] Login Akun" << CYAN << "                        |\n" << RESET;
        cout << "| " << YELLOW << "[3] Kembali ke Menu Utama" << CYAN << "             |\n" << RESET;
        cout << CYAN << "========================================" << RESET << endl;
        cout << "| Pilihan: ";
        int pilih = bacaPilihan(1, 3);
        cout << CYAN << "========================================" << RESET << endl;
        if (pilih == 1) {
            daftar_user();
        }
        else if (pilih == 2) {
            int percobaan = 0;
            User me;
            while (percobaan < 3) {
                if (login_user(me)) {
                    menu_user(me);      
                    break;
                } else {
                    percobaan++;
                    if (percobaan < 3) {
                        cout << YELLOW << "| Coba lagi. Sisa percobaan: " << 3 - percobaan << RESET << endl;
                    } else {
                        cout << RED << "| Anda gagal login 3 kali. Kembali ke menu user." << RESET << endl;
                    }
                }
            }
        }
        else {
            cout << GREEN << "| Kembali ke Menu Utama..." << RESET << endl;
            break;
        }
    }
}

void menu_user(User &me) {
    while (true) {
        cout << CYAN << "================== MENU PENGGUNA ==================" << RESET << endl;
        cout << "| " << YELLOW << "[1] Lihat Menu Film" << CYAN << "                               |\n" << RESET;
        cout << "| " << YELLOW << "[2] Memulai Film & Rating" << CYAN << "                         |\n" << RESET;
        cout << "| " << YELLOW << "[3] Lihat Film Rating Tertinggi" << CYAN << "                   |\n" << RESET;
        cout << "| " << YELLOW << "[4] Isi Saldo" << CYAN << "                                     |\n" << RESET;
        cout << "| " << YELLOW << "[5] Upgrade Premium" << CYAN << "                               |\n" << RESET;
        cout << "| " << YELLOW << "[6] Cek Status Akun" << CYAN << "                               |\n" << RESET;
        cout << "| " << MAGENTA << "[7] Masuk Mode Premium" << CYAN << "                            |\n" << RESET;
        cout << "| " << RED << "[8] Logout" << CYAN << "                                        |\n" << RESET;
        cout << CYAN << "====================================================" << RESET << endl;
        cout << "| Pilihan: ";
        int pil = bacaPilihan(1,8);
        cout << CYAN << "====================================================" << RESET << endl;
        
        switch (pil) {
            case 1:
                Tampilan_judul(dataFilmNonPremium.data(), dataFilmNonPremium.size(), false);
                break;
            case 2:
                tonton_Film_Non_Premium();
                break;
            case 3:
                tampilkan_Film_Terlaris(dataFilmNonPremium.data(), dataFilmNonPremium.size());
                break;
            case 4:
                isi_saldo(me);
                break;
            case 5: {
                cout << MAGENTA << "| Paket Langganan Premium:                      |\n";
                cout << "| 1. Seminggu (Rp86.000)                        |\n";
                cout << "| 2. Sebulan (Rp186.000)                        |\n" << RESET;
                cout << CYAN << "| Pilihan: " << RESET;
                int opsi = bacaPilihan(1, 2);
                int biaya = (opsi == 1) ? 86000 : 186000;
                int durasi = (opsi == 1) ? 7 : 30;
                if (me.saldo >= biaya) {
                    me.saldo -= biaya;
                    me.premium = true;
                    me.expire = time(nullptr) + durasi * 24 * 60 * 60;
                    updateUser(me);
                    cout << GREEN << "| Langganan berhasil. Premium aktif hingga: ";
                    char buf[20]; strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&me.expire));
                    cout << buf << RESET << endl;
                } else {
                    cout << RED << "| Saldo tidak mencukupi." << RESET << endl;
                }
                cout << CYAN << "====================================================\n\n" << RESET;
                break;
            }
            case 6: {
                cout << CYAN << "================= STATUS AKUN =====================" << RESET << endl;
                cout << "| Username: " << YELLOW << me.username << RESET << endl;
                cout << "| Saldo   : " << GREEN << "Rp" << me.saldo << RESET << endl;
                cout << "| Status  : " << (me.premium && me.expire > time(nullptr) ? MAGENTA + string("Premium") + RESET : CYAN + string("Free") + RESET) << endl;
                if (me.premium && me.expire > time(nullptr)) {
                    char buf[20]; strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&me.expire));
                    cout << "| Expire  : " << YELLOW << buf << RESET << endl;
                }
                cout << CYAN << "====================================================\n\n" << RESET;
                break;
            }
            case 7:
                if (me.premium && me.expire <= time(nullptr)) {
                    me.premium = false;
                    updateUser(me);
                    cout << RED << "| Masa aktif Premium Anda telah habis.           |\n";
                    cout << "| Silakan upgrade ulang untuk akses Premium.     |\n";
                    cout << "====================================================\n\n" << RESET;
                    break;
                }
                if (!me.premium) {
                    cout << YELLOW << "| Silakan upgrade dulu!                           |\n";
                    cout << "====================================================\n\n" << RESET;
                } else {
                    int sub;
                    // Film np[MAX_FILM], p[MAX_FILM];
                    // int cntNP = isi_film_Non_Premium(np);
                    // int cntP  = isi_Film_Premium(p);
                    do {
                        cout << MAGENTA << "=============== MODE PREMIUM =================" << RESET << endl;
                        cout << "| " << CYAN << "[1] Lihat Menu Film" << MAGENTA << "                        |\n" << RESET;
                        cout << "| " << CYAN << "[2] Memulai Film" << MAGENTA << "                           |\n" << RESET;
                        cout << "| " << CYAN << "[3] Lihat Film Rating Tertinggi" << MAGENTA << "            |\n" << RESET;
                        cout << "| " << RED << "[4] Kembali" << MAGENTA << "                                |\n" << RESET;
                        cout << MAGENTA << "==============================================" << RESET << endl;
                        cout << "| Pilih: ";
                        sub = bacaPilihan(1,4);
                        cout << MAGENTA << "==============================================" << RESET << endl;
                        switch (sub) {
                            case 1:
                                tampilkan_semua_film_mode_premium();
                                break;
                            case 2:
                                tonton_Film_Premium();
                                break;
                            case 3:
                                tampilkan_Semua_Film_Terlaris();
                                break;
                        }
                    } while (sub != 4);
                }
                break;
            case 8:
                cout << GREEN << "| Logout berhasil.                             |\n";
                cout << CYAN << "================================================\n\n" << RESET;
                return;
        }
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){
    string syarat_login[4][4] = {
        {"ikhsan","118"},
        {"rifqi","112"},
        {"rizky","113"},
        {"dzaki","106"}
    };
   int jumlah_login = sizeof(syarat_login) / sizeof(syarat_login[0]);
    inisialisasiFilmGlobal();

    while (true) {
        cout << CYAN <<"==============================================\n";
        cout << "|"<< GREEN <<"              SELAMAT DATANG (0_0)          "<< CYAN <<"|\n";
        cout << "==============================================\n";
        cout << "| Menu:                                      |\n";
        cout << "|"<< GREEN <<" [1] Admin                                  "<< CYAN <<"|\n";
        cout << "|"<< GREEN <<" [2] User                                   "<< CYAN <<"|\n";
        cout << "|"<< GREEN <<" [3] Exit                                   "<< CYAN <<"|\n";
        cout << "==============================================\n";
        cout << "| Pilihan: ";

        // GANTI CIN >> M dengan bacaPilihan(1,3)
        int m = bacaPilihan(1, 3);

        cout << "==============================================\n";

        if (m == 1) {
            Menu_admin(syarat_login, jumlah_login);
        } else if (m == 2) {
            menu_user_luar();
        } else { // m == 3
            cout << "|"<< GREEN <<" Terima kasih telah menggunakan program!    "<< CYAN <<"|\n";
            cout << "==============================================\n"<< RESET;
            break;
        }
    }

    return 0;
}