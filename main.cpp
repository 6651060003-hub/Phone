#include <iostream>
#include <string>

using namespace std;

// Cấu trúc một nhật ký cuộc gọi
struct CallLogNode {
    string phone;
    string callTime; // Thoi gian cuoc goi
    int duration;   // Thoi lượng (giay)
    CallLogNode* next;

    CallLogNode(string p, string t, int d) : phone(p), callTime(t), duration(d), next(nullptr) {}
};

class CallHistory {
private:
    CallLogNode* head;

public:
    CallHistory() : head(nullptr) {}

    // Ghi nhan cuoc goi gan nhat (Them vao dau danh sach)
    void recordCall(string phone, string time, int duration) {
        CallLogNode* newLog = new CallLogNode(phone, time, duration);
        newLog->next = head;
        head = newLog;
        cout << "-> Da ghi nhan cuoc goi voi SDT: " << phone << endl;
    }

    // Hien thi lich su cuoc goi gan nhat
    void displayCallHistory() {
        cout << "\n=== LICH SU CUOC GOI GAN NHAT ===" << endl;
        CallLogNode* current = head;
        if (!current) {
            cout << "(Lich su cuoc goi trong)" << endl;
            return;
        }
        while (current != nullptr) {
            cout << "SDT: " << current->phone 
                 << " | Thoi gian: " << current->callTime 
                 << " | Thoi luong: " << current->duration << "s" << endl;
            current = current->next;
        }
    }

    ~CallHistory() {
        CallLogNode* current = head;
        while (current != nullptr) {
            CallLogNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    CallHistory history;

    // Ghi nhan cac cuoc goi
    history.recordCall("0901234567", "10:30 20/10/2026", 120);
    history.recordCall("0987654321", "11:15 20/10/2026", 45);
    history.recordCall("0911223344", "14:00 20/10/2026", 300);

    // Hien thi danh sach
    history.displayCallHistory();

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>

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

    // 1. Ghi danh sach lien he ra tep tin (File Write)
    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Loi: Khong the mo file de ghi!" << endl;
            return;
        }

        ContactNode* current = head;
        while (current != nullptr) {
            outFile << current->name << "," << current->phone << endl;
            current = current->next;
        }
        outFile.close();
        cout << "-> Da luu danh ba vao file: " << filename << endl;
    }

    // 2. Doc danh sach lien he tu tep tin (File Read)
    void loadFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Thong bao: Khong tim thay file " << filename << " de doc!" << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string name = line.substr(0, commaPos);
                string phone = line.substr(commaPos + 1);
                addContact(name, phone);
            }
        }
        inFile.close();
        cout << "-> Da doc du lieu danh ba tu file: " << filename << endl;
    }

    void displayForward() {
        cout << "\n=== DANH SACH LIEN HE HIENTAI ===" << endl;
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

    // Them lien he ban dau
    pb.addContact("Nguyen Van A", "0901234567");
    pb.addContact("Tran Thi B", "0987654321");

    // Ghi ra file text
    pb.saveToFile("phonebook.txt");

    // Doc lai file vao danh ba moi
    Phonebook newPb;
    newPb.loadFromFile("phonebook.txt");
    newPb.displayForward();

    return 0;
}