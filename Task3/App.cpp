#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Request>& lst, const string& title) const {
    cout << "     " << title << "\n"
        << "     +" << setfill('-') << setw(98) << "-" << "+"
        << setfill(' ') << "\n";

    int row = 1;
    for (const auto& r : lst) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | ID: " << setw(4) << r.id
            << " | �����: " << setw(10) << r.destination
            << " | ����: " << setw(12) << r.flightNum
            << " | ��������: " << setw(15) << r.passenger
            << " | ����: " << r.date.toString() << " |\n";
    }
    cout << "     +" << setfill('-') << setw(98) << "-" << "+"
        << setfill(' ') << "\n";
}

void App::doAddRequest() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ����������");

    requests_.addRequest();
    cout << "���������\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doDeleteById() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ��������");

    if (getRequests().empty()) throw exception("������ ����");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    int id = it->getId();
    requests_.deleteById(id);
    cout << color(errColor) << "������� ������ ID: " << id << color(mainColor) << "\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSelectByFlight() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ������");

    if (getRequests().empty()) throw exception("������ ����");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string flight = it->getFlightNum();
    cout << "����� �� �����: " << flight << "\n";
    auto res = requests_.selectByFlight(flight);
    printList(res, "����� �� �����");
}

void App::doSelectByDate() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ������");

    if (getRequests().empty()) throw exception("������ ����");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    Date date = it->getDate();
    cout << "����� �� ����: " << date.toString() << "\n";
    auto res = requests_.selectByDate(date);
    printList(res, "����� �� ����");
}

void App::doSelectByPassenger() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ������");

    if (getRequests().empty()) throw exception("������ ����");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string pass = it->getPassenger();
    cout << "����� �� ���������: " << pass << "\n";
    auto res = requests_.selectByPassenger(pass);
    printList(res, "����� �� ���������");
}

void App::doSortById() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ����������");

    requests_.sortById();
    cout << "����������� �� ID\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSortByDate() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ����������");

    requests_.sortByDate();
    cout << "����������� �� ����\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSortByDestination() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ����������");

    requests_.sortByDestination();
    cout << "����������� �� ������\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doChangeRequest() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ���������");

    if (getRequests().empty()) throw exception("������ ����");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    int id = it->id;
    requests_.changeRequest(id);
    cout << "�������� ID: " << id << "\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSaveToBinaryFixed() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ����������");

    requests_.saveToBinaryFixed(binFile_);
    cout << "���������\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doLoadFromBinaryFixed() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� ��������");

    requests_.loadFromBinaryFixed(binFile_);
    cout << "���������\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSwapFirstLastInFile() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� swap first/last");

    requests_.swapFirstLastInFile(binFile_);
    cout << "First/last swapped\n";

    cls();
    printList(getRequests(), "����������� ������");
}

void App::doSwapEarliestLatestInFile() {
    cls();
    printList(getRequests(), "������� ������");
    getKey("\n������� ��� swap earliest/latest");

    requests_.swapEarliestLatestInFile(binFile_);
    cout << "Earliest/latest swapped\n";

    cls();
    printList(getRequests(), "����������� ������");
}