#include <iostream>
using namespace std;

int main() {
    int a, b;
    a = 12;
    b = 32;
    
   cout << "Sebelum: " << a << " " << b;
    
    int temp = a;
    a = b;
    b = temp;
    
    cout << "\nSesudah: " << a << " " << b;
    
    return 0;
}