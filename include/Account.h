#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    string username;
    string password;
    
public:
    // Constructor
    Account();
    Account(string user, string pass);
    
    // Getter
    string getUsername();
    string getPassword();
    
    // Setter
    void setUsername(string user);
    void setPassword(string pass);
    
    // Đăng nhập (trả về true nếu thành công)
    static bool login();
    
    // Kiểm tra thông tin đăng nhập
    static bool verifyLogin(string user, string pass);
};

#endif