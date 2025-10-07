#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};
    
    // 1. Jika queue kosong (front == nullptr), set front dan rear ke newNode
    if (front == nullptr) {
        front = newNode;
        rear = newNode;
    }
    // 2. Jika tidak kosong, sambungkan rear->next ke newNode, lalu update rear
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return ""; // Queue kosong
    
    // 1. Simpan data dari front node
    string document = front->document;
    Node* temp = front;
    
    // 2. Geser front ke front->next
    front = front->next;
    
    // 3. Jika front menjadi nullptr, set rear juga ke nullptr
    if (front == nullptr) {
        rear = nullptr;
    }
    
    // 4. Delete node lama dan return data
    delete temp;
    return document;
}

void processAllDocuments(Node*& front, Node*& rear) {
    // Loop hingga queue kosong, dequeue dan print setiap dokumen
    // Format: "Memproses: [nama_dokumen]"
    int count = 0;
    while (front != nullptr) {
        string document = dequeue(front, rear);
        cout << "Memproses: " << document << endl;
        count++;
    }
    
    if (count == 0) {
        cout << "Tidak ada dokumen dalam antrian." << endl;
    } else {
        cout << "Semua " << count << " dokumen telah diproses." << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;
    
    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");
    
    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);
    
    return 0;
}

//komentar
//Queue adalah struktur data dengan prinsip FIFO (First-In-First-Out).data Yang pertama akan print lalu dihapus/selesai lalu data dibelakan jadi data pertama.