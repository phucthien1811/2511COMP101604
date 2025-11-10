#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

// Cấu trúc Sách
struct Sach {
    string maSach;
    string tenSach;
    int tinhTrang; // 1: còn, 0: đã mượn
};

// Cấu trúc Phiếu Mượn
struct PhieuMuon {
    string soPhieu;
    string maSach;
    string maBanDoc;
    string ngayMuon;
    string ngayPhaiTra;
    int tinhTrang; // 1: đang mượn, 0: đã trả
};

// Hàm tính ngày phải trả (ngày mượn + 7 ngày)
string tinhNgayPhaiTra(string ngayMuon) {
    struct tm tm = {};
    int ngay, thang, nam;
    sscanf(ngayMuon.c_str(), "%d/%d/%d", &ngay, &thang, &nam);
    
    tm.tm_mday = ngay;
    tm.tm_mon = thang - 1;
    tm.tm_year = nam - 1900;
    
    time_t t = mktime(&tm);
    t += 7 * 24 * 60 * 60; // Cộng 7 ngày
    tm = *localtime(&t);
    
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return string(buffer);
}

// Đọc danh sách sách từ file
vector<Sach> docDanhSachSach() {
    vector<Sach> danhSach;
    ifstream file("SACH.txt");
    if (file.is_open()) {
        Sach s;
        while (file >> s.maSach >> ws && getline(file, s.tenSach) && file >> s.tinhTrang) {
            danhSach.push_back(s);
        }
        file.close();
    }
    return danhSach;
}

// Ghi danh sách sách vào file
void ghiDanhSachSach(vector<Sach>& danhSach) {
    ofstream file("SACH.txt");
    if (file.is_open()) {
        for (const auto& s : danhSach) {
            file << s.maSach << endl;
            file << s.tenSach << endl;
            file << s.tinhTrang << endl;
        }
        file.close();
    }
}

// Đọc danh sách phiếu mượn từ file
vector<PhieuMuon> docDanhSachPhieuMuon() {
    vector<PhieuMuon> danhSach;
    ifstream file("PHIEUMUON.txt");
    if (file.is_open()) {
        PhieuMuon pm;
        while (file >> pm.soPhieu >> pm.maSach >> pm.maBanDoc >> pm.ngayMuon >> pm.ngayPhaiTra >> pm.tinhTrang) {
            danhSach.push_back(pm);
        }
        file.close();
    }
    return danhSach;
}

// Ghi danh sách phiếu mượn vào file
void ghiDanhSachPhieuMuon(vector<PhieuMuon>& danhSach) {
    ofstream file("PHIEUMUON.txt");
    if (file.is_open()) {
        for (const auto& pm : danhSach) {
            file << pm.soPhieu << " " << pm.maSach << " " << pm.maBanDoc << " "
                 << pm.ngayMuon << " " << pm.ngayPhaiTra << " " << pm.tinhTrang << endl;
        }
        file.close();
    }
}

// Kiểm tra sách có sẵn không
bool kiemTraSachCoSan(vector<Sach>& danhSachSach, string maSach) {
    for (auto& s : danhSachSach) {
        if (s.maSach == maSach && s.tinhTrang == 1) {
            return true;
        }
    }
    return false;
}

// Tạo phiếu mượn mới
void taoPhieuMuonMoi() {
    vector<PhieuMuon> danhSachPM = docDanhSachPhieuMuon();
    vector<Sach> danhSachSach = docDanhSachSach();
    
    PhieuMuon pm;
    
    cout << "\n===== TAO PHIEU MUON MOI =====\n";
    cout << "Nhap so phieu: ";
    cin >> pm.soPhieu;
    
    cout << "Nhap ma sach: ";
    cin >> pm.maSach;
    
    // Kiểm tra sách có sẵn không
    if (!kiemTraSachCoSan(danhSachSach, pm.maSach)) {
        cout << "Sach khong co san hoac da duoc muon!\n";
        return;
    }
    
    cout << "Nhap ma ban doc: ";
    cin >> pm.maBanDoc;
    
    cout << "Nhap ngay muon (dd/mm/yyyy): ";
    cin >> pm.ngayMuon;
    
    // Tự động tính ngày phải trả
    pm.ngayPhaiTra = tinhNgayPhaiTra(pm.ngayMuon);
    pm.tinhTrang = 1; // Đang mượn
    
    // Cập nhật tình trạng sách
    for (auto& s : danhSachSach) {
        if (s.maSach == pm.maSach) {
            s.tinhTrang = 0; // Đã mượn
            break;
        }
    }
    
    danhSachPM.push_back(pm);
    ghiDanhSachPhieuMuon(danhSachPM);
    ghiDanhSachSach(danhSachSach);
    
    cout << "\nTao phieu muon thanh cong!\n";
    cout << "Ngay phai tra: " << pm.ngayPhaiTra << endl;
}

// Hiển thị danh sách phiếu mượn
void hienThiDanhSachPhieuMuon() {
    vector<PhieuMuon> danhSach = docDanhSachPhieuMuon();
    
    cout << "\n===== DANH SACH PHIEU MUON =====\n";
    cout << left << setw(12) << "So Phieu" 
         << setw(12) << "Ma Sach" 
         << setw(12) << "Ma Ban Doc" 
         << setw(15) << "Ngay Muon" 
         << setw(15) << "Ngay Tra" 
         << setw(12) << "Tinh Trang" << endl;
    cout << string(78, '-') << endl;
    
    for (const auto& pm : danhSach) {
        cout << left << setw(12) << pm.soPhieu 
             << setw(12) << pm.maSach 
             << setw(12) << pm.maBanDoc 
             << setw(15) << pm.ngayMuon 
             << setw(15) << pm.ngayPhaiTra 
             << setw(12) << (pm.tinhTrang == 1 ? "Dang muon" : "Da tra") << endl;
    }
}

// Trả sách
void traSach() {
    vector<PhieuMuon> danhSachPM = docDanhSachPhieuMuon();
    vector<Sach> danhSachSach = docDanhSachSach();
    
    string soPhieu;
    cout << "\n===== TRA SACH =====\n";
    cout << "Nhap so phieu can tra: ";
    cin >> soPhieu;
    
    bool timThay = false;
    for (auto& pm : danhSachPM) {
        if (pm.soPhieu == soPhieu && pm.tinhTrang == 1) {
            pm.tinhTrang = 0; // Đã trả
            
            // Cập nhật tình trạng sách
            for (auto& s : danhSachSach) {
                if (s.maSach == pm.maSach) {
                    s.tinhTrang = 1; // Còn
                    break;
                }
            }
            
            timThay = true;
            break;
        }
    }
    
    if (timThay) {
        ghiDanhSachPhieuMuon(danhSachPM);
        ghiDanhSachSach(danhSachSach);
        cout << "Tra sach thanh cong!\n";
    } else {
        cout << "Khong tim thay phieu muon hoac sach da duoc tra!\n";
    }
}

// Menu chính
int main() {
    int luaChon;
    
    do {
        cout << "\n========== QUAN LY PHIEU MUON SACH ==========\n";
        cout << "1. Tao phieu muon moi\n";
        cout << "2. Hien thi danh sach phieu muon\n";
        cout << "3. Tra sach\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> luaChon;
        
        switch (luaChon) {
            case 1:
                taoPhieuMuonMoi();
                break;
            case 2:
                hienThiDanhSachPhieuMuon();
                break;
            case 3:
                traSach();
                break;
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
    
    return 0;
}