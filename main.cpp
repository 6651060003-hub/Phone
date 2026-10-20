#include <iostream>
#include <string>

using namespace std;

// Cấu trúc một nút (Node) đại diện cho 1 liên hệ trong Danh bạ
struct ContactNode {
    string name;
    string phone;
    ContactNode* prev;
    ContactNode* next;

    ContactNode(string n, string p) : name(n), phone(p), prev(nullptr), next(nullptr) {}
};

// Cấu trúc quản lý Danh sách liên kết đôi
class Phonebook {
private:
    ContactNode* head;
    ContactNode* tail;

public:
    Phonebook() : head(nullptr), tail(nullptr) {}

    // 1. Thêm liên hệ vào cuối danh sách
    void addContact(string name, string phone) {
        ContactNode* newNode = new ContactNode(name, phone);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "-> Da them lien he: " << name << " - " << phone << endl;
    }

    // 2. Duyệt danh bạ từ A - Z (từ Head đến Tail)
    void displayForward() {
        cout << "\n=== DANH SACH LIEN HE (A - Z) ===" << endl;
        ContactNode* current = head;
        if (!current) {
            cout << "(Danh ba trong)" << endl;
            return;
        }
        while (current != nullptr) {
            cout << "Ten: " << current->name << " | SĐT: " << current->phone << endl;
            current = current->next;
        }
    }

    // 3. Duyệt danh bạ từ Z - A (từ Tail đến Head)
    void displayBackward() {
        cout << "\n=== DANH SACH LIEN HE (Z - A) ===" << endl;
        ContactNode* current = tail;
        if (!current) {
            cout << "(Danh ba trong)" << endl;
            return;
        }
        while (current != nullptr) {
            cout << "Ten: " << current->name << " | SĐT: " << current->phone << endl;
            current = current->prev;
        }
    }

    // 4. Xóa số điện thoại khỏi danh bạ
    void deleteContact(string phone) {
        ContactNode* current = head;
        while (current != nullptr) {
            if (current->phone == phone) {
                if (current == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                    else tail = nullptr;
                } else if (current == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                    else head = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current; // Giải phóng bộ nhớ tránh rò rỉ
                cout << "-> Da xoa so dien thoai: " << phone << endl;
                return;
            }
            current = current->next;
        }
        cout << "-> Khong tim thay so dien thoai " << phone << " de xoa!" << endl;
    }

    // 5. Hàm hủy (Destructor) để giải phóng toàn bộ bộ nhớ (chống rò rỉ bộ nhớ)
    ~Phonebook() {
        ContactNode* current = head;
        while (current != nullptr) {
            ContactNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
    }
};

int main() {
    Phonebook pb;

    // Thử nghiệm các tính năng của nhánh 1
    pb.addContact("Nguyen Van A", "0901234567");
    pb.addContact("Tran Thi B", "0987654321");
    pb.addContact("Le Van C", "0911223344");

    // Duyệt tiến & lùi
    pb.displayForward();
    pb.displayBackward();

    // Xóa liên hệ
    pb.deleteContact("0987654321");
    pb.displayForward();

    return 0;
}