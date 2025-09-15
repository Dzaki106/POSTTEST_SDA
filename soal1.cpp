#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    int arr[7], num = 2;
    
    cout << "Sebelum dibalik: ";
    for (int i = 0; i < 7; i++) {
        while (!isPrime(num)) num++;
        arr[i] = num++;
        cout << arr[i] << " ";
    }
    
    for (int i = 0; i < 3; i++) {
        int temp = arr[i];
        arr[i] = arr[6-i];
        arr[6-i] = temp;
    }
    
    cout << "\nSetelah dibalik: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}