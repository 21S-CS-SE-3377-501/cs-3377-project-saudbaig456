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
#include <ctime>

FileReader::FileReader(const char *source) {
    FileReader::fd = open(source, O_RDONLY, S_IRUSR);
    readInt(&(FileReader::numEntries));
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
    read(fd, buffer, sizeof(float));
}

FileReader::~FileReader() {
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
