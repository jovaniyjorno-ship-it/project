#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Payer>& lst, const string& title) const {
    cout << "     " << title << "\n"
        << "     +" << setfill('-') << setw(90) << "-" << "+"
        << setfill(' ') << "\n";

    int row = 1;
    for (const auto& p : lst) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | ID: " << setw(4) << p.getId()
            << " | ФИО: " << setw(15) << p.getName()
            << " | Телефон: " << setw(10) << p.getPhone()
            << " | Тариф: " << fixed << setprecision(2) << setw(5) << p.getTariff()
            << " | Скидка: " << setw(3) << p.getDiscount()
            << " | Минуты: " << setw(5) << p.getTimeMin()
            << " | Дата: " << p.getDate().toString() << " | Сумма: " << fixed << setprecision(2) << p.calculateSum() << " |\n";
    }
    cout << "     +" << setfill('-') << setw(90) << "-" << "+"
        << setfill(' ') << "\n";
}

void App::doAddPayer() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для добавления");

    payers_.addPayer();
    cout << "Добавлено\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doDeleteById() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для удаления");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.deleteById(id);
    cout << color(errColor) << "Удален абонент ID: " << id << color(mainColor) << "\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doSelectByTariff() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    double tariff = it->getTariff();
    cout << "Отбор по тарифу: " << tariff << "\n";
    auto res = payers_.selectByTariff(tariff);
    printList(res, "Отбор по тарифу");
}

void App::doSelectByDiscount() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int discount = it->getDiscount();
    cout << "Отбор по скидке: " << discount << "\n";
    auto res = payers_.selectByDiscount(discount);
    printList(res, "Отбор по скидке");
}

void App::doSelectBySumRange() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для отбора");

    if (payers_.getList().empty()) throw exception("Список пуст");

    double low = getRand(10.0, 100.0);
    double high = low + getRand(50.0, 200.0);
    cout << "Отбор по сумме в диапазоне: " << low << " - " << high << "\n";
    auto res = payers_.selectBySumRange(low, high);
    printList(res, "Отбор по сумме (отсортировано по телефону)");
}

void App::doSortById() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для сортировки");

    payers_.sortById();
    cout << "Сортировано по ID\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doSortByName() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для сортировки");

    payers_.sortByName();
    cout << "Сортировано по ФИО\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doSortBySumDescending() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для сортировки");

    payers_.sortBySumDescending();
    cout << "Сортировано по убыванию суммы\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doChangePayer() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для изменения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.changePayer(id);
    cout << "Изменен ID: " << id << "\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doSaveToCSV() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для сохранения");

    payers_.saveToCSV(csvFile_);
    cout << "Сохранено\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}

void App::doLoadFromCSV() {
    cls();
    printList(payers_.getList(), "Текущий список");
    getKey("\nНажмите для загрузки");

    payers_.loadFromCSV(csvFile_);
    cout << "Загружено\n";

    cls();
    printList(payers_.getList(), "Обновленный список");
}