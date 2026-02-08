#include "Requests.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>

Requests::Requests() {
    for (int i = 0; i < 15; ++i) {
        list_.push_back(Request::createFactory(nextId_++));
    }
}

void Requests::addRequest() {
    list_.push_back(Request::createFactory(nextId_++));
}

void Requests::deleteById(int id) {
    auto it = remove_if(list_.begin(), list_.end(), [id](const Request& r) { return r.getId() == id; });
    list_.erase(it, list_.end());
}

list<Request> Requests::selectByFlight(const string& flight) {
    list<Request> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [flight](const Request& r) {
        return r.getFlightNum() == flight;
        });
    return result;
}

list<Request> Requests::selectByDate(const Date& date) {
    list<Request> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [date](const Request& r) {
        return r.getDate() == date;
        });
    return result;
}

list<Request> Requests::selectByPassenger(const string& pass) {
    list<Request> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [pass](const Request& r) {
        return r.getPassenger() == pass;
        });
    return result;
}

void Requests::sortById() {
    list_.sort([](const Request& a, const Request& b) { return a.getId() < b.getId(); });
}

void Requests::sortByDate() {
    list_.sort([](const Request& a, const Request& b) { return a.getDate() < b.getDate(); });
}

void Requests::sortByDestination() {
    list_.sort([](const Request& a, const Request& b) { return a.getDestination() < b.getDestination(); });
}

void Requests::changeRequest(int id) {
    for (auto& r : list_) {
        if (r.getId() == id) {
            Request newR = Request::createFactory(id);
            r = newR;  // copy
            return;
        }
    }
    throw exception("Заявка не найдена");
}

void Requests::saveToBinaryFixed(const string& fname) const {
    ofstream out(fname, ios::binary | ios::trunc);
    if (!out.is_open()) throw exception(("Ошибка записи в " + fname).c_str());

    for (const auto& r : list_) {
        out.write(reinterpret_cast<const char*>(&r), sizeof(Request));
    }
}

void Requests::loadFromBinaryFixed(const string& fname) {
    ifstream in(fname, ios::binary);
    if (!in.is_open()) throw exception(("Ошибка открытия " + fname).c_str());

    list_.clear();
    Request r;
    while (in.read(reinterpret_cast<char*>(&r), sizeof(Request))) {
        list_.push_back(r);
        nextId_ = max(nextId_, r.getId() + 1);
    }
}

void Requests::swapFirstLastInFile(const string& fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f.is_open()) throw exception(("Ошибка открытия " + fname).c_str());

    f.seekg(0, ios::end);
    size_t fileSize = f.tellg();
    size_t recSize = sizeof(Request);
    if (fileSize < 2 * recSize) throw exception("Мало записей в файле");

    Request first, last;
    f.seekg(0);
    f.read(reinterpret_cast<char*>(&first), recSize);

    f.seekg(-static_cast<int>(recSize), ios::end);
    f.read(reinterpret_cast<char*>(&last), recSize);

    f.seekp(0);
    f.write(reinterpret_cast<const char*>(&last), recSize);

    f.seekp(-static_cast<int>(recSize), ios::end);
    f.write(reinterpret_cast<const char*>(&first), recSize);
}

void Requests::swapEarliestLatestInFile(const string& fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f.is_open()) throw exception(("Ошибка открытия " + fname).c_str());

    f.seekg(0, ios::end);
    size_t fileSize = f.tellg();
    size_t recSize = sizeof(Request);
    if (fileSize < 2 * recSize) throw exception("Мало записей в файле");

    size_t numRecs = fileSize / recSize;
    Date minDate; minDate.setDate(31, 12, 9999);
    Date maxDate; maxDate.setDate(1, 1, 0);
    size_t minPos = 0, maxPos = 0;

    for (size_t pos = 0; pos < numRecs; ++pos) {
        f.seekg(pos * recSize + offsetof(Request, date));
        Date d;
        f.read(reinterpret_cast<char*>(&d), sizeof(Date));
        if (d < minDate) { minDate = d; minPos = pos; }
        if (maxDate < d) { maxDate = d; maxPos = pos; }
    }

    if (minPos == maxPos) throw exception("Нет разных дат для swap");

    Request minR, maxR;
    f.seekg(minPos * recSize);
    f.read(reinterpret_cast<char*>(&minR), recSize);

    f.seekg(maxPos * recSize);
    f.read(reinterpret_cast<char*>(&maxR), recSize);

    f.seekp(minPos * recSize);
    f.write(reinterpret_cast<const char*>(&maxR), recSize);

    f.seekp(maxPos * recSize);
    f.write(reinterpret_cast<const char*>(&minR), recSize);
}