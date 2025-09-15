#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{3,4,6},{7,1,8},{9,2,0}};
    int sum = 0;
    
    cout << "Matriks 3x3:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
            if (i == 1) sum += matrix[i][j];
        }
        cout << endl;
    }
    
    cout << "Jumlah baris 2: " << sum;
    
    return 0;
}