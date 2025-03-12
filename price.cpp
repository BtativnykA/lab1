#include <iostream>
#include <fstream>
#include "price.h" 
using namespace std;

// Функція додає дві ціни і змінює результат 
void addPrices(Price a, Price b, Price &result) {
    result.hryvnias = a.hryvnias + b.hryvnias;
    result.kopiyky = a.kopiyky + b.kopiyky;
    if (result.kopiyky >= 100) { // Якщо більше 100 копійок – переводимо у гривні
        result.hryvnias++;
        result.kopiyky -= 100;
    }
}

// Функція множить ціну на кількість товарів і записує у `result`
void multiplyPrice(Price p, int quantity, Price &result) {
    int total = (p.hryvnias * 100 + p.kopiyky) * quantity;
    result.hryvnias = total / 100;
    result.kopiyky = total % 100;
}

// Функція округлює ціну до 10 копійок і змінює `p`
void roundTo10Kop(Price &p) {
    int total = (p.hryvnias * 100 + p.kopiyky + 5) / 10 * 10;
    p.hryvnias = total / 100;
    p.kopiyky = total % 100; 
}

// Основна функція - обробляє файл і виводить чек
void processFile() {
    ifstream file("price.txt"); // Відкриваємо файл
    if (!file) { // Якщо не відкрився – виводимо помилку
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    Price total = {0, 0};  // Початкова сума = 0 грн 0 коп
    int h, k, q;

    cout << "Чек:\n";

    while (file >> h >> k >> q) { // Читаємо грн, коп, кількість
        Price temp = {h, k}; // Формуємо структуру ціни
        Price itemTotal;
        multiplyPrice(temp, q, itemTotal); // Рахуємо загальну ціну 
        addPrices(total, itemTotal, total); // Додаємо до загальної суми
       
        // Вивід для кожного товару
        cout << q << " шт. × " << h << " грн " << k << " коп = " 
             << itemTotal.hryvnias << " грн " << itemTotal.kopiyky << " коп\n";
    }

    roundTo10Kop(total); // Округляємо загальну суму
    
    // Вивід підсумку
    cout << "Загальна сума (після округлення): " << total.hryvnias << " грн " << total.kopiyky << " коп\n";
}