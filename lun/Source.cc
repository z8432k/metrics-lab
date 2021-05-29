#include <iostream>
#include "theatre.h"
#include <regex>
#include <string>


using namespace std;


int is_menunumber()
{
    int choice;
    while (true)
    {
        cin >> choice;
        if(choice > 0 && choice <=9)
        {
            cin.ignore(32767, '\n');
            return choice;
        }
        else
        {
            cerr << "Введено неверное значение. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}
int is_number()
{
    unsigned int value;
    while (true)
    {
        cin >> value;
        if (value > 0 && value <= 9999999)
        {
            cin.ignore(32767, '\n');
            return value;
        }
        else
        {
            cerr << "Введено неверное значение или превышен лимит 9999999. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}
string nameshow()
{
    while (true)
    {
        string namesh;
        getline(cin, namesh);
        wchar_t c = namesh[0];
        if (c >= 'А' && c <= 'Я' || c >= 'а' && c <= 'я')
        {
            return namesh;
        }
        else
        {
            cerr << "Название представления должно начинаться с буквы (кириллицы)." << endl;
        }
    }
}
string datashow()
{
    while (true)
    {
        string datashow;
        getline(cin, datashow);
        regex reg("^([0]?[1-9]|[1|2][0-9]|[3][0|1])-([0]?[1-9]|[1][0-2])-[0-9]{4}");
        if (regex_match(datashow, reg))
        {

            return datashow;
        }
        else
        {
            cerr << "Введено неверное значение даты. Формат даты дд-мм-гг." <<
                 endl;
        }
    }
}
string timeshow()
{
    while (true)
    {
        string timeshow;
        getline(cin, timeshow);
        regex reg("^([0]?[0-9]|[1][0-9]|[2][0-3]):[0-5]{1}[0-9]{1}");
        if (regex_match(timeshow, reg))
        {
            return timeshow;
        }
        else
        {
            cerr << "Введено неверное значение времени. Формат времени час:мин."
                 << endl;
        }
    }
}
string Ending(int buf)
{
    if (buf % 10 < 4 && buf % 10 > 1)
    {
        return "билета";
    }
    else if (buf % 10 == 1)
    {
        return "билет";
    }
    else
    {
        return "билетов";
    }
}
int main()
{
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);
    int var;
    theatre a;
    a.outdatatime(); // вывод даты последнего входа в программу
    do
    {
        cout << "Введите номер пункта меню: " << endl;
        a.menu();
        var = is_menunumber();
        switch (var)
        {
            case 1: // вывести все билеты
            {
                system("clear");
                a.showallfile();
                cout << endl;

                break;
            }
            case 2: // добавление билета
            {
                system("clear");
                string ticketinfo;
                string name;
                string data;
                string time;
                string countticket;
                int buf;
                cout << "Введите название представления:" << endl;
                name = nameshow();
                cout << "Введите дату проведения представления:" << endl;
                data = datashow();
                cout << "Введите время представления:" << endl;
                time = timeshow();
                cout << "Введите количество свободных билетов:" << endl;
                buf = is_number();
                countticket = to_string(buf) + " " + Ending(buf);
                ticketinfo = name + " \t" + data + "\t" + time + "\t" + countticket;
                a.addshow(ticketinfo);
                cout << "Представление добавлено." << endl;
                break;
            }
            case 3: // изменение информации о билете
            {
                system("clear");
                int ticketpos;
                string ticketinfo;
                string name;
                string data;
                string time;
                string countticket;
                int buf;
                cout << "Введите номер представления, который необходимо изменить: "
                     << endl;
                ticketpos = is_number();
                cout << "Введите название представления:" << endl;
                name = nameshow();
                cout << "Введите дату проведения представления:" << endl;
                data = datashow();
                cout << "Введите время представления:" << endl;
                time = timeshow();
                cout << "Введите количество свободных билетов:" << endl;
                buf = is_number();
                countticket = to_string(buf) + " " + Ending(buf);
                ticketinfo = name + "\t" + data + "\t" + time + "\t" + countticket;
                a.edititm(ticketpos, ticketinfo);
                cout << "Информация о представлении изменена." << endl << endl;
                break;
            }
            case 4: // сортировка по алфавиту
            {
                system("clear");
                a.sortfile();
                cout << "Файл отсортирован по алфавиту." << endl;
                break;
            }
            case 5: //обратная сортировка алфавита
            {


                system("clear");
                a.sortfilereverse();
                cout << "Файл отсортирован по алфавиту (обратная)." << endl;
                break;
            }
            case 6: // поиск билета
            {
                system("clear");
                string elem;
                cout << "Введите что-нибудь для поиска: " << endl;
                cin >> elem;
                cout << "Результаты поиска по запросу (" << elem << "):" << endl;
                a.finditm(elem);
                break;
            }
            case 7: // удаление определённого билета
            {
                system("clear");
                int deltickpos;
                cout << "Введите позицию представления, который необходимо удалить:"<< endl;
                deltickpos = is_number();
                a.delticket(deltickpos);
                cout << "Представление под номером " << deltickpos << " было удалено."<<endl;
                break;
            }
            case 8://очистка файла
            {
                system("clear");
                a.deleteall();
                cout << "Поздравляю, теперь тебе всё восстанавливать вручную. Файл пуст, наслаждайся." << endl;
                break;
            }
            default:
                break;
        }
    } while (var != 9);

    // system("pause");

    return 0;
}
