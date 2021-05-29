#include "theatre.h"

theatre::theatre() : inFile("Tickets.txt"), outFile("Data.txt")
{
    if (!inFile.is_open() | !outFile.is_open())
    {
        cerr << "Файл не может быть открыт.\n";
    }
    while (getline(inFile,buff))
    {
        vec.push_back(buff);
    }
    inFile.close();
}

void theatre::showallfile()
{
    int count = 1;
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << count << " " << *it << endl;
        count++;
    }
}
void theatre::outdatatime()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    outFile << "Дата последнего входа: ";
    outFile << 1900 + ltm->tm_year <<"-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday <<
            " "
            << ltm->tm_hour <<":" << ltm->tm_min << ":"<<ltm->tm_sec <<endl;
    outFile.close();
}
void theatre::sortfile()
{
    outFileticket.open("Tickets.txt");
    if (!outFileticket.is_open())
    {
        cerr << "Файл не может быть открыт";
    }
    sort(vec.begin(),vec.end());
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl;
    }
    outFileticket.close();
}
void theatre::sortfilereverse()
{
    outFileticket.open("Tickets.txt"); //открываем файл
    if (!outFileticket.is_open())
    {
        cerr << "Файл не может быть открыт";
    }
    sort(vec.begin(), vec.end(), [](string a, string b) {return a > b;}); // сортируем
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl; // перезаписываем в файл отсортированный вектор
    }
    outFileticket.close();
}
void theatre::delticket(int a)
{
    outFileticket.open("Tickets.txt");
    if (!outFileticket.is_open())

    {
        cerr << "Файл не может быть открыт";
    }
    auto iterator = vec.begin(); //указатель на первый элемент
    if (vec.size() > a)
    {
        vec.erase(iterator + (a - 1));
    }
    else
    {
        cerr << "Билета под таким номером не существует." << endl;
    }
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl;
    }
    outFileticket.close();
}
void theatre::finditm(string itm)
{
    vector<string>::iterator it = vec.begin();
    while (it != vec.end())
    {
        string cur_str = *it;
        int index = cur_str.find(itm);
        if (index != string::npos)
        {
            cout << *it << endl;
        }
        it++;
    }
}
void theatre::edititm(int ticketpos,string ticketinfo)
{
    outFileticket.open("Tickets.txt");
    if (!outFileticket.is_open())
    {
        cerr << "Файл не может быть открыт";
    }
    if (vec.size() > ticketpos)
    {
        vec.at(ticketpos - 1) = ticketinfo;
    }
    else
    {
        cerr << "Представления под таким номером не существует!" << endl;
    }
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl;
    }
    outFileticket.close();
}
void theatre::deleteall()
{
    vec.clear();

    outFileticket.open("Tickets.txt"); //открываем файл
    if (!outFileticket.is_open())
    {
        cerr << "Файл не может быть открыт";
    }
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl; // перезаписываем в файл отсортированный вектор
    }
    outFileticket.close();
}
void theatre::addshow(string ti)
{
    outFileticket.open("Tickets.txt"); //открываем файл
    if (!outFileticket.is_open())
    {
        cerr << "Файл не может быть открыт";
    }
    vec.push_back(ti);
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        outFileticket << *it << endl; // перезаписываем в файл отсортированный вектор
    }
    outFileticket.close();
}
void theatre::menu()
{
    cout << "1.Показать все представления." << endl;
    cout << "2.Добавить представление." << endl;
    cout << "3.Изменить информацию о представлении." << endl;
    cout << "4.Сортировка по алфавиту." << endl;
    cout << "5.Обратная сортировка по алфавиту." << endl;
    cout << "6.Поиск." << endl;
    cout << "7.Удалить представление." << endl;
    cout << "8.Удалить все представления." << endl;
    cout << "9.Выход." << endl;
}

