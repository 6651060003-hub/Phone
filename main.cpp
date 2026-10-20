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
#include <iostream>
#include <string>

using namespace std;

// Cấu trúc một nút trong Danh sách liên kết đôi
struct ContactNode {
    string name;
    string phone;
    ContactNode* prev;
    ContactNode* next;

    ContactNode(string n, string p) : name(n), phone(p), prev(nullptr), next(nullptr) {}
};

// Cấu trúc quản lý Danh bạ
class Phonebook {
private:
    ContactNode* head;
    ContactNode* tail;

public:
    Phonebook() : head(nullptr), tail(nullptr) {}

    // Thêm liên hệ vào cuối danh sách
    void addContact(string name, string phone) {
        ContactNode* newNode = new ContactNode(name, phone);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Hiển thị danh sách liên hệ
    void displayForward() {
        cout << "\n=== DANH SACH LIEN HE ===" << endl;
        ContactNode* current = head;
        if (!current) {
            cout << "(Danh ba trong)" << endl;
            return;
        }
        while (current != nullptr) {
            cout << "Ten: " << current->name << " | SDT: " << current->phone << endl;
            current = current->next;
        }
    }

    // 1. Sắp xếp nổi bọt (Bubble Sort) theo tên (A-Z)
    void bubbleSortByName() {
        if (!head || !head->next) return;

        bool swapped;
        ContactNode* ptr1;
        ContactNode* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->name > ptr1->next->name) {
                    // Hoán đổi dữ liệu giữa 2 nút
                    swap(ptr1->name, ptr1->next->name);
                    swap(ptr1->phone, ptr1->next->phone);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
        cout << "\n-> Da sap xep danh ba theo ten (Bubble Sort)!" << endl;
    }

    // 2. Sắp xếp chèn (Insertion Sort) theo tên (A-Z)
    void insertionSortByName() {
        if (!head || !head->next) return;

        ContactNode* sorted = nullptr;
        ContactNode* current = head;

        while (current != nullptr) {
            ContactNode* next = current->next;
            current->prev = current->next = nullptr;

            if (!sorted) {
                sorted = current;
            } else if (sorted->name >= current->name) {
                current->next = sorted;
                sorted->prev = current;
                sorted = current;
            } else {
                ContactNode* temp = sorted;
                while (temp->next != nullptr && temp->next->name < current->name) {
                    temp = temp->next;
                }
                current->next = temp->next;
                if (temp->next != nullptr) current->next->prev = current;
                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }
        head = sorted;

        // Cập nhật lại con trỏ Tail
        ContactNode* temp = head;
        while (temp && temp->next) temp = temp->next;
        tail = temp;

        cout << "\n-> Da sap xep danh ba theo ten (Insertion Sort)!" << endl;
    }

    ~Phonebook() {
        ContactNode* current = head;
        while (current != nullptr) {
            ContactNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    Phonebook pb;

    // Thêm các liên hệ chưa đúng thứ tự bảng chữ cái
    pb.addContact("Tran Thi B", "0987654321");
    pb.addContact("Nguyen Van A", "0901234567");
    pb.addContact("Dang Van D", "0933445566");
    pb.addContact("Le Van C", "0911223344");

    cout << "--- DANH SACH BAN DAU (CHUA SAP XEP) ---";
    pb.displayForward();

    // Chạy thử thuật toán Sắp xếp nổi bọt (Bubble Sort)
    pb.bubbleSortByName();
    pb.displayForward();

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct ContactNode {
    string name;
    string phone;
    ContactNode* prev;
    ContactNode* next;

    ContactNode(string n, string p) : name(n), phone(p), prev(nullptr), next(nullptr) {}
};

class Phonebook {
private:
    ContactNode* head;
    ContactNode* tail;

    // Hàm phụ trợ chuyển chuỗi về chữ thường để so sánh không phân biệt hoa/thường
    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

public:
    Phonebook() : head(nullptr), tail(nullptr) {}

    void addContact(string name, string phone) {
        ContactNode* newNode = new ContactNode(name, phone);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Tim kiem chuoi ky tu theo tien to (Prefix Search)
    void searchByPrefix(string prefix) {
        cout << "\n=== KET QUA TIM KIEM VOI TIEN TO: \"" << prefix << "\" ===" << endl;
        ContactNode* current = head;
        bool found = false;
        string lowerPrefix = toLower(prefix);

        while (current != nullptr) {
            string lowerName = toLower(current->name);
            // Kiem tra xem ten co bat dau bang prefix hay khong
            if (lowerName.find(lowerPrefix) == 0) {
                cout << "Ten: " << current->name << " | SDT: " << current->phone << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "(Khong tim thay lien he nao phu hop)" << endl;
        }
    }

    ~Phonebook() {
        ContactNode* current = head;
        while (current != nullptr) {
            ContactNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    Phonebook pb;

    pb.addContact("Nguyen Van A", "0901234567");
    pb.addContact("Nguyen Thi B", "0987654321");
    pb.addContact("Le Van C", "0911223344");
    pb.addContact("Tran Van D", "0933445566");

    // Tim tat ca lien he bat dau bang "Nguy"
    pb.searchByPrefix("Nguy");

    // Tim tat ca lien he bat dau bang "Le"
    pb.searchByPrefix("le");

    return 0;
}