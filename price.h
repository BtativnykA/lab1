#ifndef PRICE_H
#define PRICE_H

#include <iostream>
#include <fstream>

using namespace std;

struct Price {
    int hryvnias;
    short int kopiyky;
};
void addPrices(Price a, Price b, Price &result);
void multiplyPrice(Price p, int quantity, Price &result);
void roundTo10Kop(Price &p);
void processFile();

#endif