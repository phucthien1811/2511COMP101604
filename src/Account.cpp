#include "../include/Account.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>

Account::Account() {
    username = "";
    password = "";
}

Account::Account(string user, string pass) {
    username = user;
    password = pass;
}

string Account::getUsername() {
    return username;
}

string Account::getPassword() {
    return password;
}

void Account::setUsername(string user) {
    username = user;
}

void Account::setPassword(string pass) {
    password = pass;
}

bool Account::login() {
    Utils::clearScreen();
    Utils::printLine(50);
    cout << "*                                                *" << endl;
    cout << "*           DANG NHAP HE THONG                   *" << endl;
    cout << "*                                                *" << endl;
    Utils::printLine(50);
    
    int attempts = 0;
    string user, pass;
    
    while (attempts < 3) {
        cout << "\n User: ";
        getline(cin, user);
        
        cout << " Password: ";
        pass = Utils::inputPassword();
        cout << endl;
        
        if (verifyLogin(user, pass)) {
            cout << "\n=> Dang nhap thanh cong!" << endl;
            Utils::pause();
            return true;
        } else {
            attempts++;
            if (attempts < 3) {
                cout << "\n=> Sai thong tin dang nhap! Ban con " << (3 - attempts) << " lan thu." << endl;
                Utils::pause();
                Utils::clearScreen();
                Utils::printLine(50);
                cout << "*                                                *" << endl;
                cout << "*           DANG NHAP HE THONG                   *" << endl;
                cout << "*                                                *" << endl;
                Utils::printLine(50);
            }
        }
    }
    
    cout << "\n=> Da nhap sai 3 lan. Thoat chuong trinh!" << endl;
    Utils::pause();
    return false;
}

bool Account::verifyLogin(string user, string pass) {
    ifstream file("data/ACCOUNT.txt");
    
    if (!file.is_open()) {
        // Tạo file mới với tài khoản mặc định
        ofstream newFile("data/ACCOUNT.txt");
        newFile << "admin admin" << endl;
        newFile.close();
        
        // Mở lại để đọc
        file.open("data/ACCOUNT.txt");
    }
    
    string fileUser, filePass;
    while (file >> fileUser >> filePass) {
        if (fileUser == user && filePass == pass) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}