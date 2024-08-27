#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>

using namespace std;

class Product {
public:
    Product(int id = 0, string name = "", double price = 0.0);
    int getId() const;
    void setId(int id);
    string getName() const;
    void setName(string name);
    double getPrice() const;
    void setPrice(double price);

private:
    int m_id;
    string m_name;
    double m_price;
};

#endif // __PRODUCT_H__
