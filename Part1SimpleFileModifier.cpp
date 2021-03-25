//
// Created by erik on 2/2/21.
//

#include "FileReader.h"
#include "Part1SimpleFileModifier.h"
#include "FileModifyException.h"
#include <iostream>
#include <vector>
#include "Util.h"

using namespace std;

void Part1SimpleFileModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    FileReader fileReader(sourceFile);
    cout << fileReader.getNumEntries() << endl;
    fileReader.populateEntries();
    fileReader.printEntries();

    EntryInfo* ptr = fileReader.getEntries();
    cout << ptr[0].quantity;
    std::vector<EntryInfo> list;
    cout << "Made the vector";
    for(int i =0; i<fileReader.getNumEntries(); i++) {
        list.push_back(ptr[i]);
    }
    for(int i=0; i<list.size(); i++) {
        cout << list.at(i).quantity << ", ";
    }
}
