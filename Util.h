//
// Created by erik on 2/2/21.
//

#ifndef INC_21S_CS3377_PROJECT_UTIL_H
#define INC_21S_CS3377_PROJECT_UTIL_H


#include <ctime>

struct EntryInfo {
    time_t timestamp;
    int itemID;
    char* itemName;
    int quantity;
    float price;
};

enum class ModifierType {
    // Part 1
    SIMPLE_MODIFIER = 1,
    // Part 2
    MULTI_PROCESS_MODIFIER,
    // Part 3
    THREADED_MODIFIER,
    // Part 4
    IPC_MODIFIER
};

/**
 * This enum says whether the FileModifier will read, write, or both
 * Parts 1 and 3 are READ_AND_WRITE (single process), whereas parts 2 and 4
 * are in two parts (the initial process getting READ_AND_WRITE, and you giving
 * the 2nd process the proper code for its role)
 */
enum class IOType : unsigned int {
    READ_AND_WRITE = 1,
    READ,
    WRITE
};

class Util {
public:
    const static char* usage;
    const static char* inputFilename;
    const static char* outputFilename;
    const static int portNumber = 12345;

    static ModifierType toModifierType(int type);
    static IOType toIOType(int type);

};


#endif //INC_21S_CS3377_PROJECT_UTIL_H
