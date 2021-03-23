//
// Created by erik on 2/2/21.
//

#include "FileReader.h"
#include "Part1SimpleFileModifier.h"
#include "FileModifyException.h"
#include <iostream>

using namespace std;

void Part1SimpleFileModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    FileReader fileReader(sourceFile);
    time_t t;
    fileReader.readTime(&t);
    cout << t << endl;
    int id;
    fileReader.readInt(&id);
    cout << id << endl;
    char* name = new char(50);
    fileReader.readString(name);
    cout << name << endl;
    int qty;
    fileReader.readInt(&qty);
    cout << qty << endl;
    float price;
    fileReader.readFloat(&price);
    cout << price << endl;
}
