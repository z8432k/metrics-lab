#include <iostream>
#include "reg.h"

#define QSIZE 256

using namespace std;

void menu() {
    cout << "1) Распечатать записи в очереди" << endl;
    cout << "2) Встать в очередь" << endl;
    cout << "3) Изменить запись в очереди" << endl;
    cout << "4) Удалить запись из очереди" << endl;
    cout << "5) Очистить очередь" << endl;
    cout << "6) Поиск по номеру в очереди" << endl;
    cout << "7) Изменить порядок сортировки" << endl;
    cout << "8) Выход" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int point = 0;
    int id;
    string result;
    reg db;

    while (point != 8) {
        cout << "Выберите пункт меню:" << endl;

        menu();

        point = reg::num(0, 8);

        switch (point) {
            case 1:
                system("clear");
                db.show();
                cout << endl;
                break;
            case 2:
                system("clear");
                if (db.addTicket()) {
                    cout << "Запись успешно добавлена." << endl;
                }
                break;
            case 3:
                system("clear");
                cout << "Введите номер записи, которую необходимо изменить:" << endl;
                id = reg::num(0, QSIZE);
                db.updateTicket(id);
                cout << "Запись успешно обновлена." << endl;
                break;
            case 4:
                system("clear");
                cout << "Введите номер записи, которую необходимо изменить:" << endl;
                id = reg::num(0, QSIZE);

                if (db.drop(id)) {
                    cout << "Запись под номером " << id << " была удалена." << endl;
                }
                break;
            case 5:
                system("clear");
                db.emptyBase();
                cout << "Файл данных успешно очищщен." << endl;
                break;
            case 6:
                system("clear");
                id = reg::num(0, QSIZE);
                cout << "Введите номер в очереди" << endl;
                result = db.searchTicket(id);
                cout << result << endl;
                break;
            case 7:
                system("clear");
                db.changeSortOrder();
                cout << "Порядок сортировки изменён" << endl;
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
