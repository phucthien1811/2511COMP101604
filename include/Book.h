#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Cấu trúc sách
struct Book {
    string maSach;        // Mã sách
    string tenSach;       // Tên sách
    string tacGia;        // Tác giả
    string nhaXuatBan;    // Nhà xuất bản
    int namPhatHanh;      // Năm phát hành
    int soTrang;          // Số trang
    string ngayNhap;      // Ngày nhập (format: DD/MM/YYYY)
    int tinhTrang;        // Tình trạng: 1 = còn trong thư viện, 0 = đang được mượn
    
    // Constructor mặc định
    Book() : namPhatHanh(0), soTrang(0), tinhTrang(1) {}
};

// Khai báo node cho danh sách liên kết đôi
struct BookNode {
    Book data;
    BookNode* prev;
    BookNode* next;
    
    BookNode(const Book& book) : data(book), prev(nullptr), next(nullptr) {}
};

// Lớp quản lý sách sử dụng danh sách liên kết đôi
class BookList {
private:
    BookNode* head;
    BookNode* tail;
    int count;
    
    // Hàm hỗ trợ
    BookNode* timSachTheoMa(const string& maSach);
    bool kiemTraMaSachTonTai(const string& maSach);
    void xoaToanBoNode();
    
public:
    // Constructor và Destructor
    BookList();
    ~BookList();
    
    // Các chức năng chính
    bool themSach(const Book& sach);
    bool xoaSach(const string& maSach);
    void hienThiDanhSach();
    Book* timSach(const string& maSach);
    
    // Quản lý file
    bool docTuFile(const string& filename);
    bool luuVaoFile(const string& filename);
    
    // Cập nhật tình trạng sách
    bool capNhatTinhTrang(const string& maSach, int tinhTrangMoi);
    
    // Kiểm tra sách có đang được mượn không
    bool sachDangDuocMuon(const string& maSach);
    
    // Lấy số lượng sách
    int laySoLuong() const { return count; }
    
    // Hiển thị thông tin chi tiết một sách
    void hienThiThongTinSach(const Book& sach);
    
    // Tìm kiếm sách theo tiêu chí
    void timKiemTheoTen(const string& ten);
    void timKiemTheoTacGia(const string& tacGia);
};

// Các hàm hỗ trợ nhập liệu
void nhapThongTinSach(Book& sach);
bool kiemTraNamHopLe(int nam);
bool kiemTraNgayHopLe(const string& ngay);

#endif // BOOK_H
