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