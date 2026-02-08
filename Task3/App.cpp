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
            << " | Пункт: " << setw(10) << r.destination
            << " | Рейс: " << setw(12) << r.flightNum
            << " | Пассажир: " << setw(15) << r.passenger
            << " | Дата: " << r.date.toString() << " |\n";
    }
    cout << "     +" << setfill('-') << setw(98) << "-" << "+"
        << setfill(' ') << "\n";
}

void App::doAddRequest() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для добавления");

    requests_.addRequest();
    cout << "Добавлено\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doDeleteById() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для удаления");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    int id = it->id;
    requests_.deleteById(id);
    cout << color(errColor) << "Удалена заявка ID: " << id << color(mainColor) << "\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSelectByFlight() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    string flight = it->flightNum;
    cout << "Отбор по рейсу: " << flight << "\n";
    auto res = requests_.selectByFlight(flight);
    printList(res, "Отбор по рейсу");
}

void App::doSelectByDate() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    Date date = it->date;
    cout << "Отбор по дате: " << date.toString() << "\n";
    auto res = requests_.selectByDate(date);
    printList(res, "Отбор по дате");
}

void App::doSelectByPassenger() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    string pass = it->passenger;
    cout << "Отбор по пассажиру: " << pass << "\n";
    auto res = requests_.selectByPassenger(pass);
    printList(res, "Отбор по пассажиру");
}

void App::doSortById() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для сортировки");

    requests_.sortById();
    cout << "Сортировано по ID\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSortByDate() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для сортировки");

    requests_.sortByDate();
    cout << "Сортировано по дате\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSortByDestination() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для сортировки");

    requests_.sortByDestination();
    cout << "Сортировано по пункту\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doChangeRequest() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для изменения");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    int id = it->id;
    requests_.changeRequest(id);
    cout << "Изменено ID: " << id << "\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSaveToBinaryFixed() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для сохранения");

    requests_.saveToBinaryFixed(binFile_);
    cout << "Сохранено\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doLoadFromBinaryFixed() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для загрузки");

    requests_.loadFromBinaryFixed(binFile_);
    cout << "Загружено\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSwapFirstLastInFile() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для swap first/last");

    requests_.swapFirstLastInFile(binFile_);
    cout << "First/last swapped\n";

    cls();
    printList(getRequests(), "Обновленный список");
}

void App::doSwapEarliestLatestInFile() {
    cls();
    printList(getRequests(), "Текущий список");
    getKey("\nНажмите для swap earliest/latest");

    requests_.swapEarliestLatestInFile(binFile_);
    cout << "Earliest/latest swapped\n";

    cls();
    printList(getRequests(), "Обновленный список");
}