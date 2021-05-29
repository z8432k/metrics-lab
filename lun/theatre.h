#ifndef METRICS_LAB_THEATRE_H
#define METRICS_LAB_THEATRE_H

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>





using namespace std;
class theatre
{
private:
    ifstream inFile; //переменная для чтения из файла
    ofstream outFileticket;
    ofstream outFile; //
    vector<string> vec;
    string buff;
public:
    theatre();
    void showallfile(); //показать все записи в файле
    void outdatatime(); //вывод в файл времени запуска приложения
    void sortfile(); // сортировка по алфавиту
    void sortfilereverse(); // обратная сортировка
    void delticket(int a); // удалить определённый билет
    void finditm(string itm); // найти билет
    void edititm(int ticketpos,string ticketinfo); //изменение билета
    void deleteall();
    void addshow(string ti);
    void menu(); //вывод меню
};

#endif //METRICS_LAB_THEATRE_H
