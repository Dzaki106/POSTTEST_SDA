#include <iostream>
#include <string>
using namespace std;

struct Jadwal {
    string kode;
    string tujuan;
    string waktuTerbang; 
    Jadwal* next;
};

class FlightSystem {
private:
    Jadwal* head;
    string nim;
    string nama;
    int counter;
    int digitAkhir;
    
public:
    FlightSystem(string n, string nm) { 
        head = NULL;
        nim = n;
        nama = nm; 
        counter = 1;
        digitAkhir = n[n.length()-1] - '0';
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
    
    int getPosisiSisip() {
        if (digitAkhir == 0) return 2;
        return digitAkhir + 1;
    }
    
    void tambah(string tujuan, string waktu) {
        string kode = generateKode();
        Jadwal* baru = new Jadwal();
        baru->kode = kode;
        baru->tujuan = tujuan;
        baru->waktuTerbang = waktu;
        baru->next = NULL;
        
        if (head == NULL) {
            head = baru;
        } else {
            Jadwal* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = baru;
        }
        cout << "Berhasil tambah " << kode << endl;
    }
    
    void sisip(string tujuan, string waktu) {
        if (head == NULL) {
            cout << "List kosong" << endl;
            return;
        }
        
        int posisi = getPosisiSisip();
        string kode = generateKode();
        Jadwal* baru = new Jadwal();
        baru->kode = kode;
        baru->tujuan = tujuan;
        baru->waktuTerbang = waktu;
        
        if (posisi == 1) {
            baru->next = head;
            head = baru;
        } else {
            Jadwal* current = head;
            for (int i = 1; i < posisi-1; i++) {
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    break;
                }
            }
            baru->next = current->next;
            current->next = baru;
        }
        cout << "Berhasil sisip " << kode << " di posisi " << posisi << endl;
    }
    
    void hapusAwal() {
        if (head == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        string kode = head->kode;
        Jadwal* temp = head;
        head = head->next;
        delete temp;
        
        cout << "Berhasil hapus " << kode << endl;
    }
    
    void updateWaktuTerbang() {
        if (head == NULL) {
            cout << "Tidak ada jadwal" << endl;
            return;
        }
        
        string kode;
        cout << "Masukkan kode penerbangan: ";
        cin >> kode;
        
        Jadwal* current = head;
        while (current != NULL) {
            if (current->kode == kode) {
                cout << "\nData saat ini:" << endl;
                cout << "Kode: " << current->kode << endl;
                cout << "Tujuan: " << current->tujuan << endl;
                cout << "Waktu terbang lama: " << current->waktuTerbang << endl;
                
                string waktuBaru;
                cout << "Masukkan waktu terbang baru (waktu:00:00): ";
                cin >> waktuBaru;
                
                current->waktuTerbang = waktuBaru;
                cout << "Waktu terbang berhasil diupdate: " << current->waktuTerbang << endl;
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
        Jadwal* current = head;
        int no = 1;
        while (current != NULL) {
            cout << no << ". " << current->kode << " | " 
                 << current->tujuan << " | " << current->waktuTerbang << endl;
            current = current->next;
            no++;
        }
        cout << "Total jadwal: " << no-1 << endl;
    }
    
    string getNama() { return nama; }
    string getNim() { return nim; }
};

int main() {
    string nim = "2409106106"; 
    string nama = "Dzaki Mubarak";
    FlightSystem system(nim, nama);
    
    while (true) {
        cout << "================================" << endl;
        cout << "     FLIGHT SCHEDULE SYSTEM" << endl;
        cout << "   " << system.getNama() << " - " << system.getNim() << endl;  
        cout << "================================" << endl;
        cout << "1. Tambah Jadwal" << endl;
        cout << "2. Sisipkan Jadwal" << endl;
        cout << "3. Hapus Jadwal Awal" << endl;
        cout << "4. Update Waktu Terbang" << endl;
        cout << "5. Tampilkan Semua Jadwal" << endl;
        cout << "0. Keluar" << endl;       
        string pilih;
        cout << "Pilih menu: ";
        cin >> pilih;
        
        if (pilih == "1") {
            string tujuan, waktu;
            cout << "Tujuan penerbangan: ";
            cin.ignore();
            getline(cin, tujuan);
            cout << "Waktu terbang (waktu:00:00): ";
            cin >> waktu;
            system.tambah(tujuan, waktu);
        } 
        else if (pilih == "2") {
            string tujuan, waktu;
            cout << "Tujuan penerbangan: ";
            cin.ignore();
            getline(cin, tujuan);
            cout << "Waktu terbang (waktu:00:00): ";
            cin >> waktu;
            system.sisip(tujuan, waktu);
        } 
        else if (pilih == "3") {
            system.hapusAwal();
        } 
        else if (pilih == "4") {
            system.updateWaktuTerbang();
        } 
        else if (pilih == "5") {
            system.tampilkan();
        } 
        else if (pilih == "0") {
            cout << "Terima kasih!" << endl;
            break;
        } 
        else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
    
    return 0;
}