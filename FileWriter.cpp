//
// Created by saudbaig on 3/25/21.
//
#include "FileWriter.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include "Util.h"
#include "FileModifyException.h"
#include <cstring>

using namespace std;
FileWriter::FileWriter(int fd, vector<EntryInfo> records) {
    this->fd = fd;
    if(fd == -1) {
        cerr << "Can't open file for writing: " << strerror(errno) << endl;
        exit(1);
    }
    this->records = records;
    this->numEntries = records.size();
    writeInt(&(this->numEntries));
}

FileWriter::FileWriter(const char *dest, std::vector<EntryInfo> records) {
    this->fd = open(dest, O_WRONLY | O_CREAT, S_IRWXU);
    //error check
    if(fd == -1) {
        cerr << "Can't open file for writing: " << strerror(errno) << endl;
        exit(1);
    }
    this->records = records;
    this->numEntries = records.size();
    writeInt(&(this->numEntries));
}

void FileWriter::writeInt(int *buffer) {
    int bytes = write(this->fd, buffer, sizeof(int));
    handleError(bytes);
}

void FileWriter::writeTime(time_t *buffer) {
    int bytes = write(this->fd, buffer, sizeof(time_t));
    handleError(bytes);
}

void FileWriter::writeString(char *buffer) {
    int bytes = write(this->fd, buffer, 50*sizeof(char));
    handleError(bytes);
}

void FileWriter::writeFloat(float *buffer) {
    int bytes = write(this->fd, buffer, sizeof(float));
    handleError(bytes);
}

void FileWriter::writeRecords() {
    //write vector contents to the output file
    for(int i=0; i<records.size(); i++) {
        writeTime(&(records.at(i).timestamp));
        writeInt(&(records.at(i).itemID));
        writeString(records.at(i).itemName);
        writeInt(&(records.at(i).quantity));
        writeFloat(&(records.at(i).price));

    }
    close(this->fd);
}
void FileWriter::handleError(int bytes) {
    if(bytes == -1) {
        cerr << "Writing error: " << strerror(errno) << endl;
        exit(1);
    }
}



FileWriter::~FileWriter() {

}

