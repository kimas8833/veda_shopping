#include "shoplist.h"
#include "productmanager.h"
#include <iostream>
#include <iomanip>


void Shoplist::addProduct(Product* product, int quantity) {
    int id = product->getId();
    if (cart.find(id) != cart.end()) {
        cart[id].second += quantity;  // 이미 장바구니에 있으면 수량 추가
    } else {
        cart[id] = std::make_pair(product, quantity);  // 새로 추가
    }
}

void Shoplist::removeProduct(int id) {
    if (cart.find(id) != cart.end()) {
        cart.erase(id);
    } else {
        std::cout << "Product not found in the cart!" << std::endl;
    }
}

void Shoplist::displayCart() {
    cout << endl << "  ID  |      Name      |    Price     |  Quantity  " << endl;
    cout << "----------------------------------------------------" << endl;
    for (const auto& item : cart) {
        Product* product = item.second.first;
        int quantity = item.second.second;

        // ID 출력 (5자리)
        cout << setw(5) << setfill('0') << right << product->getId() << " | ";

        // 이름 출력 (14자리)
        cout << setw(14) << setfill(' ') << left << product->getName() << " | ";

        // 가격 출력 (10자리)
        cout << setw(10) << setfill(' ') << right << fixed << setprecision(2) << product->getPrice() << " | ";

        // 수량 출력 (10자리)
        cout << setw(10) << setfill(' ') << right << quantity << endl;
    }
}

double Shoplist::calculateTotal() {
    double total = 0.0;
    for (const auto& item : cart) {
        Product* product = item.second.first;
        int quantity = item.second.second;
        total += product->getPrice() * quantity;
    }
    return total;
}

bool Shoplist::displayMenu(ProductManager& productManager) {
    int ch, key, quantity;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Shopping Cart                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Cart                            " << endl;
    cout << "  2. Add Product to Cart                     " << endl;
    cout << "  3. Remove Product from Cart                " << endl;
    cout << "  4. Display Total Price                     " << endl;
    cout << "  5. Quit                                    " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you want to do? ";
    cin >> ch;
    switch (ch) {
        case 1: default:
            displayCart();
            cin.ignore();
            getchar();
            break;
        case 2:
            // 상품 ID를 입력받아 장바구니에 추가
            cout << "Enter Product ID to add: ";
            cin >> key;
            cout << "Enter quantity: ";
            cin >> quantity;
            {
                Product* product = productManager.searchProduct(key);
                if (product != nullptr) {
                    addProduct(product, quantity);
                    cout << quantity << " of " << product->getName() << " added to cart!" << endl;
                } else {
                    cout << "Product not found!" << endl;
                }
            }
            cin.ignore();
            getchar();
            break;
        case 3:
            displayCart();
            cout << "Choose Product ID to remove: ";
            cin >> key;
            removeProduct(key);
            cin.ignore();
            getchar();
            break;
        case 4:
            cout << "Total Price: " << calculateTotal() << endl;
            cin.ignore();
            getchar();
            break;
        case 5:
            return false;
    }
    return true;
}
