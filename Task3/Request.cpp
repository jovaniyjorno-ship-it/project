#include "Request.h"
#include "Utils.h"

Request Request::createFactory(int id) {
    Request r;
    r.id = id;
    string dest = "Город" + to_string(getRand(1, 15));
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";
    string pass = "Пассажир" + to_string(getRand(1, 30)) + " И.И.";
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));

    strncpy(r.destination, dest.c_str(), 30); r.destination[30] = '\0';
    strncpy(r.flightNum, flight.c_str(), 15); r.flightNum[15] = '\0';
    strncpy(r.passenger, pass.c_str(), 30); r.passenger[30] = '\0';
    r.date = d;
    return r;
}

string Request::toString() const {
    ostringstream oss;
    oss << "ID: " << id << ", Пункт: " << destination << ", Рейс: " << flightNum
        << ", Пассажир: " << passenger << ", Дата: " << date.toString();
    return oss.str();
}