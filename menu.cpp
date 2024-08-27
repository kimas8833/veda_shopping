#include <iostream>
#include "clientmanager.h"
#include "productmanager.h"
#include "shoplist.h"

using namespace std;

bool displayMainMenu() {
    ClientManager cm;
    ProductManager pm;
    Shoplist sl;

    bool running = true;
    while (running) {
        int choice;
        cout << "\033[2J\033[1;1H";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                Main Menu                    " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. Client Manager                          " << endl;
        cout << "  2. Product Manager                         " << endl;
        cout << "  3. Shopping Cart                           " << endl;
        cout << "  4. Quit                                    " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << " What do you want to do? ";
        cin >> choice;

        switch (choice) {
            case 1:
                while (cm.displayMenu());
                break;
            case 2:
                while (pm.displayMenu());
                break;
            case 3:
                while (sl.displayMenu(pm));  // ProductManager 객체를 인자로 전달
                break;
            case 4:
                running = false;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
    return running;
}
