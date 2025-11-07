#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

using namespace std;

class Utils {
public:
    // Xóa màn hình
    static void clearScreen();
    
    // Dừng màn hình
    static void pause();
    
    // Lấy ngày hiện tại dạng DD/MM/YYYY
    static string getCurrentDate();
    
    // Tính ngày trả (ngày mượn + 7 ngày)
    static string calculateReturnDate(string borrowDate);
    
    // Chuyển đổi string sang int
    static int stringToInt(string s);
    
    // Chuyển đổi int sang string
    static string intToString(int n);
    
    // Kiểm tra chuỗi có phải số không
    static bool isNumber(string s);
    
    // Mã hóa password thành dấu *
    static string inputPassword();
    
    // Vẽ khung tiêu đề
    static void printHeader(string title);
    
    // Vẽ đường kẻ ngang
    static void printLine(int length = 80);
    
    // Trim khoảng trắng đầu cuối
    static string trim(string s);
    
    // Kiểm tra file tồn tại
    static bool fileExists(string filename);
};

#endif