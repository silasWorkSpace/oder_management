#include <iostream>
#include <string>
#include "manager.h"

using namespace std;

void showMenu() {
    cout << "\n===== ORDER MANAGEMENT (MULTI-PRODUCT) =====\n";
    cout << "1. Add new order\n";
    cout << "2. Remove order by ID\n";
    cout << "3. Search order by ID\n";
    cout << "4. Search orders by customer name\n";
    cout << "5. Show all orders (sorted by ID)\n";
    cout << "6. Save to file\n";
    cout << "7. Load from file\n";
    cout << "0. Exit\n";
    cout << "=> Your choice: ";
}

int main() {
    Manager mgr;
    mgr.init();
    const string path = "data.txt";

    string choice;
    while (true) {
        showMenu();
        getline(cin, choice);

        if (choice == "1")       mgr.addOrUpdate();
        else if (choice == "2")  mgr.remove();
        else if (choice == "3")  mgr.searchById();
        else if (choice == "4")  mgr.searchByCustomer();
        else if (choice == "5")  mgr.showAllSorted();
        else if (choice == "6")  mgr.save(path);
        else if (choice == "7")  mgr.load(path);
        else if (choice == "0") {
            cout << "Exit.\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
