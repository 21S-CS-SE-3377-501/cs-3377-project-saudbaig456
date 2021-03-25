//
// Created by saudbaig on 3/25/21.
//

#ifndef INC_21S_CS3377_PROJECT_FILEWRITER_H
#define INC_21S_CS3377_PROJECT_FILEWRITER_H
#include <cstdio>
#include <ctime>
#include "Util.h"
#include <vector>
class FileWriter {
public:
    FileWriter(const char *dest);
    void writeInt(int *buffer);
    void writeTime(time_t* buffer);
    void writeString(char* buffer);
    void writeFloat(float* buffer);
    ~FileWriter();

private:
    std::vector<EntryInfo> records;

};
#endif //PROJECTTEMPLATE_FILEWRITER_H
