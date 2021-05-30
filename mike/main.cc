#include <iostream>
#include "reg.h"

#define QSIZE 256

using namespace std;

void menu() {
    cout << "(1) Добавить запись." << endl;
    cout << "(2) Сортировка по возрастанию." << endl;
    cout << "(3) Сортировка по убыванию." << endl;
    cout << "(4) Изменить запись." << endl;
    cout << "(5) Вывести все записи." << endl;
    cout << "(6) Удалить запись." << endl;
    cout << "(7) Удалить все записи." << endl;
    cout << "(8) Выход." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int point = 0;
    int id;
    reg db;

    while (point != 8) {
        cout << "Выберите пункт меню:" << endl;

        menu();

        point = reg::num(0, 8);

        switch (point) {
            case 1:
                system("clear");
                if (db.addRow()) {
                    cout << "Запись успешно добавлена." << endl;
                }
                break;
            case 2:
                system("clear");
                db.upsort();
                break;
            case 3:
                system("clear");
                db.downsort();
                break;
            case 4:
                system("clear");
                cout << "Введите номер записи, которую необходимо изменить:" << endl;
                id = reg::num(0, QSIZE);
                db.updateRow(id);
                cout << "Запись успешно обновлена." << endl;
                break;
            case 5:
                system("clear");
                db.showTickets(NULL);
                cout << endl;
                break;
            case 6:
                system("clear");
                cout << "Введите номер записи, которую необходимо изменить:" << endl;
                id = reg::num(0, QSIZE);

                if (db.dropRow(id)) {
                    cout << "Запись под номером " << id << " была удалена." << endl;
                }
                break;
            case 7:
                system("clear");
                db.emptyBase();
                cout << "Файл данных успешно очищщен." << endl;
                break;
            default:
                if (point != 8) {
                    cerr << "Неизвестный пункт меню." << endl;
                }
                break;
        }

    }

    return 0;
}

#pragma clang diagnostic pop
