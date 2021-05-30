#ifndef METRICS_LAB_FOTO_H
#define METRICS_LAB_FOTO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class foto {
private:
    ifstream inFile;
    ofstream outFileData;
    ofstream outFile;
    vector<string> rows;
    string buffer;

    static string readRow();
    bool isDuplicate(string &entry);

public:
    foto();
    void printAll(vector<string> *rows = nullptr);
    void writeTimestamp();
    void trimData();
    bool addRow();
    void updateRow(int id);
    bool dropRow(int id);
    void ascSort();
    void descSort();

    static int getnumber(int min, int max);
    static string getname();
    static void printMenu();
};


#endif //METRICS_LAB_FOTO_H
