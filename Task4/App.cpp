#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Payer>& lst, const string& title) const {
    // determine available width from console
    const int consoleWidth = static_cast<int>(getConsoleSize().X);
    const int totalWidth = max(40, min(consoleWidth - 4, 120));

    cout << "     " << title << "\n";
    cout << "     +" << string(totalWidth, '-') << "+\n";

    auto fit = [](const string& s, int maxLen) {
        if (maxLen <= 0) return string();
        if ((int)s.size() <= maxLen) return s;
        if (maxLen <= 3) return string(maxLen, '.');
        return s.substr(0, maxLen - 3) + "...";
    };

    int row = 1;
    const int innerWidth = totalWidth - 2; // padding
    for (const auto& p : lst) {
        // line 1: compact id and name
        string idPart = "ID:" + to_string(p.getId());
        string namePart = " Name: " + fit(p.getName(), innerWidth - (int)idPart.size());
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ') << " ";
        cout << idPart << namePart << "\n";

        // line 2: phone, tariff, discount, minutes
        ostringstream l2;
        l2 << " Phone:" << fit(p.getPhone(), 12)
           << "  Tariff:" << fixed << setprecision(2) << p.getTariff()
           << "  Disc:" << p.getDiscount()
           << "  Min:" << p.getTimeMin();
        cout << "      " << fit(l2.str(), innerWidth) << "\n";

        // line 3: date and sum
        ostringstream l3;
        l3 << " Date:" << p.getDate().toString() << "  Sum:" << fixed << setprecision(2) << p.calculateSum();
        cout << "      " << fit(l3.str(), innerWidth) << "\n";
    }

    cout << "     +" << string(totalWidth, '-') << "+\n";
}

void App::doAddPayer() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ����������");

    payers_.addPayer();
    cout << "���������\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doDeleteById() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ��������");

    if (payers_.getList().empty()) throw exception("������ ����");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.deleteById(id);
    cout << color(errColor) << "������ ������� ID: " << id << color(mainColor) << "\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doSelectByTariff() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ������");

    if (payers_.getList().empty()) throw exception("������ ����");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    double tariff = it->getTariff();
    cout << "����� �� ������: " << tariff << "\n";
    auto res = payers_.selectByTariff(tariff);
    printList(res, "����� �� ������");
}

void App::doSelectByDiscount() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ������");

    if (payers_.getList().empty()) throw exception("������ ����");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int discount = it->getDiscount();
    cout << "����� �� ������: " << discount << "\n";
    auto res = payers_.selectByDiscount(discount);
    printList(res, "����� �� ������");
}

void App::doSelectBySumRange() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ������");

    if (payers_.getList().empty()) throw exception("������ ����");

    double low = getRand(10.0, 100.0);
    double high = low + getRand(50.0, 200.0);
    cout << "����� �� ����� � ���������: " << low << " - " << high << "\n";
    auto res = payers_.selectBySumRange(low, high);
    printList(res, "����� �� ����� (������������� �� ��������)");
}

void App::doSortById() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ����������");

    payers_.sortById();
    cout << "����������� �� ID\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doSortByName() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ����������");

    payers_.sortByName();
    cout << "����������� �� ���\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doSortBySumDescending() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ����������");

    payers_.sortBySumDescending();
    cout << "����������� �� �������� �����\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doChangePayer() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ���������");

    if (payers_.getList().empty()) throw exception("������ ����");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.changePayer(id);
    cout << "������� ID: " << id << "\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doSaveToCSV() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ����������");

    payers_.saveToCSV(csvFile_);
    cout << "���������\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}

void App::doLoadFromCSV() {
    cls();
    printList(payers_.getList(), "������� ������");
    getKey("\n������� ��� ��������");

    payers_.loadFromCSV(csvFile_);
    cout << "���������\n";

    cls();
    printList(payers_.getList(), "����������� ������");
}