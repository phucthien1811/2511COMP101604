#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
using namespace std;

class Reader {
private:
    string maBanDoc;      // Mã bạn đọc (duy nhất)
    string hoTen;         // Họ tên
    string ngaySinh;      // Ngày sinh
    string diaChi;        // Địa chỉ
    string soDienThoai;   // Số điện thoại
    string ngayDangKy;    // Ngày đăng ký
    
public:
    // Constructor
    Reader();
    Reader(string ma, string ten, string ns, string dc, string sdt, string ngayDK);
    
    // Getter
    string getMaBanDoc();
    string getHoTen();
    string getNgaySinh();
    string getDiaChi();
    string getSoDienThoai();
    string getNgayDangKy();
    
    // Setter
    void setMaBanDoc(string ma);
    void setHoTen(string ten);
    void setNgaySinh(string ns);
    void setDiaChi(string dc);
    void setSoDienThoai(string sdt);
    void setNgayDangKy(string ngay);
    
    // Hiển thị thông tin
    void display();
    static void displayHeader();
    
    // Chuyển đổi sang string để lưu file
    string toString();
    
    // Đọc từ string
    static Reader fromString(string line);
};

class ReaderManager {
private:
    vector<Reader> readers;
    string filename;
    
public:
    ReaderManager();
    
    // Đọc/ghi file
    void loadFromFile();
    void saveToFile();
    
    // CRUD operations
    void addReader();
    void displayAllReaders();
    void searchReader();
    void deleteReader();
    
    // Kiểm tra bạn đọc tồn tại
    bool readerExists(string maBanDoc);
    Reader* findReader(string maBanDoc);
    
    // Menu
    void showMenu();
};

#endif