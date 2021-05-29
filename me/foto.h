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

public:
    foto();
    void printAll();
    void writeTimestamp();
    void trimData();
    void addRow();

    static int getnumber(int min, int max);
    static string getname();
    static void printMenu();
};


#endif //METRICS_LAB_FOTO_H
