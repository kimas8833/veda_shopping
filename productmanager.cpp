#include "productmanager.h"
#include "product.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

ProductManager::ProductManager() {
    loadProducts(); // 프로그램 시작 시 파일에서 상품 목록을 로드
}

ProductManager::~ProductManager() {
    saveProducts(); // 프로그램 종료 시 파일에 상품 목록을 저장
    for (auto& p : productList) {
        delete p.second;
    }
}

void ProductManager::loadProducts() {
    ifstream file("productlist.txt");
    if (!file.fail()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, priceStr;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, priceStr, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);

            Product* product = new Product(id, name, price);
            productList[id] = product;
        }
    }
    file.close();
}

void ProductManager::saveProducts() {
    ofstream file("productlist.txt");
    if (!file.fail()) {
        for (const auto& p : productList) {
            file << p.first << "," << p.second->getName() << "," << p.second->getPrice() << endl;
        }
    }
    file.close();
}

void ProductManager::addProduct(Product* product) {
    int id = makeProductId();
    product->setId(id);
    productList[id] = product;
    saveProducts(); // 상품 추가 후 저장
}

void ProductManager::deleteProduct(int id) {
    auto it = productList.find(id);
    if (it != productList.end()) {
        delete it->second;
        productList.erase(it);
        saveProducts(); // 상품 삭제 후 저장
    }
}

void ProductManager::modifyProduct(int id) {
    auto it = productList.find(id);
    if (it != productList.end()) {
        Product* p = it->second;
        string name;
        double price;

        cout << "Current Name: " << p->getName() << endl;
        cout << "Enter new name: ";
        cin >> name;
        p->setName(name);

        cout << "Current Price: " << p->getPrice() << endl;
        cout << "Enter new price: ";
        cin >> price;
        p->setPrice(price);

        productList[id] = p;
        saveProducts(); // 상품 수정 후 저장
    }
}

Product* ProductManager::searchProduct(int id) {
    return productList[id];
}

void ProductManager::displayProducts() {
    cout << endl << "  ID  |    Name    |     Price     " << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& p : productList) {
        // ID 출력 (5자리)
        cout << setw(5) << setfill('0') << right << p.first << " | ";

        // 이름 출력 (10자리)
        cout << setw(10) << setfill(' ') << left << p.second->getName() << " | ";

        // 가격 출력 (10자리)
        cout << setw(10) << setfill(' ') << right << fixed << setprecision(2) << p.second->getPrice() << endl;
    }
}

int ProductManager::makeProductId() {
    if (productList.empty()) return 1;
    return productList.rbegin()->first + 1;
}

bool ProductManager::displayMenu() {
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                    " << endl;
    cout << "  2. Add Product                             " << endl;
    cout << "  3. Delete Product                          " << endl;
    cout << "  4. Modify Product                          " << endl;
    cout << "  5. Quit                                    " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you want to do? ";
    cin >> ch;
    switch (ch) {
        case 1: default:
            displayProducts();
            cin.ignore();
            getchar();
            break;
        case 2:
            {
                string name;
                double price;
                cout << "Enter Product Name: ";
                cin >> name;
                cout << "Enter Product Price: ";
                cin >> price;
                Product* product = new Product(0, name, price); // ID는 addProduct 내부에서 설정
                addProduct(product);
            }
            break;
        case 3:
            displayProducts();
            cout << "Choose Product ID: ";
            cin >> key;
            deleteProduct(key);
            break;
        case 4:
            displayProducts();
            cout << "Choose Product ID: ";
            cin >> key;
            modifyProduct(key);
            break;
        case 5:
            return false;
    }
    return true;
}
