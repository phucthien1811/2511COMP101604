#include "../include/Book.h"
#include <ctime>

// ==================== CONSTRUCTOR VÀ DESTRUCTOR ====================

BookList::BookList() : head(nullptr), tail(nullptr), count(0) {}

BookList::~BookList() {
    xoaToanBoNode();
}

void BookList::xoaToanBoNode() {
    BookNode* current = head;
    while (current != nullptr) {
        BookNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    count = 0;
}

// ==================== HÀM HỖ TRỢ ====================

BookNode* BookList::timSachTheoMa(const string& maSach) {
    BookNode* current = head;
    while (current != nullptr) {
        if (current->data.maSach == maSach) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool BookList::kiemTraMaSachTonTai(const string& maSach) {
    return timSachTheoMa(maSach) != nullptr;
}

// ==================== CÁC CHỨC NĂNG CHÍNH ====================

bool BookList::themSach(const Book& sach) {
    // Kiểm tra mã sách đã tồn tại
    if (kiemTraMaSachTonTai(sach.maSach)) {
        cout << "Loi: Ma sach '" << sach.maSach << "' da ton tai!" << endl;
        return false;
    }
    
    // Tạo node mới
    BookNode* newNode = new BookNode(sach);
    
    // Thêm vào danh sách rỗng
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        // Thêm vào cuối danh sách
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    count++;
    cout << "Them sach thanh cong! Ma sach: " << sach.maSach << endl;
    return true;
}

bool BookList::xoaSach(const string& maSach) {
    BookNode* node = timSachTheoMa(maSach);
    
    if (node == nullptr) {
        cout << "Loi: Khong tim thay sach co ma '" << maSach << "'!" << endl;
        return false;
    }
    
    // Kiểm tra sách có đang được mượn không
    if (node->data.tinhTrang == 0) {
        cout << "Loi: Khong the xoa sach '" << maSach 
             << "' vi sach dang duoc muon!" << endl;
        return false;
    }
    
    // Xóa node
    if (node == head && node == tail) {
        // Chỉ có 1 node
        head = tail = nullptr;
    } else if (node == head) {
        // Xóa node đầu
        head = head->next;
        head->prev = nullptr;
    } else if (node == tail) {
        // Xóa node cuối
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        // Xóa node ở giữa
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    delete node;
    count--;
    cout << "Xoa sach thanh cong! Ma sach: " << maSach << endl;
    return true;
}

void BookList::hienThiThongTinSach(const Book& sach) {
    cout << left 
         << setw(12) << sach.maSach
         << setw(30) << sach.tenSach
         << setw(20) << sach.tacGia
         << setw(20) << sach.nhaXuatBan
         << setw(8) << sach.namPhatHanh
         << setw(10) << sach.soTrang
         << setw(15) << sach.ngayNhap
         << setw(12) << (sach.tinhTrang == 1 ? "Con" : "Dang muon")
         << endl;
}

void BookList::hienThiDanhSach() {
    if (head == nullptr) {
        cout << "\nDanh sach sach trong!" << endl;
        return;
    }
    
    cout << "\n========== DANH SACH SACH ==========" << endl;
    cout << "Tong so sach: " << count << endl;
    cout << string(130, '-') << endl;
    
    cout << left 
         << setw(12) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(20) << "Nha xuat ban"
         << setw(8) << "Nam PH"
         << setw(10) << "So trang"
         << setw(15) << "Ngay nhap"
         << setw(12) << "Tinh trang"
         << endl;
    cout << string(130, '-') << endl;
    
    BookNode* current = head;
    while (current != nullptr) {
        hienThiThongTinSach(current->data);
        current = current->next;
    }
    cout << string(130, '-') << endl;
}

Book* BookList::timSach(const string& maSach) {
    BookNode* node = timSachTheoMa(maSach);
    return node ? &(node->data) : nullptr;
}

// ==================== QUẢN LÝ FILE ====================

bool BookList::docTuFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file: " << filename << endl;
        return false;
    }
    
    // Xóa dữ liệu cũ
    xoaToanBoNode();
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Book sach;
        string tinhTrangStr;
        
        getline(ss, sach.maSach, '|');
        getline(ss, sach.tenSach, '|');
        getline(ss, sach.tacGia, '|');
        getline(ss, sach.nhaXuatBan, '|');
        ss >> sach.namPhatHanh;
        ss.ignore();
        ss >> sach.soTrang;
        ss.ignore();
        getline(ss, sach.ngayNhap, '|');
        ss >> sach.tinhTrang;
        
        themSach(sach);
    }
    
    file.close();
    cout << "Doc file thanh cong! Tong so sach: " << count << endl;
    return true;
}

bool BookList::luuVaoFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi: " << filename << endl;
        return false;
    }
    
    BookNode* current = head;
    while (current != nullptr) {
        file << current->data.maSach << "|"
             << current->data.tenSach << "|"
             << current->data.tacGia << "|"
             << current->data.nhaXuatBan << "|"
             << current->data.namPhatHanh << "|"
             << current->data.soTrang << "|"
             << current->data.ngayNhap << "|"
             << current->data.tinhTrang << endl;
        current = current->next;
    }
    
    file.close();
    cout << "Luu file thanh cong!" << endl;
    return true;
}

// ==================== CẬP NHẬT TÌNH TRẠNG ====================

bool BookList::capNhatTinhTrang(const string& maSach, int tinhTrangMoi) {
    BookNode* node = timSachTheoMa(maSach);
    if (node == nullptr) {
        return false;
    }
    
    node->data.tinhTrang = tinhTrangMoi;
    return true;
}

bool BookList::sachDangDuocMuon(const string& maSach) {
    BookNode* node = timSachTheoMa(maSach);
    if (node == nullptr) {
        return false;
    }
    return node->data.tinhTrang == 0;
}

// ==================== TÌM KIẾM ====================

void BookList::timKiemTheoTen(const string& ten) {
    bool found = false;
    BookNode* current = head;
    
    cout << "\n========== KET QUA TIM KIEM THEO TEN ==========" << endl;
    cout << string(130, '-') << endl;
    cout << left 
         << setw(12) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(20) << "Nha xuat ban"
         << setw(8) << "Nam PH"
         << setw(10) << "So trang"
         << setw(15) << "Ngay nhap"
         << setw(12) << "Tinh trang"
         << endl;
    cout << string(130, '-') << endl;
    
    while (current != nullptr) {
        if (current->data.tenSach.find(ten) != string::npos) {
            hienThiThongTinSach(current->data);
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Khong tim thay sach nao co ten '" << ten << "'!" << endl;
    }
    cout << string(130, '-') << endl;
}

void BookList::timKiemTheoTacGia(const string& tacGia) {
    bool found = false;
    BookNode* current = head;
    
    cout << "\n========== KET QUA TIM KIEM THEO TAC GIA ==========" << endl;
    cout << string(130, '-') << endl;
    cout << left 
         << setw(12) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(20) << "Nha xuat ban"
         << setw(8) << "Nam PH"
         << setw(10) << "So trang"
         << setw(15) << "Ngay nhap"
         << setw(12) << "Tinh trang"
         << endl;
    cout << string(130, '-') << endl;
    
    while (current != nullptr) {
        if (current->data.tacGia.find(tacGia) != string::npos) {
            hienThiThongTinSach(current->data);
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Khong tim thay sach nao cua tac gia '" << tacGia << "'!" << endl;
    }
    cout << string(130, '-') << endl;
}

// ==================== HÀM HỖ TRỢ NHẬP LIỆU ====================

bool kiemTraNamHopLe(int nam) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int namHienTai = 1900 + ltm->tm_year;
    return (nam >= 1000 && nam <= namHienTai);
}

bool kiemTraNgayHopLe(const string& ngay) {
    if (ngay.length() != 10) return false;
    if (ngay[2] != '/' || ngay[5] != '/') return false;
    
    try {
        int day = stoi(ngay.substr(0, 2));
        int month = stoi(ngay.substr(3, 2));
        int year = stoi(ngay.substr(6, 4));
        
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if (!kiemTraNamHopLe(year)) return false;
        
        // Kiểm tra số ngày trong tháng
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeapYear ? 29 : 28)) return false;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

void nhapThongTinSach(Book& sach) {
    cout << "\n===== NHAP THONG TIN SACH =====" << endl;
    
    cout << "Ma sach: ";
    getline(cin, sach.maSach);
    
    cout << "Ten sach: ";
    getline(cin, sach.tenSach);
    
    cout << "Tac gia: ";
    getline(cin, sach.tacGia);
    
    cout << "Nha xuat ban: ";
    getline(cin, sach.nhaXuatBan);
    
    do {
        cout << "Nam phat hanh: ";
        cin >> sach.namPhatHanh;
        if (!kiemTraNamHopLe(sach.namPhatHanh)) {
            cout << "Nam phat hanh khong hop le! Vui long nhap lai." << endl;
        }
    } while (!kiemTraNamHopLe(sach.namPhatHanh));
    
    do {
        cout << "So trang: ";
        cin >> sach.soTrang;
        if (sach.soTrang <= 0) {
            cout << "So trang phai lon hon 0! Vui long nhap lai." << endl;
        }
    } while (sach.soTrang <= 0);
    
    cin.ignore();
    
    do {
        cout << "Ngay nhap (DD/MM/YYYY): ";
        getline(cin, sach.ngayNhap);
        if (!kiemTraNgayHopLe(sach.ngayNhap)) {
            cout << "Ngay khong hop le! Vui long nhap theo dinh dang DD/MM/YYYY." << endl;
        }
    } while (!kiemTraNgayHopLe(sach.ngayNhap));
    
    // Mặc định tình trạng là 1 (còn trong thư viện)
    sach.tinhTrang = 1;
    
    cout << "================================" << endl;
}
