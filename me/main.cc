#include <iostream>
#include "foto.h"

using namespace std;

int getnumber(int min = 0, int max = INT32_MAX) {
    int result;

    for (;;) {
        cin >> result;

        if(result > min && result <= max) {
            cin.ignore( numeric_limits<streamsize>::max(), '\n');

            return result;
        }
        else {
            cerr << L"Ошибка. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int menu_choice;
    foto f;

    f.writeTimestamp();

    cout << "Выберите пункт меню" << endl;

    foto::printMenu();

    menu_choice = getnumber(0, 8);

    int id;
    switch (menu_choice) {
        case 1:
            system("clear");
            f.addRow();
            cout << "Запись успешно добавлена." << endl;
            break;
        case 2:
            system("clear");
            break;
        case 3:
            system("clear");
            break;
        case 4:
            system("clear");
            cout << "Введите номер записи, которую необходимо изменить:" << endl;
            id = getnumber();
            f.updateRow(id);
            cout << "Запись успешно обновлена." << endl;
            break;
        case 5:
            system("clear");
            f.printAll();
            cout << endl;
            break;
        case 6:
            system("clear");
            cout << "Введите номер записи, которую необходимо изменить:"<< endl;
            id = getnumber();
            f.dropRow(id);
            cout << "Запись под номером " << id << " была удалена."<<endl;
            break;
        case 7:
            system("clear");
            f.trimData();
            cout << "Файл данных успешно очищщен." << endl;
            break;
        case 8:
            system("clear");
            break;
        default:
            break;

    }

    return 0;
}
