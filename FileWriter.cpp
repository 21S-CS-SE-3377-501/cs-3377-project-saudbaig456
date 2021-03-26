//
// Created by saudbaig on 3/25/21.
//
#include "FileWriter.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include "Util.h"

FileWriter::FileWriter(const char *dest, std::vector<EntryInfo> records) {
    this->fd = open(dest, O_WRONLY | O_CREAT, S_IRWXU);
    this->records = records;
    this->numEntries = records.size();
    writeInt(&(this->numEntries));
}

void FileWriter::writeInt(int *buffer) {
    write(this->fd, buffer, sizeof(int));
}

void FileWriter::writeTime(time_t *buffer) {
    write(this->fd, buffer, sizeof(time_t));
}

void FileWriter::writeString(char *buffer) {
    write(this->fd, buffer, 50*sizeof(char));
}

void FileWriter::writeFloat(float *buffer) {
    write(this->fd, buffer, sizeof(float));
}

void FileWriter::writeRecords() {
    for(int i=0; i<records.size(); i++) {
        writeTime(&(records.at(i).timestamp));
        writeInt(&(records.at(i).itemID));
        writeString(records.at(i).itemName);
        writeInt(&(records.at(i).quantity));
        writeFloat(&(records.at(i).price));

    }
    close(this->fd);
}

FileWriter::~FileWriter() {

}
