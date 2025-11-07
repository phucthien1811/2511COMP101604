#include "../include/Book.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Constructor
Book::Book() {
    maSach = "";
    tenSach = "";
    tacGia = "";
    nxb = "";
    giaBan = 0;
    namPhatHanh = 0;
    soTrang = 0;
    ngayNhapKho = "";
    tinhTrang = 0;
}

Book::Book(string ma, string ten, string tg, string nxbP, double gia, 
           int nam, int trang, string ngayNhap, int tt) {
    maSach = ma;
    tenSach = ten;
    tacGia = tg;
    nxb = nxbP;
    giaBan = gia;
    namPhatHanh = nam;
    soTrang = trang;
    ngayNhapKho = ngayNhap;
    tinhTrang = tt;
}

// Getter
string Book::getMaSach() { return maSach; }
string Book::getTenSach() { return tenSach; }
string Book::getTacGia() { return tacGia; }
string Book::getNXB() { return nxb; }
double Book::getGiaBan() { return giaBan; }
int Book::getNamPhatHanh() { return namPhatHanh; }
int Book::getSoTrang() { return soTrang; }
string Book::getNgayNhapKho() { return ngayNhapKho; }
int Book::getTinhTrang() { return tinhTrang; }

// Setter
void Book::setMaSach(string ma) { maSach = ma; }
void Book::setTenSach(string ten) { tenSach = ten; }
void Book::setTacGia(string tg) { tacGia = tg; }
void Book::setNXB(string nxbP) { nxb = nxbP; }
void Book::setGiaBan(double gia) { giaBan = gia; }
void Book::setNamPhatHanh(int nam) { namPhatHanh = nam; }
void Book::setSoTrang(int trang) { soTrang = trang; }
void Book::setNgayNhapKho(string ngay) { ngayNhapKho = ngay; }
void Book::setTinhTrang(int tt) { tinhTrang = tt; }

void Book::displayHeader() {
    cout << left << setw(8) << "Ma Sach" 
         << setw(35) << "Ten Sach"
         << setw(20) << "Tac Gia"
         << setw(25) << "NXB"
         << setw(12) << "Gia Ban"
         << setw(8) << "Nam PH"
         << setw(10) << "So Trang"
         << setw(12) << "Ngay Nhap"
         << setw(12) << "Tinh Trang" << endl;
    Utils::printLine(142);
}

void Book::display() {
    cout << left << setw(8) << maSach
         << setw(35) << tenSach
         << setw(20) << tacGia
         << setw(25) << nxb
         << setw(12) << fixed << setprecision(0) << giaBan
         << setw(8) << namPhatHanh
         << setw(10) << soTrang
         << setw(12) << ngayNhapKho
         << setw(12) << (tinhTrang == 0 ? "Da muon" : "Con " + Utils::intToString(tinhTrang)) << endl;
}

string Book::toString() {
    return maSach + "|" + tenSach + "|" + tacGia + "|" + nxb + "|" + 
           Utils::intToString((int)giaBan) + "|" + Utils::intToString(namPhatHanh) + "|" + 
           Utils::intToString(soTrang) + "|" + ngayNhapKho + "|" + Utils::intToString(tinhTrang);
}

Book Book::fromString(string line) {
    stringstream ss(line);
    string ma, ten, tg, nxbP, giaStr, namStr, trangStr, ngay, ttStr;
    
    getline(ss, ma, '|');
    getline(ss, ten, '|');
    getline(ss, tg, '|');
    getline(ss, nxbP, '|');
    getline(ss, giaStr, '|');
    getline(ss, namStr, '|');
    getline(ss, trangStr, '|');
    getline(ss, ngay, '|');
    getline(ss, ttStr, '|');
    
    double gia = Utils::stringToInt(giaStr);
    int nam = Utils::stringToInt(namStr);
    int trang = Utils::stringToInt(trangStr);
    int tt = Utils::stringToInt(ttStr);
    
    return Book(ma, ten, tg, nxbP, gia, nam, trang, ngay, tt);
}

// BookManager
BookManager::BookManager() {
    filename = "data/SACH.txt";
    loadFromFile();
}

void BookManager::loadFromFile() {
    books.clear();
    ifstream file(filename);
    
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            books.push_back(Book::fromString(line));
        }
    }
    
    file.close();
}

void BookManager::saveToFile() {
    ofstream file(filename);
    
    for (int i = 0; i < books.size(); i++) {
        file << books[i].toString() << endl;
    }
    
    file.close();
}

void BookManager::addBook() {
    Utils::clearScreen();
    Utils::printHeader("THEM SACH MOI");
    
    Book book;
    string input;
    
    cout << "\n Nhap ma sach: ";
    getline(cin, input);
    
    if (bookExists(input)) {
        cout << "\n=> Ma sach da ton tai!" << endl;
        Utils::pause();
        return;
    }
    
    book.setMaSach(input);
    
    cout << " Nhap ten sach: ";
    getline(cin, input);
    book.setTenSach(input);
    
    cout << " Nhap tac gia: ";
    getline(cin, input);
    book.setTacGia(input);
    
    cout << " Nhap nha xuat ban: ";
    getline(cin, input);
    book.setNXB(input);
    
    cout << " Nhap gia ban: ";
    getline(cin, input);
    book.setGiaBan(Utils::stringToInt(input));
    
    cout << " Nhap nam phat hanh: ";
    getline(cin, input);
    book.setNamPhatHanh(Utils::stringToInt(input));
    
    cout << " Nhap so trang: ";
    getline(cin, input);
    book.setSoTrang(Utils::stringToInt(input));
    
    book.setNgayNhapKho(Utils::getCurrentDate());
    
    cout << " Nhap so luong: ";
    getline(cin, input);
    book.setTinhTrang(Utils::stringToInt(input));
    
    books.push_back(book);
    saveToFile();
    
    cout << "\n=> Them sach thanh cong!" << endl;
    Utils::pause();
}

void BookManager::displayAllBooks() {
    Utils::clearScreen();
    Utils::printHeader("DANH SACH SACH");
    
    if (books.empty()) {
        cout << "\n=> Khong co sach nao trong thu vien!" << endl;
        Utils::pause();
        return;
    }
    
    cout << endl;
    Book::displayHeader();
    
    for (int i = 0; i < books.size(); i++) {
        books[i].display();
    }
    
    cout << "\nTong so sach: " << books.size() << endl;
    Utils::pause();
}

void BookManager::searchBook() {
    Utils::clearScreen();
    Utils::printHeader("TIM KIEM SACH");
    
    cout << "\n Nhap ma sach can tim: ";
    string maSach;
    getline(cin, maSach);
    
    bool found = false;
    
    cout << endl;
    Book::displayHeader();
    
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getMaSach() == maSach) {
            books[i].display();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\n=> Khong tim thay sach!" << endl;
    }
    
    Utils::pause();
}

void BookManager::deleteBook() {
    Utils::clearScreen();
    Utils::printHeader("XOA SACH");
    
    cout << "\n Nhap ma sach can xoa: ";
    string maSach;
    getline(cin, maSach);
    
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getMaSach() == maSach) {
            if (books[i].getTinhTrang() == 0) {
                cout << "\n=> Khong the xoa sach dang duoc muon!" << endl;
                Utils::pause();
                return;
            }
            
            books.erase(books.begin() + i);
            saveToFile();
            cout << "\n=> Xoa sach thanh cong!" << endl;
            Utils::pause();
            return;
        }
    }
    
    cout << "\n=> Khong tim thay sach!" << endl;
    Utils::pause();
}

bool BookManager::bookExists(string maSach) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getMaSach() == maSach) {
            return true;
        }
    }
    return false;
}

Book* BookManager::findBook(string maSach) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getMaSach() == maSach) {
            return &books[i];
        }
    }
    return nullptr;
}

void BookManager::updateBookStatus(string maSach, int newStatus) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getMaSach() == maSach) {
            books[i].setTinhTrang(newStatus);
            saveToFile();
            return;
        }
    }
}

void BookManager::showMenu() {
    int choice;
    string input;
    
    do {
        Utils::clearScreen();
        Utils::printHeader("QUAN LY SACH");
        
        cout << "\n 1. Hien thi thong tin sach" << endl;
        cout << " 2. Them sach" << endl;
        cout << " 3. Tim kiem sach" << endl;
        cout << " 4. Xoa sach" << endl;
        cout << " 0. Quay lai" << endl;
        
        cout << "\n Chon chuc nang: ";
        getline(cin, input);
        choice = Utils::stringToInt(input);
        
        switch (choice) {
            case 1:
                displayAllBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 0:
                break;
            default:
                cout << "\n=> Lua chon khong hop le!" << endl;
                Utils::pause();
        }
    } while (choice != 0);
}