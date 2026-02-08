#pragma once
#include "pch.h"
#include "Payer.h"

class Payers {
private:
    list<Payer> list_;
    int nextId_ = 1;

public:
    Payers();

    void addPayer();
    void deleteById(int id);
    list<Payer> selectByTariff(double tariff) const;
    list<Payer> selectByDiscount(int discount) const;
    list<Payer> selectBySumRange(double low, double high) const;
    void sortById();
    void sortByName();
    void sortBySumDescending();
    void changePayer(int id);

    const list<Payer>& getList() const { return list_; }

    void saveToCSV(const string& fname) const;
    void loadFromCSV(const string& fname);
};