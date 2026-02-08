#include "Payers.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>  // для runtime_error

void checkInputFormat(istringstream& iss) {
    if (iss.fail()) throw runtime_error("CSV: неверный формат числа");
}

Payers::Payers() {
    for (int i = 0; i < 15; ++i) {
        list_.push_back(Payer::createFactory(nextId_++));
    }
}

void Payers::addPayer() {
    list_.push_back(Payer::createFactory(nextId_++));
}

void Payers::deleteById(int id) {
    auto it = remove_if(list_.begin(), list_.end(), [id](const Payer& p) { return p.getId() == id; });
    list_.erase(it, list_.end());
}

list<Payer> Payers::selectByTariff(double tariff) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [tariff](const Payer& p) {
        return eq(p.getTariff(), tariff);
        });
    return result;
}

list<Payer> Payers::selectByDiscount(int discount) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [discount](const Payer& p) {
        return p.getDiscount() == discount;
        });
    return result;
}

list<Payer> Payers::selectBySumRange(double low, double high) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [low, high](const Payer& p) {
        double sum = p.calculateSum();
        return sum >= low && sum <= high;
        });
    result.sort([](const Payer& a, const Payer& b) { return a.getPhone() < b.getPhone(); });
    return result;
}

void Payers::sortById() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getId() < b.getId(); });
}

void Payers::sortByName() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getName() < b.getName(); });
}

void Payers::sortBySumDescending() {
    list_.sort([](const Payer& a, const Payer& b) { return a.calculateSum() > b.calculateSum(); });
}

void Payers::changePayer(int id) {
    for (auto& p : list_) {
        if (p.getId() == id) {
            p = Payer::createFactory(id);
            return;
        }
    }
    throw runtime_error("Абонент не найден");
}

void Payers::saveToCSV(const string& fname) const {
    ofstream out(fname);
    if (!out.is_open()) throw runtime_error(("Ошибка записи в " + fname).c_str());

    out << "ID,ФИО,Телефон,Тариф,Скидка,Минуты,День,Месяц,Год\n";
    for (const auto& p : list_) {
        out << p.getId() << "," << p.getName() << "," << p.getPhone() << "," << p.getTariff() << "," << p.getDiscount()
            << "," << p.getTimeMin() << "," << p.getDate().getDay() << "," << p.getDate().getMonth() << "," << p.getDate().getYear() << "\n";
    }
}

void Payers::loadFromCSV(const string& fname) {
    if (fname.empty()) throw runtime_error("CSV: пустое имя файла.");

    ifstream in(fname);
    if (!in.is_open()) throw runtime_error(("CSV: не удалось открыть файл " + fname + " для чтения.").c_str());

    string line;
    if (!getline(in, line)) throw runtime_error("CSV: файл пуст.");

    {
        istringstream iss(line);
        string token;
        if (!getline(iss, token, ',')) throw runtime_error("CSV: неверный заголовок.");
        if (token != "ID") throw runtime_error("CSV: неверный заголовок (ожидается ID).");
        // Проверки для остальных заголовков аналогично, но опускаем по примеру
    }

    list_.clear();
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Payer p;
        int id, discount, timeMin, d, m, y;
        double tariff;
        string name, phone;

        iss >> id;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после ID).");
        getline(iss, name, ',');
        getline(iss, phone, ',');
        iss >> tariff;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после тарифа).");
        iss >> discount;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после скидки).");
        iss >> timeMin;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после минут).");
        iss >> d;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после дня).");
        iss >> m;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный формат строки (после месяца).");
        iss >> y;
        checkInputFormat(iss);

        p.setId(id);
        p.setName(name);
        p.setPhone(phone);
        p.setTariff(tariff);
        p.setDiscount(discount);
        p.setTimeMin(timeMin);
        p.setDate(d, m, y);

        list_.push_back(p);
        nextId_ = max(nextId_, p.getId() + 1);
    }

    if (list_.empty()) throw runtime_error("CSV: в файле нет абонентов для загрузки.");
}