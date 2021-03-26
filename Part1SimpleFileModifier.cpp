//
// Created by erik on 2/2/21.
//

#include "FileReader.h"
#include "FileWriter.h"
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
    cout << "The entries before: " << endl;
    fileReader.printEntries();

    //add new entries
    const char* sobellName = "A Programming Guide to Linux Commands, Editors, and Shell Programming by Sobell";
    fileReader.makeEntry(1612195200, 4636152, sobellName, 70, 70.99);
    const char* apueName = "Advanced Programming in the UNIX Environment by Stevens and Rago";
    fileReader.makeEntry(1613412000, 6530927, apueName, 68, 89.99);
    cout << "The entries after: " << endl;
    fileReader.printEntries();
    FileWriter filewriter(destFile, fileReader.getEntries());
    filewriter.writeRecords();


}
