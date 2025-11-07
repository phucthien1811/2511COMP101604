#ifndef BORROWSLIP_H
#define BORROWSLIP_H

#include <string>
#include <vector>
#include "Book.h"
#include "Reader.h"

using namespace std;

class BorrowSlip {
private:
    string soPhieu;         // Số phiếu mượn (duy nhất)
    string maBanDoc;        // Mã bạn đọc
    string maSach;          // Mã sách
    string ngayMuon;        // Ngày mượn
    string ngayTraDuKien;   // Ngày trả dự kiến (+7 ngày)
    int tinhTrang;          // Tình trạng (1 = đang mượn, 0 = đã trả)
    
public:
    // Constructor
    BorrowSlip();
    BorrowSlip(string soPhieu, string maBD, string maSach, 
               string ngayMuon, string ngayTra, int tinhTrang);
    
    // Getter
    string getSoPhieu();
    string getMaBanDoc();
    string getMaSach();
    string getNgayMuon();
    string getNgayTraDuKien();
    int getTinhTrang();
    
    // Setter
    void setSoPhieu(string sp);
    void setMaBanDoc(string maBD);
    void setMaSach(string maSach);
    void setNgayMuon(string ngay);
    void setNgayTraDuKien(string ngay);
    void setTinhTrang(int tt);
    
    // Hiển thị thông tin
    void display();
    static void displayHeader();
    
    // Chuyển đổi sang string để lưu file
    string toString();
    
    // Đọc từ string
    static BorrowSlip fromString(string line);
};

class BorrowSlipManager {
private:
    vector<BorrowSlip> slips;
    string filename;
    BookManager* bookManager;
    ReaderManager* readerManager;
    
public:
    BorrowSlipManager(BookManager* bm, ReaderManager* rm);
    
    // Đọc/ghi file
    void loadFromFile();
    void saveToFile();
    
    // Tạo số phiếu tự động
    string generateSlipNumber();
    
    // CRUD operations
    void borrowBook();
    void returnBook();
    void displayAllSlips();
    void searchSlip();
    
    // Kiểm tra phiếu mượn tồn tại
    bool slipExists(string soPhieu);
    BorrowSlip* findSlip(string soPhieu);
    
    // Menu
    void showMenu();
};

#endif