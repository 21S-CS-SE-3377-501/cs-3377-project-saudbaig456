//
// Created by erik on 2/2/21.
//

#include "FileReader.h"
#include "Part1SimpleFileModifier.h"
#include "FileModifyException.h"
#include <iostream>
#include <vector>
#include "Util.h"
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void Part1SimpleFileModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    FileReader fileReader(sourceFile);
    cout << fileReader.getNumEntries() << endl;
    fileReader.populateEntries();
    fileReader.printEntries();

    EntryInfo* ptr = fileReader.getEntries();

    std::vector<EntryInfo> list;
    cout << "Made the vector" << endl;

    for(int i =0; i<fileReader.getNumEntries(); i++) {
        list.push_back(ptr[i]);
    }
    //char sobellName[6] = {'S','o','b','e','l','l'};
    const char* sobellName = "A Programming Guide to Linux Commands, Editors, and Shell Programming by Sobell ";
    EntryInfo sobell = {
            1612195200,
            4636152,
            (char*) sobellName,     //work around be casting it to charPtr
            70,
            70.99
    };
    const char* apueName = "Advanced Programming in the UNIX Environment by Stevens and Rago";
    EntryInfo apue = {
            1613412000,
            6530927,
            (char*) apueName,     //work around be casting it to charPtr
            68,
            89.99
    };
    list.push_back(sobell);
    list.push_back(apue);

    for(int i=0; i<list.size(); i++) {
        cout << list.at(i).itemName << endl;
    }

    int writeFd = open(destFile, O_WRONLY | O_CREAT, S_IRWXU);
    close(writeFd);
}
