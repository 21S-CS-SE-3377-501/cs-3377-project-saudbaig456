//
// Created by saudbaig on 3/22/21.
//
//add minimal error handling to functions
#include "FileReader.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include "Util.h"
#include <ctime>
#include <vector>

using namespace std;

FileReader::FileReader(const char *source) {
    FileReader::fd = open(source, O_RDONLY, S_IRUSR);
    readInt(&(FileReader::numEntries));
    FileReader::entries = std::vector<EntryInfo>(numEntries);
    //alloc memory to array's structs' char pointers
    for(int i=0; i<numEntries; i++) {
        this->entries.at(i).itemName = new char[50];
    }
}

void FileReader::readInt(int* buffer) {
    read(FileReader::fd, buffer, sizeof(int));
}

void FileReader::readTime(time_t* buffer) {
    read(FileReader::fd, buffer, sizeof(time_t));
}

void FileReader::readString(char* buffer) {
    read(FileReader::fd, buffer, 50 * sizeof(char));
}

void FileReader::readFloat(float* buffer) {
    read(FileReader::fd, buffer, sizeof(float));
}

void FileReader::populateEntries() {
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

