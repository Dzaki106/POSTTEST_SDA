#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node*& head_ref) {
    // Hanya berjalan jika ada 2 node atau lebih
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    Node* head = head_ref;
    Node* tail = head_ref->prev;  // Tail adalah prev dari head

    // Kasus khusus: hanya ada 2 node
    if (head->next == tail && tail->prev == head) {
        // Cukup update head_ref ke tail
        head_ref = tail;
        return;
    }

    // Simpan neighbor nodes
    Node* head_next = head->next;
    Node* tail_prev = tail->prev;

    // Update koneksi untuk tail menjadi head baru
    tail->next = head_next;
    tail->prev = head;
    head_next->prev = tail;

    // Update koneksi untuk head menjadi tail baru
    head->next = tail;
    head->prev = tail_prev;
    tail_prev->next = head;

    // Update head_ref ke tail (yang sekarang menjadi head baru)
    head_ref = tail;
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

void insertEnd(Node*& head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    Node* tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main() {
    Node* head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);
    cout << "List setelah exchange head dan tail: ";
    // Expected output: 5 2 3 4 1
    printList(head);

    // Test dengan 2 node
    Node* head2 = nullptr;
    insertEnd(head2, 10);
    insertEnd(head2, 20);
    
    cout << "\nList 2 node sebelum exchange: ";
    printList(head2);
    
    exchangeHeadAndTail(head2);
    cout << "List 2 node setelah exchange: ";
    printList(head2); // Expected: 20 10

    return 0;
}

//komentar
//Kita ingin menukar posisi node pertama (head) dan node terakhir (tail) tanpa mengubah isi datanya, hanya dengan mengubah hubungan pointer antar node.