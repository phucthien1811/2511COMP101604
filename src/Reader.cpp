#include "../include/Reader.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Constructor
Reader::Reader() {
    maBanDoc = "";
    hoTen = "";
    ngaySinh = "";
    diaChi = "";
    soDienThoai = "";
    ngayDangKy = "";
}

Reader::Reader(string ma, string ten, string ns, string dc, string sdt, string ngayDK) {
    maBanDoc = ma;
    hoTen = ten;
    ngaySinh = ns;
    diaChi = dc;
    soDienThoai = sdt;
    ngayDangKy = ngayDK;
}

// Getter
string Reader::getMaBanDoc() { return maBanDoc; }
string Reader::getHoTen() { return hoTen; }
string Reader::getNgaySinh() { return ngaySinh; }
string Reader::getDiaChi() { return diaChi; }
string Reader::getSoDienThoai() { return soDienThoai; }
string Reader::getNgayDangKy() { return ngayDangKy; }

// Setter
void Reader::setMaBanDoc(string ma) { maBanDoc = ma; }
void Reader::setHoTen(string ten) { hoTen = ten; }
void Reader::setNgaySinh(string ns) { ngaySinh = ns; }
void Reader::setDiaChi(string dc) { diaChi = dc; }
void Reader::setSoDienThoai(string sdt) { soDienThoai = sdt; }
void Reader::setNgayDangKy(string ngay) { ngayDangKy = ngay; }

void Reader::displayHeader() {
    cout << left << setw(10) << "Ma Ban Doc"
         << setw(22) << "Ho Ten"
         << setw(12) << "Ngay Sinh"
         << setw(35) << "Dia Chi"
         << setw(14) << "So Dien Thoai"
         << setw(12) << "Ngay DK" << endl;
    Utils::printLine(105);
}

void Reader::display() {
    cout << left << setw(10) << maBanDoc
         << setw(22) << hoTen
         << setw(12) << ngaySinh
         << setw(35) << diaChi
         << setw(14) << soDienThoai
         << setw(12) << ngayDangKy << endl;
}

string Reader::toString() {
    return maBanDoc + "|" + hoTen + "|" + ngaySinh + "|" + diaChi + "|" + 
           soDienThoai + "|" + ngayDangKy;
}

Reader Reader::fromString(string line) {
    stringstream ss(line);
    string ma, ten, ns, dc, sdt, ngayDK;
    
    getline(ss, ma, '|');
    getline(ss, ten, '|');
    getline(ss, ns, '|');
    getline(ss, dc, '|');
    getline(ss, sdt, '|');
    getline(ss, ngayDK, '|');
    
    return Reader(ma, ten, ns, dc, sdt, ngayDK);
}

// ReaderManager
ReaderManager::ReaderManager() {
    filename = "data/DOCGIA.txt";
    loadFromFile();
}

void ReaderManager::loadFromFile() {
    readers.clear();
    ifstream file(filename);
    
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            readers.push_back(Reader::fromString(line));
        }
    }
    
    file.close();
}

void ReaderManager::saveToFile() {
    ofstream file(filename);
    
    for (int i = 0; i < readers.size(); i++) {
        file << readers[i].toString() << endl;
    }
    
    file.close();
}

void ReaderManager::addReader() {
    Utils::clearScreen();
    Utils::printHeader("THEM BAN DOC MOI");
    
    Reader reader;
    string input;
    
    cout << "\n Nhap ma ban doc: ";
    getline(cin, input);
    
    if (readerExists(input)) {
        cout << "\n=> Ma ban doc da ton tai!" << endl;
        Utils::pause();
        return;
    }
    
    reader.setMaBanDoc(input);
    
    cout << " Nhap ho ten: ";
    getline(cin, input);
    reader.setHoTen(input);
    
    cout << " Nhap ngay sinh (DD/MM/YYYY): ";
    getline(cin, input);
    reader.setNgaySinh(input);
    
    cout << " Nhap dia chi: ";
    getline(cin, input);
    reader.setDiaChi(input);
    
    cout << " Nhap so dien thoai: ";
    getline(cin, input);
    reader.setSoDienThoai(input);
    
    reader.setNgayDangKy(Utils::getCurrentDate());
    
    readers.push_back(reader);
    saveToFile();
    
    cout << "\n=> Them ban doc thanh cong!" << endl;
    Utils::pause();
}

void ReaderManager::displayAllReaders() {
    Utils::clearScreen();
    Utils::printHeader("DANH SACH BAN DOC");
    
    if (readers.empty()) {
        cout << "\n=> Khong co ban doc nao!" << endl;
        Utils::pause();
        return;
    }
    
    cout << endl;
    Reader::displayHeader();
    
    for (int i = 0; i < readers.size(); i++) {
        readers[i].display();
    }
    
    cout << "\nTong so ban doc: " << readers.size() << endl;
    Utils::pause();
}

void ReaderManager::searchReader() {
    Utils::clearScreen();
    Utils::printHeader("TIM KIEM BAN DOC");
    
    cout << "\n Nhap ma ban doc can tim: ";
    string maBanDoc;
    getline(cin, maBanDoc);
    
    bool found = false;
    
    cout << endl;
    Reader::displayHeader();
    
    for (int i = 0; i < readers.size(); i++) {
        if (readers[i].getMaBanDoc() == maBanDoc) {
            readers[i].display();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\n=> Khong tim thay ban doc!" << endl;
    }
    
    Utils::pause();
}

void ReaderManager::deleteReader() {
    Utils::clearScreen();
    Utils::printHeader("XOA BAN DOC");
    
    cout << "\n Nhap ma ban doc can xoa: ";
    string maBanDoc;
    getline(cin, maBanDoc);
    
    for (int i = 0; i < readers.size(); i++) {
        if (readers[i].getMaBanDoc() == maBanDoc) {
            readers.erase(readers.begin() + i);
            saveToFile();
            cout << "\n=> Xoa ban doc thanh cong!" << endl;
            Utils::pause();
            return;
        }
    }
    
    cout << "\n=> Khong tim thay ban doc!" << endl;
    Utils::pause();
}

bool ReaderManager::readerExists(string maBanDoc) {
    for (int i = 0; i < readers.size(); i++) {
        if (readers[i].getMaBanDoc() == maBanDoc) {
            return true;
        }
    }
    return false;
}

Reader* ReaderManager::findReader(string maBanDoc) {
    for (int i = 0; i < readers.size(); i++) {
        if (readers[i].getMaBanDoc() == maBanDoc) {
            return &readers[i];
        }
    }
    return nullptr;
}

void ReaderManager::showMenu() {
    int choice;
    string input;
    
    do {
        Utils::clearScreen();
        Utils::printHeader("QUAN LY BAN DOC");
        
        cout << "\n 1. Hien thi danh sach ban doc" << endl;
        cout << " 2. Them ban doc" << endl;
        cout << " 3. Tim kiem ban doc" << endl;
        cout << " 4. Xoa ban doc" << endl;
        cout << " 0. Quay lai" << endl;
        
        cout << "\n Chon chuc nang: ";
        getline(cin, input);
        choice = Utils::stringToInt(input);
        
        switch (choice) {
            case 1:
                displayAllReaders();
                break;
            case 2:
                addReader();
                break;
            case 3:
                searchReader();
                break;
            case 4:
                deleteReader();
                break;
            case 0:
                break;
            default:
                cout << "\n=> Lua chon khong hop le!" << endl;
                Utils::pause();
        }
    } while (choice != 0);
}