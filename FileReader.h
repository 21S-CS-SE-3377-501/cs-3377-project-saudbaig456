//
// Created by saudbaig on 3/22/21.
//
#ifndef INC_21S_CS3377_PROJECT_FILEREADER_H
#define INC_21S_CS3377_PROJECT_FILEREADER_H
#include <cstdio>
#include <ctime>
#include "Util.h"
#include <vector>
class FileReader {

public:
    FileReader(const char *source);
    void readInt(int* buffer);
    void readTime(time_t* buffer);
    void readString(char* buffer);
    void readFloat(float* buffer);
    int getFd() const;
    void setFd(int fd);
    int getNumEntries() const;
    void setNumEntries(int numEntries);
    void populateEntries();
    void printEntries();
    //function to add new entry to backing array
    void makeEntry(time_t time, int id, const char* name, int qty, float price);
    ~FileReader();

private:
    int fd;
    int numEntries;
public:
    const std::vector<EntryInfo> &getEntries() const;

private:
    std::vector<EntryInfo> entries;
};
#endif //PROJECTTEMPLATE_FILEREADER_H
