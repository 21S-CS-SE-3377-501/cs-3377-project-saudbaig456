//
// Created by erik on 2/2/21.
//
//extra imports
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#include "Part1SimpleFileModifier.h"
#include "FileModifyException.h"

using namespace std;

void Part1SimpleFileModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    //Fill this in and probably going to have to refactor into 2 separate files
    int fd = open(sourceFile, O_RDONLY, S_IRUSR);
    int numEntries = 0;
    //read the an integer from the beginning of the file seems to return the number of bytes it read
    int numRead = read(fd, &numEntries, sizeof(int));
    cout << "Number of entries: " << numEntries << endl;
    //take numEntries and read that many times
        //read a date/time
        time_t timestamp;
        read(fd, &timestamp, sizeof(time_t));
        cout << "Timestamp: " << timestamp << endl;
        //read an item ID
        int id = 0;
        read(fd, &id, sizeof(int));
        cout << "Item ID: " << id << endl;
        //read an item Name
        char* name = new char(50);
        read(fd, name, 50*sizeof(char));
        cout << "Item Name: " << *name << endl;
        //read an item Quantity
        int quantity;
        read(fd, &quantity, sizeof(int));
        cout << "Quantity: " << quantity << endl;
        //read an item Price
        float price;
        read(fd, &price, sizeof(float));
        cout << "Price: " << price << endl;
        delete name;
    close(fd);

}
