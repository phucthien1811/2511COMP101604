#include "../include/Menu.h"
#include "../include/Utils.h"
#include <iostream>

Menu::Menu() {
    bookManager = new BookManager();
    readerManager = new ReaderManager();
    slipManager = new BorrowSlipManager(bookManager, readerManager);
}

Menu::~Menu() {
    delete bookManager;
    delete readerManager;
    delete slipManager;
}

void Menu::displayMainMenu() {
    Utils::clearScreen();
    Utils::printLine(60);
    cout << "*                                                          *" << endl;
    cout << "*          HE THONG QUAN LY THU VIEN                       *" << endl;
    cout << "*                                                          *" << endl;
    Utils::printLine(60);
    
    cout << "\n 1. Quan ly sach" << endl;
    cout << " 2. Quan ly ban doc" << endl;
    cout << " 3. Quan ly phieu muon" << endl;
    cout << " 0. Thoat chuong trinh" << endl;
    
    cout << "\n Chon chuc nang: ";
}

void Menu::run() {
    int choice;
    string input;
    
    do {
        displayMainMenu();
        getline(cin, input);
        choice = Utils::stringToInt(input);
        
        switch (choice) {
            case 1:
                bookManager->showMenu();
                break;
            case 2:
                readerManager->showMenu();
                break;
            case 3:
                slipManager->showMenu();
                break;
            case 0:
                Utils::clearScreen();
                cout << "\n=> Cam on ban da su dung chuong trinh!" << endl;
                break;
            default:
                cout << "\n=> Lua chon khong hop le!" << endl;
                Utils::pause();
        }
    } while (choice != 0);
}