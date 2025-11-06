#include "include/Book.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menuQuanLySach(BookList& danhSachSach) {
    int choice;
    string filename = "data/SACH.txt";
    
    do {
        cout << "\n============================================" << endl;
        cout << "       QUAN LY SACH THU VIEN" << endl;
        cout << "============================================" << endl;
        cout << "1. Them sach moi" << endl;
        cout << "2. Xoa sach" << endl;
        cout << "3. Hien thi danh sach sach" << endl;
        cout << "4. Tim sach theo ma" << endl;
        cout << "5. Tim sach theo ten" << endl;
        cout << "6. Tim sach theo tac gia" << endl;
        cout << "7. Doc du lieu tu file" << endl;
        cout << "8. Luu du lieu vao file" << endl;
        cout << "0. Thoat" << endl;
        cout << "============================================" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                Book sachMoi;
                nhapThongTinSach(sachMoi);
                if (danhSachSach.themSach(sachMoi)) {
                    danhSachSach.luuVaoFile(filename);
                }
                break;
            }
            
            case 2: {
                string maSach;
                cout << "Nhap ma sach can xoa: ";
                getline(cin, maSach);
                if (danhSachSach.xoaSach(maSach)) {
                    danhSachSach.luuVaoFile(filename);
                }
                break;
            }
            
            case 3: {
                danhSachSach.hienThiDanhSach();
                break;
            }
            
            case 4: {
                string maSach;
                cout << "Nhap ma sach can tim: ";
                getline(cin, maSach);
                Book* sach = danhSachSach.timSach(maSach);
                if (sach) {
                    cout << "\n========== THONG TIN SACH ==========" << endl;
                    cout << "Ma sach: " << sach->maSach << endl;
                    cout << "Ten sach: " << sach->tenSach << endl;
                    cout << "Tac gia: " << sach->tacGia << endl;
                    cout << "Nha xuat ban: " << sach->nhaXuatBan << endl;
                    cout << "Nam phat hanh: " << sach->namPhatHanh << endl;
                    cout << "So trang: " << sach->soTrang << endl;
                    cout << "Ngay nhap: " << sach->ngayNhap << endl;
                    cout << "Tinh trang: " << (sach->tinhTrang == 1 ? "Con trong thu vien" : "Dang duoc muon") << endl;
                    cout << "====================================" << endl;
                } else {
                    cout << "Khong tim thay sach co ma '" << maSach << "'!" << endl;
                }
                break;
            }
            
            case 5: {
                string tenSach;
                cout << "Nhap ten sach can tim: ";
                getline(cin, tenSach);
                danhSachSach.timKiemTheoTen(tenSach);
                break;
            }
            
            case 6: {
                string tacGia;
                cout << "Nhap ten tac gia can tim: ";
                getline(cin, tacGia);
                danhSachSach.timKiemTheoTacGia(tacGia);
                break;
            }
            
            case 7: {
                danhSachSach.docTuFile(filename);
                break;
            }
            
            case 8: {
                danhSachSach.luuVaoFile(filename);
                break;
            }
            
            case 0: {
                cout << "Tam biet!" << endl;
                break;
            }
            
            default: {
                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                break;
            }
        }
        
    } while (choice != 0);
}

int main() {
    BookList danhSachSach;
    
    // Đọc dữ liệu từ file khi khởi động
    cout << "Dang tai du lieu..." << endl;
    danhSachSach.docTuFile("data/SACH.txt");
    
    // Hiển thị menu
    menuQuanLySach(danhSachSach);
    
    return 0;
}
