#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string maSach;      // Mã sách (duy nhất)
    string tenSach;     // Tên sách
    string tacGia;      // Tác giả
    string nxb;         // Nhà xuất bản
    double giaBan;      // Giá bán
    int namPhatHanh;    // Năm phát hành
    int soTrang;        // Số trang
    string ngayNhapKho; // Ngày nhập kho
    int tinhTrang;      // Tình trạng (0 = đang mượn, >0 = còn lại)
    
public:
    // Constructor
    Book();
    Book(string ma, string ten, string tg, string nxb, double gia, 
         int nam, int trang, string ngayNhap, int tinhTrang);
    
    // Getter
    string getMaSach();
    string getTenSach();
    string getTacGia();
    string getNXB();
    double getGiaBan();
    int getNamPhatHanh();
    int getSoTrang();
    string getNgayNhapKho();
    int getTinhTrang();
    
    // Setter
    void setMaSach(string ma);
    void setTenSach(string ten);
    void setTacGia(string tg);
    void setNXB(string nxb);
    void setGiaBan(double gia);
    void setNamPhatHanh(int nam);
    void setSoTrang(int trang);
    void setNgayNhapKho(string ngay);
    void setTinhTrang(int tt);
    
    // Hiển thị thông tin
    void display();
    static void displayHeader();
    
    // Chuyển đổi sang string để lưu file
    string toString();
    
    // Đọc từ string
    static Book fromString(string line);
};

class BookManager {
private:
    vector<Book> books;
    string filename;
    
public:
    BookManager();
    
    // Đọc/ghi file
    void loadFromFile();
    void saveToFile();
    
    // CRUD operations
    void addBook();
    void displayAllBooks();
    void searchBook();
    void deleteBook();
    void updateBookStatus(string maSach, int newStatus);
    
    // Kiểm tra sách tồn tại
    bool bookExists(string maSach);
    Book* findBook(string maSach);
    
    // Menu
    void showMenu();
};

#endif