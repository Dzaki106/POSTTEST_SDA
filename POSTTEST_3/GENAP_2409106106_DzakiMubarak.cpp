#include <iostream>
#include <string>
using namespace std;

struct Jadwal {
    string kode;
    string tujuan;
    string waktuTerbang;
    string status;
};

struct Node {
    Jadwal data;
    Node* prev;
    Node* next;
};

class FlightSystem {
private:
    Node* head;
    Node* tail;
    string nim;
    string nama;
    int counter;
    int digitAkhir;
    
    bool isValidTime(const string& waktu) {
        if (waktu.length() != 5 || waktu[2] != ':') return false;
        
        string jamStr = waktu.substr(0, 2);
        string menitStr = waktu.substr(3, 2);
        
        for (char c : jamStr) if (c < '0' || c > '9') return false;
        for (char c : menitStr) if (c < '0' || c > '9') return false;
        
        int jam = stoi(jamStr);
        int menit = stoi(menitStr);
        return (jam >= 0 && jam <= 23) && (menit >= 0 && menit <= 59);
    }
    
    string toLower(string str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] = str[i] + 32;
            }
        }
        return str;
    }
    
    int hitungPanjangList() {
        int count = 0;
        Node* current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }
    
public:
    FlightSystem(string n, string nm) { 
        head = NULL;
        tail = NULL;
        nim = n;
        nama = nm; 
        counter = 1;
        digitAkhir = n[n.length()-1] - '0';
    }
    
    ~FlightSystem() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    string generateKode() {
        string tigaDigit = nim.substr(nim.length()-3, 3);
        string kode;
        
        if (counter == 1) {
            kode = "JT-" + tigaDigit;
        } else {
            kode = "JT-" + tigaDigit + "-" + to_string(counter-1);
        }
        counter++;
        return kode;
    }
    
    void tambahAwal() {
        string tujuan, waktu;
        cout << "Tujuan penerbangan: ";
        cin.ignore();
        getline(cin, tujuan);
        cout << "Waktu terbang (waktu:00:00): ";
        cin >> waktu;
        
        if (!isValidTime(waktu)) {
            cout << "Format waktu tidak valid!" << endl;
            return;
        }
        
        string kode = generateKode();
        Node* baru = new Node();
        baru->data.kode = kode;
        baru->data.tujuan = tujuan;
        baru->data.waktuTerbang = waktu;
        baru->data.status = "OnTime";
        baru->prev = NULL;
        baru->next = NULL;
        
        if (head == NULL) {
            head = baru;
            tail = baru;
        } else {
            baru->next = head;
            head->prev = baru;
            head = baru;
        }
        cout << "Berhasil tambah " << kode << endl;
    }
    
    void tambahAkhir() {
        string tujuan, waktu;
        cout << "Tujuan penerbangan: ";
        cin.ignore();
        getline(cin, tujuan);
        cout << "Waktu terbang (contoh: 14:30): ";
        cin >> waktu;
        
        if (!isValidTime(waktu)) {
            cout << "Format waktu tidak valid!" << endl;
            return;
        }
        
        string kode = generateKode();
        Node* baru = new Node();
        baru->data.kode = kode;
        baru->data.tujuan = tujuan;
        baru->data.waktuTerbang = waktu;
        baru->data.status = "OnTime";
        baru->prev = NULL;
        baru->next = NULL;
        
        if (head == NULL) {
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
        cout << "Berhasil tambah " << kode << endl;
    }
    
    void tambahSpesifik() {
        int panjang = hitungPanjangList();
        int posisi;
        
        cout << "Masukkan posisi (1-" << panjang + 1 << "): ";
        cin >> posisi;
        
        if (posisi < 1 || posisi > panjang + 1) {
            cout << "Posisi tidak valid!" << endl;
            return;
        }
        
        string tujuan, waktu;
        cout << "Tujuan penerbangan: ";
        cin.ignore();
        getline(cin, tujuan);
        cout << "Waktu terbang (waktu:00:00): ";
        cin >> waktu;
        
        if (!isValidTime(waktu)) {
            cout << "Format waktu tidak valid!" << endl;
            return;
        }
        
        if (posisi == 1) {
            tambahAwal();
        } else if (posisi == panjang + 1) {
            tambahAkhir();
        } else {
            string kode = generateKode();
            Node* baru = new Node();
            baru->data.kode = kode;
            baru->data.tujuan = tujuan;
            baru->data.waktuTerbang = waktu;
            baru->data.status = "OnTime";
            
            Node* current = head;
            for (int i = 1; i < posisi - 1; i++) {
                current = current->next;
            }
            
            baru->next = current->next;
            baru->prev = current;
            current->next->prev = baru;
            current->next = baru;
            
            cout << "Berhasil tambah " << kode << " di posisi " << posisi << endl;
        }
    }

    void hapusAwal() {
        if (head == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        string kode = head->data.kode;
        
        if (head == tail) {
            delete head;
            head = NULL;
            tail = NULL;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
        }
        
        cout << "Berhasil hapus " << kode << endl;
    }
    
    void hapusAkhir() {
        if (tail == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        string kode = tail->data.kode;
        
        if (head == tail) {
            delete tail;
            head = NULL;
            tail = NULL;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
        }
        
        cout << "Berhasil hapus " << kode << endl;
    }

    void hapusSpesifik() {
        int panjang = hitungPanjangList();
        if (panjang == 0) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        int posisi;
        cout << "Masukkan posisi yang ingin dihapus (1-" << panjang << "): ";
        cin >> posisi;
        
        if (posisi < 1 || posisi > panjang) {
            cout << "Posisi tidak valid!" << endl;
            return;
        }
        
        if (posisi == 1) {
            hapusAwal();
        } else if (posisi == panjang) {
            hapusAkhir();
        } else {
            Node* current = head;
            for (int i = 1; i < posisi; i++) {
                current = current->next;
            }
            
            string kode = current->data.kode;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            
            cout << "Berhasil hapus " << kode << " dari posisi " << posisi << endl;
        }
    }
    
void updateWaktuTerbang() {
    if (head == NULL) {
        cout << "Tidak ada jadwal" << endl;
        return;
    }
    
    string kode;
    cout << "Masukkan kode penerbangan: ";
    cin >> kode;
    
    Node* current = head;
    while (current != NULL) {
        if (current->data.kode == kode) {
            cout << "\nData saat ini:" << endl;
            cout << "Kode: " << current->data.kode << endl;
            cout << "Tujuan: " << current->data.tujuan << endl;
            cout << "Waktu terbang lama: " << current->data.waktuTerbang << endl;
            cout << "Status: " << current->data.status << endl;
            
            string waktuBaru;
            cout << "Masukkan waktu terbang baru (waktu:00:00): ";
            cin >> waktuBaru;
            
            if (!isValidTime(waktuBaru)) {
                cout << "Format waktu tidak valid!" << endl;
                return;
            }
            
            current->data.waktuTerbang = waktuBaru;
            current->data.status = "Delayed";
            cout << "Waktu terbang berhasil diupdate: " << current->data.waktuTerbang << endl;
            cout << "Status otomatis berubah menjadi: Delayed" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Kode tidak ditemukan" << endl;
}

    void tampilkan() {
        if (head == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        cout << "\nDaftar Jadwal Penerbangan:" << endl;
        Node* current = head;
        int no = 1;
        while (current != NULL) {
            cout << no << ". " << current->data.kode << " | " 
                 << current->data.tujuan << " | " << current->data.waktuTerbang << endl;
            current = current->next;
            no++;
        }
        cout << "Total jadwal: " << no-1 << endl;
    }

    void tampilkanDariBelakang() {
        if (tail == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        cout << "\nDaftar Kode Penerbangan (dari Belakang):" << endl;
        Node* current = tail;
        int no = 1;
        
        while (current != NULL) {
            cout << no << ". " << current->data.kode << endl;
            current = current->prev;
            no++;
        }
        cout << "Total jadwal: " << no-1 << endl;
    }    
        
    void cariDetailData() {
        if (head == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        cout << "\nPencarian Detail Jadwal Penerbangan" << endl;
        cout << "1. Cari berdasarkan Kode Penerbangan" << endl;
        cout << "2. Cari berdasarkan Tujuan Penerbangan" << endl;
        cout << "Pilih metode pencarian (1-2): ";
        
        string pilihan;
        cin >> pilihan;
        cin.ignore();
        
        if (pilihan == "1") {
            string kodeCari;
            cout << "Masukkan kode penerbangan: ";
            getline(cin, kodeCari);
            
            Node* current = head;
            bool ditemukan = false;
            
            while (current != NULL) {
                if (toLower(current->data.kode) == toLower(kodeCari)) {
                    cout << "\nData ditemukan:" << endl;
                    cout << "Kode: " << current->data.kode << endl;
                    cout << "Tujuan: " << current->data.tujuan << endl;
                    cout << "Waktu terbang: " << current->data.waktuTerbang << endl;
                    cout << "Status: " << current->data.status << endl;
                    ditemukan = true;
                    break;
                }
                current = current->next;
            }
            
            if (!ditemukan) {
                cout << "Kode penerbangan '" << kodeCari << "' tidak ditemukan" << endl;
            }
            
        } else if (pilihan == "2") {
            string tujuanCari;
            cout << "Masukkan tujuan penerbangan: ";
            getline(cin, tujuanCari);
            
            Node* current = head;
            bool ditemukan = false;
            int hasilCount = 0;
            
            cout << "\nHasil Pencarian:" << endl;
            
            while (current != NULL) {
                if (toLower(current->data.tujuan).find(toLower(tujuanCari)) != string::npos) {
                    cout << hasilCount + 1 << ". " << current->data.kode << " | " 
                         << current->data.tujuan << " | " << current->data.waktuTerbang << " | " 
                         << current->data.status << endl;
                    ditemukan = true;
                    hasilCount++;
                }
                current = current->next;
            }
            
            if (!ditemukan) {
                cout << "Tujuan penerbangan '" << tujuanCari << "' tidak ditemukan" << endl;
            } else {
                cout << "Total ditemukan: " << hasilCount << " jadwal" << endl;
            }
            
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
    
    string getNama() { return nama; }
    string getNim() { return nim; }
};

int main() {
    string nim = "2409106106"; 
    string nama = "Dzaki Mubarak";
    FlightSystem system(nim, nama);
    
    while (true) {
        cout << "\n================================" << endl;
        cout << "     FLIGHT SCHEDULE SYSTEM" << endl;
        cout << "   " << system.getNama() << " - " << system.getNim() << endl;  
        cout << "================================" << endl;
        cout << "1. Tambah di Awal" << endl;
        cout << "2. Tambah di Akhir" << endl;
        cout << "3. Tambah di Posisi Spesifik" << endl;
        cout << "4. Hapus di Awal" << endl;
        cout << "5. Hapus di Akhir" << endl;
        cout << "6. Hapus di Posisi Spesifik" << endl;
        cout << "7. Update Data" << endl;
        cout << "8. Tampilkan Semua Jadwal" << endl;
        cout << "9. Tampilkan Jadwal dari belakang" << endl;
        cout << "10. Cari Detail Jadwal" << endl;
        cout << "11. Keluar" << endl;
        cout << "================================" << endl;
        
        string pilih;
        cout << "Pilih menu: ";
        cin >> pilih;
        
        if (pilih == "1") {
            system.tambahAwal();
        } 
        else if (pilih == "2") {
            system.tambahAkhir();
        } 
        else if (pilih == "3") {
            system.tambahSpesifik();
        } 
        else if (pilih == "4") {
            system.hapusAwal();
        } 
        else if (pilih == "5") {
            system.hapusAkhir();
        } 
        else if (pilih == "6") {
            system.hapusSpesifik();
        } 
        else if (pilih == "7") {
            system.updateWaktuTerbang();
        } 
        else if (pilih == "8") {
            system.tampilkan();
        } 
        else if (pilih == "9") {
            system.tampilkanDariBelakang();
        } 
        else if (pilih == "10") {
            system.cariDetailData();
        } 
        else if (pilih == "11") {
            cout << "Terima kasih!" << endl;
            break;
        } 
        else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
    
    return 0;
}