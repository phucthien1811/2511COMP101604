// Test program for Book module
#include "include/Book.h"
#include <iostream>

using namespace std;

void testThemSach(BookList& ds) {
    cout << "\n===== TEST THEM SACH =====" << endl;
    
    Book s1;
    s1.maSach = "S010";
    s1.tenSach = "Test Book 1";
    s1.tacGia = "Test Author";
    s1.nhaXuatBan = "Test Publisher";
    s1.namPhatHanh = 2023;
    s1.soTrang = 300;
    s1.ngayNhap = "06/11/2025";
    s1.tinhTrang = 1;
    
    ds.themSach(s1);
    
    // Test thêm trùng mã
    ds.themSach(s1);
}

void testXoaSach(BookList& ds) {
    cout << "\n===== TEST XOA SACH =====" << endl;
    
    // Test xóa sách đang được mượn
    cout << "\n1. Thu xoa sach dang duoc muon (S003):" << endl;
    ds.xoaSach("S003");
    
    // Test xóa sách còn trong thư viện
    cout << "\n2. Thu xoa sach con trong thu vien (S005):" << endl;
    ds.xoaSach("S005");
}

void testTimKiem(BookList& ds) {
    cout << "\n===== TEST TIM KIEM =====" << endl;
    
    // Tìm theo mã
    cout << "\n1. Tim theo ma (S001):" << endl;
    Book* s = ds.timSach("S001");
    if (s) {
        cout << "Tim thay: " << s->tenSach << endl;
    }
    
    // Tìm theo tên
    cout << "\n2. Tim theo ten (C++):" << endl;
    ds.timKiemTheoTen("C++");
    
    // Tìm theo tác giả
    cout << "\n3. Tim theo tac gia (Nguyen):" << endl;
    ds.timKiemTheoTacGia("Nguyen");
}

int main() {
    BookList danhSach;
    
    // Đọc dữ liệu từ file
    cout << "===== DOC DU LIEU TU FILE =====" << endl;
    danhSach.docTuFile("data/SACH.txt");
    
    // Hiển thị danh sách ban đầu
    danhSach.hienThiDanhSach();
    
    // Test các chức năng
    testThemSach(danhSach);
    testXoaSach(danhSach);
    testTimKiem(danhSach);
    
    // Hiển thị danh sách sau khi test
    cout << "\n===== DANH SACH SAU KHI TEST =====" << endl;
    danhSach.hienThiDanhSach();
    
    // Lưu vào file
    cout << "\n===== LUU DU LIEU VAO FILE =====" << endl;
    danhSach.luuVaoFile("data/SACH.txt");
    
    return 0;
}
