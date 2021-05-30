#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

#define DATA "register.txt"
#define DATE "lastuse.txt"

class reg {
private:
    ifstream in;
    ofstream outData, out;
    vector<string> tickets;
    string buf;

    static string readRow();

    void setDate();
    void aroundData(function<void (ofstream &out)> &callback);

public:
    reg();

    void showTickets(vector<string> *rows);

    void writeTimestamp();

    void emptyBase();

    bool addRow();

    void updateRow(int id);

    bool dropRow(int id);

    void upsort();

    void downsort();

    static int num(size_t min, size_t max);

    static string str();
};
