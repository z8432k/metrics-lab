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
    bool down = false;

    string inputTicket();

    void setDate();

    void showTickets(vector<string> *rows);

    void aroundData(function<void(ofstream &out)> &callback);

    static size_t split(const std::string &str, std::vector<std::string> &items, char sep);

    int findmax();

    int getPos(int id);

public:

    reg();

    void show();

    void writeTimestamp();

    void emptyBase();

    bool addTicket();

    void updateTicket(int id);

    bool drop(int id);

    void upsort();

    void downsort();

    void changeSortOrder();

    string searchTicket(int id);

    static int num(size_t min, size_t max);

    static string str();
};
