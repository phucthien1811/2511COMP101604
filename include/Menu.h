#ifndef MENU_H
#define MENU_H

#include "Book.h"
#include "Reader.h"
#include "BorrowSlip.h"

class Menu {
private:
    BookManager* bookManager;
    ReaderManager* readerManager;
    BorrowSlipManager* slipManager;
    
public:
    Menu();
    ~Menu();
    
    void displayMainMenu();
    void run();
};

#endif