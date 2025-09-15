#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    Mahasiswa mhs[4] = {
        {"dzaki", "2409106106", 3.2},
        {"faras", "2409106092", 3.8},
        {"ripqi", "2409106112", 3.5},
        {"riski", "2409106113", 3.1}
    };
        
    for (int i = 0; i < 3; i++) {
        for (int j = i+1; j < 4; j++) {
            if (mhs[i].ipk > mhs[j].ipk) {
                Mahasiswa temp = mhs[i];
                mhs[i] = mhs[j];
                mhs[j] = temp;
            }
        }
    }
    
    cout << "\nascending by IPK:\n";
    for (int i = 0; i < 4; i++) {
        cout << mhs[i].nama << " - " << mhs[i].nim << " - " << mhs[i].ipk << endl;
    }
    
    return 0;
}