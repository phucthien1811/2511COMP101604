#include "../include/BorrowSlip.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Constructor
BorrowSlip::BorrowSlip() {
    soPhieu = "";
    maBanDoc = "";
    maSach = "";
    ngayMuon = "";
    ngayTraDuKien = "";
    tinhTrang = 1;
}

BorrowSlip::BorrowSlip(string sp, string maBD, string ms, string nm, string nt, int tt) {
    soPhieu = sp;
    maBanDoc = maBD;
    maSach = ms;
    ngayMuon = nm;
    ngayTraDuKien = nt;
    tinhTrang = tt;
}

// Getter
string BorrowSlip::getSoPhieu() { return soPhieu; }
string BorrowSlip::getMaBanDoc() { return maBanDoc; }
string BorrowSlip::getMaSach() { return maSach; }
string BorrowSlip::getNgayMuon() { return ngayMuon; }
string BorrowSlip::getNgayTraDuKien() { return ngayTraDuKien; }
int BorrowSlip::getTinhTrang() { return tinhTrang; }

// Setter
void BorrowSlip::setSoPhieu(string sp) { soPhieu = sp; }
void BorrowSlip::setMaBanDoc(string maBD) { maBanDoc = maBD; }
void BorrowSlip::setMaSach(string ms) { maSach = ms; }
void BorrowSlip::setNgayMuon(string ngay) { ngayMuon = ngay; }
void BorrowSlip::setNgayTraDuKien(string ngay) { ngayTraDuKien = ngay; }
void BorrowSlip::setTinhTrang(int tt) { tinhTrang = tt; }

void BorrowSlip::displayHeader() {
    cout << left << setw(10) << "So Phieu"
         << setw(12) << "Ma Ban Doc"
         << setw(10) << "Ma Sach"
         << setw(14) << "Ngay Muon"
         << setw(14) << "Ngay Tra DK"
         << setw(14) << "Tinh Trang" << endl;
    Utils::printLine(74);
}

void BorrowSlip::display() {
    cout << left << setw(10) << soPhieu
         << setw(12) << maBanDoc
         << setw(10) << maSach
         << setw(14) << ngayMuon
         << setw(14) << ngayTraDuKien
         << setw(14) << (tinhTrang == 1 ? "Dang muon" : "Da tra") << endl;
}

string BorrowSlip::toString() {
    return soPhieu + "|" + maBanDoc + "|" + maSach + "|" + ngayMuon + "|" + 
           ngayTraDuKien + "|" + Utils::intToString(tinhTrang);
}

BorrowSlip BorrowSlip::fromString(string line) {
    stringstream ss(line);
    string sp, maBD, ms, nm, nt, ttStr;
    
    getline(ss, sp, '|');
    getline(ss, maBD, '|');
    getline(ss, ms, '|');
    getline(ss, nm, '|');
    getline(ss, nt, '|');
    getline(ss, ttStr, '|');
    
    int tt = Utils::stringToInt(ttStr);
    
    return BorrowSlip(sp, maBD, ms, nm, nt, tt);
}

// BorrowSlipManager
BorrowSlipManager::BorrowSlipManager(BookManager* bm, ReaderManager* rm) {
    filename = "data/PHIEUMUON.txt";
    bookManager = bm;
    readerManager = rm;
    loadFromFile();
}

void BorrowSlipManager::loadFromFile() {
    slips.clear();
    ifstream file(filename);
    
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            slips.push_back(BorrowSlip::fromString(line));
        }
    }
    
    file.close();
}

void BorrowSlipManager::saveToFile() {
    ofstream file(filename);
    
    for (int i = 0; i < slips.size(); i++) {
        file << slips[i].toString() << endl;
    }
    
    file.close();
}

string BorrowSlipManager::generateSlipNumber() {
    int maxNum = 0;
    
    for (int i = 0; i < slips.size(); i++) {
        string sp = slips[i].getSoPhieu();
        if (sp.length() >= 2) {
            string numStr = sp.substr(2);
            int num = Utils::stringToInt(numStr);
            if (num > maxNum) {
                maxNum = num;
            }
        }
    }
    
    maxNum++;
    string result = "PM";
    
    if (maxNum < 10) result += "00";
    else if (maxNum < 100) result += "0";
    
    result += Utils::intToString(maxNum);
    
    return result;
}

void BorrowSlipManager::borrowBook() {
    Utils::clearScreen();
    Utils::printHeader("MUON SACH");
    
    string maBanDoc, maSach;
    
    cout << "\n Nhap ma ban doc: ";
    getline(cin, maBanDoc);
    
    if (!readerManager->readerExists(maBanDoc)) {
        cout << "\n=> Ma ban doc khong ton tai!" << endl;
        Utils::pause();
        return;
    }
    
    cout << " Nhap ma sach: ";
    getline(cin, maSach);
    
    Book* book = bookManager->findBook(maSach);
    
    if (book == nullptr) {
        cout << "\n=> Ma sach khong ton tai!" << endl;
        Utils::pause();
        return;
    }
    
    if (book->getTinhTrang() == 0) {
        cout << "\n=> Sach da duoc muon het!" << endl;
        Utils::pause();
        return;
    }
    
    // Tạo phiếu mượn
    BorrowSlip slip;
    slip.setSoPhieu(generateSlipNumber());
    slip.setMaBanDoc(maBanDoc);
    slip.setMaSach(maSach);
    slip.setNgayMuon(Utils::getCurrentDate());
    slip.setNgayTraDuKien(Utils::calculateReturnDate(slip.getNgayMuon()));
    slip.setTinhTrang(1);
    
    slips.push_back(slip);
    saveToFile();
    
    // Cập nhật tình trạng sách
    bookManager->updateBookStatus(maSach, book->getTinhTrang() - 1);
    
    cout << "\n=> Muon sach thanh cong!" << endl;
    cout << " So phieu muon: " << slip.getSoPhieu() << endl;
    cout << " Ngay tra du kien: " << slip.getNgayTraDuKien() << endl;
    Utils::pause();
}

void BorrowSlipManager::returnBook() {
    Utils::clearScreen();
    Utils::printHeader("TRA SACH");
    
    cout << "\n Nhap so phieu muon: ";
    string soPhieu;
    getline(cin, soPhieu);
    
    for (int i = 0; i < slips.size(); i++) {
        if (slips[i].getSoPhieu() == soPhieu) {
            if (slips[i].getTinhTrang() == 0) {
                cout << "\n=> Sach da duoc tra roi!" << endl;
                Utils::pause();
                return;
            }
            
            // Cập nhật phiếu mượn
            slips[i].setTinhTrang(0);
            saveToFile();
            
            // Cập nhật tình trạng sách
            Book* book = bookManager->findBook(slips[i].getMaSach());
            if (book != nullptr) {
                bookManager->updateBookStatus(slips[i].getMaSach(), book->getTinhTrang() + 1);
            }
            
            cout << "\n=> Tra sach thanh cong!" << endl;
            Utils::pause();
            return;
        }
    }
    
    cout << "\n=> Khong tim thay phieu muon!" << endl;
    Utils::pause();
}

void BorrowSlipManager::displayAllSlips() {
    Utils::clearScreen();
    Utils::printHeader("DANH SACH PHIEU MUON");
    
    if (slips.empty()) {
        cout << "\n=> Khong co phieu muon nao!" << endl;
        Utils::pause();
        return;
    }
    
    cout << endl;
    BorrowSlip::displayHeader();
    
    for (int i = 0; i < slips.size(); i++) {
        slips[i].display();
    }
    
    cout << "\nTong so phieu muon: " << slips.size() << endl;
    Utils::pause();
}

void BorrowSlipManager::searchSlip() {
    Utils::clearScreen();
    Utils::printHeader("TIM KIEM PHIEU MUON");
    
    cout << "\n Nhap so phieu muon: ";
    string soPhieu;
    getline(cin, soPhieu);
    
    bool found = false;
    
    cout << endl;
    BorrowSlip::displayHeader();
    
    for (int i = 0; i < slips.size(); i++) {
        if (slips[i].getSoPhieu() == soPhieu) {
            slips[i].display();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\n=> Khong tim thay phieu muon!" << endl;
    }
    
    Utils::pause();
}

bool BorrowSlipManager::slipExists(string soPhieu) {
    for (int i = 0; i < slips.size(); i++) {
        if (slips[i].getSoPhieu() == soPhieu) {
            return true;
        }
    }
    return false;
}

BorrowSlip* BorrowSlipManager::findSlip(string soPhieu) {
    for (int i = 0; i < slips.size(); i++) {
        if (slips[i].getSoPhieu() == soPhieu) {
            return &slips[i];
        }
    }
    return nullptr;
}

void BorrowSlipManager::showMenu() {
    int choice;
    string input;
    
    do {
        Utils::clearScreen();
        Utils::printHeader("QUAN LY PHIEU MUON");
        
        cout << "\n 1. Hien thi tat ca phieu muon" << endl;
        cout << " 2. Muon sach" << endl;
        cout << " 3. Tra sach" << endl;
        cout << " 4. Tim kiem phieu muon" << endl;
        cout << " 0. Quay lai" << endl;
        
        cout << "\n Chon chuc nang: ";
        getline(cin, input);
        choice = Utils::stringToInt(input);
        
        switch (choice) {
            case 1:
                displayAllSlips();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                searchSlip();
                break;
            case 0:
                break;
            default:
                cout << "\n=> Lua chon khong hop le!" << endl;
                Utils::pause();
        }
    } while (choice != 0);
}