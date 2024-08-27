#ifndef __PRODUCT_MANAGER_H__
#define __PRODUCT_MANAGER_H__

#include <map>
#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();
    ~ProductManager();

    void addProduct(Product* product);
    void deleteProduct(int id);
    void modifyProduct(int id);
    Product* searchProduct(int id);
    void displayProducts();

    bool displayMenu();

private:
    map<int, Product*> productList;
    int makeProductId();

    void loadProducts();
    void saveProducts();
};

#endif // __PRODUCT_MANAGER_H__
