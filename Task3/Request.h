#pragma once
#include "pch.h"
#include "Date.h"

struct Request : public Object {
    int id;
    char destination[31];  // fixed for binary
    char flightNum[16];
    char passenger[31];
    Date date;

    static Request createFactory(int id);  // фабрика для создания/изменения

    int getId() const { return id; }
    string getDestination() const { return string(destination); }
    string getFlightNum() const { return string(flightNum); }
    string getPassenger() const { return string(passenger); }
    Date getDate() const { return date; }

    string toString() const override;  // const
};