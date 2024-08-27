#ifndef __SHOPLIST_H__
#define __SHOPLIST_H__

#include <map>
#include "product.h"

class ProductManager;

class Shoplist {
public:
    void addProduct(Product* product, int quantity);
    void removeProduct(int id);
    void displayCart();
    double calculateTotal();
    bool displayMenu(ProductManager& productManager);

private:
    std::map<int, std::pair<Product*, int>> cart;  // Product ID와 (Product 포인터, 수량)의 쌍을 저장하는 map
};

#endif // __SHOPLIST_H__
