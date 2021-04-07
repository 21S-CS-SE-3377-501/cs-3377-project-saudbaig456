//
// Created by saudbaig on 3/22/21.
//
//add minimal error handling to functions
#include "FileReader.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "Util.h"
#include <ctime>
#include <vector>
#include "FileModifyException.h"
#include <cstring>

using namespace std;

FileReader::FileReader(int fd) {
    this->fd = fd;
    //error check
    if(fd == -1) {
        cerr << "Can't open file for reading: " << strerror(errno) << endl;
        exit(1);
    }
    readInt(&(FileReader::numEntries));
    FileReader::entries = std::vector<EntryInfo>(numEntries);

    //alloc memory to vector's structs' char pointers
    for(int i=0; i<numEntries; i++) {
        this->entries.at(i).itemName = new char[50];
    }
}

FileReader::FileReader(const char *source) {
    FileReader::fd = open(source, O_RDONLY, S_IRUSR);
    //error check
    if(fd == -1) {
        cerr << "Can't open file for reading: " << strerror(errno) << endl;
        exit(1);
    }
    readInt(&(FileReader::numEntries));
    FileReader::entries = std::vector<EntryInfo>(numEntries);

    //alloc memory to vector's structs' char pointers
    for(int i=0; i<numEntries; i++) {
        this->entries.at(i).itemName = new char[50];
    }
}

void FileReader::readInt(int* buffer) {
    int bytes = read(FileReader::fd, buffer, sizeof(int));
    handleError(bytes);
}

void FileReader::readTime(time_t* buffer) {
    int bytes = read(FileReader::fd, buffer, sizeof(time_t));
    handleError(bytes);
}

void FileReader::readString(char* buffer) {
    int bytes = read(FileReader::fd, buffer, 50 * sizeof(char));
    handleError(bytes);
}

void FileReader::readFloat(float* buffer) {
    int bytes = read(FileReader::fd, buffer, sizeof(float));
    handleError(bytes);
}

void FileReader::handleError(int bytes) {
    if(bytes == -1) {
        cerr << "Reading error: " << strerror(errno) << endl;
        exit(1);
    }
}

void FileReader::populateEntries() {
    //read in entries from the file
    for(int i =0; i <entries.size(); i++) {
        this->readTime(&(this->entries.at(i).timestamp));
        this->readInt(&(this->entries.at(i).itemID));
        this->readString(this->entries.at(i).itemName);
        this->readInt(&(this->entries.at(i).quantity));
        this->readFloat(&(this->entries.at(i).price));
    }
    close(FileReader::fd);
}

void FileReader::printEntries() {
    for(int i =0; i<entries.size(); i++) {
        cout << "Time: " << this->entries.at(i).timestamp;
        cout << ", ID: " << this->entries.at(i).itemID;
        cout << ", Name: " << this->entries.at(i).itemName;
        cout << ", Qty: " << this->entries.at(i).quantity;
        cout << ", Price: " << this->entries.at(i).price << endl;
    }
}

void FileReader::makeEntry(time_t time, int id, const char* name, int qty, float price) {
    EntryInfo entry {
        time,
        id,
        new char[50],
        qty,
        price
    };
    //deep copy the string ptr
    for(int i=0; i<49; i++) {
        entry.itemName[i] = name[i];
    }
    entries.push_back(entry);
    numEntries++;
}

FileReader::~FileReader() {
    for(int i=0; i<entries.size(); i++) {
        delete (this->entries.at(i).itemName);
    }
}

int FileReader::getFd() const {
    return fd;
}

void FileReader::setFd(int fd) {
    FileReader::fd = fd;
}

int FileReader::getNumEntries() const {
    return numEntries;
}

void FileReader::setNumEntries(int numEntries) {
    FileReader::numEntries = numEntries;
}

const vector<EntryInfo> &FileReader::getEntries() const {
    return entries;
}

