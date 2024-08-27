#include "product.h"

Product::Product(int id, string name, double price)
    : m_id(id), m_name(name), m_price(price) {}

int Product::getId() const {
    return m_id;
}

void Product::setId(int id) {
    m_id = id;
}

string Product::getName() const {
    return m_name;
}

void Product::setName(string name) {
    m_name = name;
}

double Product::getPrice() const {
    return m_price;
}

void Product::setPrice(double price) {
    m_price = price;
}
