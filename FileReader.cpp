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

using namespace std;

FileReader::FileReader(const char *source) {
    FileReader::fd = open(source, O_RDONLY, S_IRUSR);
    readInt(&(FileReader::numEntries));
    FileReader::entries = new EntryInfo[numEntries];
//    for(int i=0; i<numEntries; i++) {
//        entries[0].itemName = new char(50);
//    }
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
    for(int i =0; i <this->numEntries; i++) {
        this->readTime(&(this->entries[i].timestamp));
        this->readInt(&(this->entries[i].itemID));
        this->readString(this->entries[i].itemName);
        this->readInt(&(this->entries[i].quantity));
        this->readFloat(&(this->entries[i].price));
    }
}

void FileReader::printEntries() {
    for(int i =0; i< this->numEntries; i++) {
        cout << "Time: " << this->entries[i].timestamp;
        cout << ", ID: " << this->entries[i].itemID;
        cout << ", Name: " << this->entries[i].itemName;
        cout << ", Qty: " << this->entries[i].quantity;
        cout << ", Price: " << this->entries[i].price << endl;
    }
}

FileReader::~FileReader() {
    for(int i=0; i<this->numEntries; i++) {
        //delete (this->entries[i].itemName);
    }
    delete (this->entries[0].itemName);
    delete (this->entries[1].itemName);

    delete[] FileReader::entries;
    close(FileReader::fd);
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
