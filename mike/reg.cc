#include "reg.h"
#include <algorithm>

reg::reg() : in(DATA), out(DATE) {
    if (!in.is_open() | !out.is_open()) {
        cerr << "Файл не может быть открыт." << endl;
    }

    while (getline(in, buf)) {
        tickets.push_back(buf);
    }

    setDate();

    in.close();
}

void reg::showTickets(vector<string> *r) {
    size_t cnt = 1;

    if (r==nullptr) {
        r = &tickets;
    }

    for (auto &item :  *r) {
        cout << cnt++ << "\t" << item << endl;
    }
}

void reg::emptyBase() {
    tickets.clear();

    function<void (ofstream &out)> lambda = [](ofstream &out) {
        1 + 1;
    };

    outData.open(DATA);

    if (!outData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    outData << "";

    outData.close();
}

bool reg::addRow() {
    string row = readRow();

    function<void (ofstream &out)> cb = [this, &row](ofstream &outD) -> void {
        tickets.push_back(row);
    };

    aroundData(cb);

    return true;
}

string reg::readRow() {
    string row;
    string manufacturer;
    string brand;
    int iso;

    cout << "Введите название производителя" << endl;
    manufacturer = str();

    cout << "Введите название бренда:" << endl;
    brand = str();

    cout << "Введите чувствительность:" << endl;
    iso = num(1, 12800);

    row = manufacturer + "\t" + brand + "\t" + to_string(iso);

    return row;
}

int reg::num(size_t min, size_t max) {
    int result;

    for (;;) {
        cin >> result;

        if (result > min && result <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            return result;
        } else {
            cerr << "Ошибка. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

void reg::setDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    out << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":"
        << ltm->tm_min << ":" << ltm->tm_sec << endl;

    out.close();
}

string reg::str() {
    while (true) {
        string str;
        getline(cin, str);

        if (str.length() >= 2) {
            return str;
        } else {
            cerr << "Название не болжно быть таким коротким." << endl;
        }
    }
}

void reg::updateRow(int id) {
    string row = readRow();

    outData.open(DATA);

    if (!outData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    if (tickets.size() > id) {
        tickets.at(id - 1) = row;
    } else {
        cerr << "Записи с указанным номером не существует" << endl;
    }

    for (auto &item : tickets) {
        outData << item << endl;
    }

    outData.close();
}

bool reg::dropRow(int id) {
    outData.open(DATA);

    if (!outData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }


    if (tickets.size() > id) {
        tickets.erase(tickets.begin() + (id - 1));
    } else {
        cerr << "Запись под указанным номером не существует." << endl;

        return false;
    }

    for (auto &item : tickets) {
        outData << item << endl;
    }

    outData.close();

    return true;
}

void reg::upsort() {
    vector<string> sorted = tickets;
    sort(sorted.begin(), sorted.end());

    showTickets(&sorted);
}

void reg::downsort() {
    vector<string> sorted = tickets;
    sort(sorted.begin(), sorted.end(), greater<>());

    showTickets(&sorted);
}

void reg::aroundData(function<void(ofstream &)> &callback) {
    outData.open(DATA);

    if (!outData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    callback(outData);

    for (auto &item : tickets) {
        outData << item << endl;
    }

    outData.close();
}

