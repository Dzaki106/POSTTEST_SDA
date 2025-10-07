#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node*& head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};
    
    // Kasus 1: List masih kosong
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    

    // Kasus 2: Data baru lebih kecil dari head (sisipkan di awal)
    if (data < head_ref->data) {
        Node* last = head_ref->prev; // Dapatkan node terakhir
        
        newNode->next = head_ref;
        newNode->prev = last;
        head_ref->prev = newNode;
        last->next = newNode;
        head_ref = newNode; // Update head ke node baru
        return;
    }
    
    // Kasus 3: Cari posisi yang tepat (tengah/akhir)
    Node* current = head_ref;
    
    // Cari posisi yang tepat untuk menyisipkan
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }
    
    // Sisipkan newNode setelah current
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

void printList(Node* head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }
    Node* current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

void printListReverse(Node* head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }
    Node* current = head_ref->prev; 
    Node* tail = current;
    do {
        cout << current->data << " ";
        current = current->prev;
    } while (current != tail);
    cout << endl;
}

int main() {
    Node* head = nullptr;
    
    // Test sorted insert
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);
    sortedInsert(head, 5);  //  awal
    sortedInsert(head, 50); //  akhir
    sortedInsert(head, 25); //  tengah
    
    cout << "Circular Doubly Linked List (ascending): ";
    printList(head);
    
    cout << "Circular Doubly Linked List (descending): ";
    printListReverse(head);   

    return 0;
}

//komentar
//menggunakan Circular Doubly Linked List buat dapat acending dan juga decending