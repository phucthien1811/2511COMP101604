#include "../include/Utils.h"
#include <iostream>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <algorithm>

void Utils::clearScreen() {
    system("cls");
}

void Utils::pause() {
    cout << "\nNhan phim bat ky de tiep tuc...";
    _getch();
}

string Utils::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string day = intToString(ltm->tm_mday);
    string month = intToString(1 + ltm->tm_mon);
    string year = intToString(1900 + ltm->tm_year);
    
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;
    
    return day + "/" + month + "/" + year;
}

string Utils::calculateReturnDate(string borrowDate) {
    // Tách ngày/tháng/năm
    int day, month, year;
    sscanf(borrowDate.c_str(), "%d/%d/%d", &day, &month, &year);
    
    // Cộng thêm 7 ngày
    day += 7;
    
    // Xử lý tràn tháng (đơn giản hóa)
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Năm nhuận
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    
    while (day > daysInMonth[month - 1]) {
        day -= daysInMonth[month - 1];
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    
    string d = intToString(day);
    string m = intToString(month);
    string y = intToString(year);
    
    if (d.length() == 1) d = "0" + d;
    if (m.length() == 1) m = "0" + m;
    
    return d + "/" + m + "/" + y;
}

int Utils::stringToInt(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    return result;
}

string Utils::intToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

bool Utils::isNumber(string s) {
    if (s.empty()) return false;
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

string Utils::inputPassword() {
    string password = "";
    char ch;
    
    while (true) {
        ch = _getch();
        
        if (ch == 13) { // Enter
            break;
        } else if (ch == 8) { // Backspace
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    
    return password;
}

void Utils::printHeader(string title) {
    printLine();
    int spaces = (80 - title.length()) / 2;
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << title << endl;
    printLine();
}

void Utils::printLine(int length) {
    for (int i = 0; i < length; i++) {
        cout << "=";
    }
    cout << endl;
}

string Utils::trim(string s) {
    // Xóa khoảng trắng đầu
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    
    // Xóa khoảng trắng cuối
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
    
    return s;
}

bool Utils::fileExists(string filename) {
    ifstream file(filename);
    return file.good();
}