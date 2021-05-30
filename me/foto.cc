#include "foto.h"

foto::foto(): inFile("data.txt"), outFile("mark.txt") {
    if (!inFile.is_open() | !outFile.is_open()) {
        cerr << "Файл не может быть открыт." << endl;
    }

    while (getline(inFile, buffer)) {
        rows.push_back(buffer);
    }

    inFile.close();
}

void foto::printAll() {
    size_t cnt = 1;

    for (auto &item :  rows) {
        cout << cnt++ << "\t" << item << endl;
    }
}

void foto::writeTimestamp() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    outFile << 1900 + ltm->tm_year <<"-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour <<":" << ltm->tm_min << ":"<<ltm->tm_sec <<endl;

    outFile.close();
}

void foto::trimData() {
    rows.clear();

    outFileData.open("data.txt");

    if (!outFileData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    outFileData << "";

    outFileData.close();
}

void foto::printMenu() {
    cout << "(1) Добавить запись." << endl;
    cout << "(2) Сортировка по возрастанию" << endl;
    cout << "(3) Сортировка по убыванию" << endl;
    cout << "(4) Изменить запись." << endl;
    cout << "(5) Вывести все записи." << endl;
    cout << "(6) Удалить запись" << endl;
    cout << "(7) Удалить все записи." << endl;
    cout << "(8) Выход" << endl;
}

void foto::addRow() {
    string row = readRow();

    outFileData.open("data.txt");

    if (!outFileData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    rows.push_back(row);

    for (auto &item : rows) {
        outFileData << item << endl;
    }

    outFileData.close();
}

string foto::readRow() {
    string row;
    string manufacturer;
    string brand;
    int iso;

    cout << "Введите название производителя" << endl;
    manufacturer = getname();

    cout << "Введите название бренда:" << endl;
    brand = getname();

    cout << "Введите чувствительность:" << endl;
    iso = getnumber(1, 12800);

    row = manufacturer + "\t" + brand + "\t" + to_string(iso);

    return row;
}

int foto::getnumber(int min, int max) {
    int result;

    for (;;) {
        cin >> result;

        if(result > min && result <= max) {
            cin.ignore( numeric_limits<streamsize>::max(), '\n');

            return result;
        }
        else {
            cerr << "Ошибка. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

string foto::getname() {
    for (;;) {
        string str;
        getline(cin, str);

        if (str.length() >= 2) {
            return str;
        }
        else {
            cerr << "Название не болжно быть таким коротким." << endl;
        }
    }
}

void foto::updateRow(int id) {
    string row = readRow();

    outFileData.open("data.txt");

    if (!outFileData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    if (rows.size() > id) {
        rows.at(id - 1) = row;
    }
    else {
        cerr << "аписи с указанным номером не существует" << endl;
    }

    for (auto &item : rows) {
        outFileData << item << endl;
    }

    outFileData.close();
}

void foto::dropRow(int id) {
    outFileData.open("data.txt");

    if (!outFileData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }


    if (rows.size() > id) {
        rows.erase(rows.begin() + (id - 1));
    }
    else {
        cerr << "Запись под указанным номером не существует." << endl;
    }

    for (auto &item : rows) {
        outFileData << item << endl;
    }

    outFileData.close();
}

