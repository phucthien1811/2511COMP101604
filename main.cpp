#include "include/Account.h"
#include "include/Menu.h"
#include <iostream>
#include <direct.h>
#include <sys/stat.h>

using namespace std;

void createDataDirectory() {
    struct stat info;
    
    // Kiểm tra thư mục data có tồn tại không
    if (stat("data", &info) != 0) {
        // Tạo thư mục data nếu chưa tồn tại
        _mkdir("data");
    }
}

int main() {
    // Tạo thư mục data nếu chưa có
    createDataDirectory();
    
    // Đăng nhập
    if (!Account::login()) {
        return 0;
    }
    
    // Chạy menu chính
    Menu menu;
    menu.run();
    
    return 0;
}