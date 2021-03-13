#include <iostream>
#include <unistd.h>
#include <cstring>

#include "Util.h"
#include "Modifier.h"
#include "FileModifierFactory.h"
#include "FileModifyException.h"

using namespace std;

//---------------------------------------------------------
// Arguments:
// ModifierType: 1-4, corresponds to the project parts
//      1. Simple modifier
//      2. Multiprocess modifier
//      3. Threaded modifier
//      4. IPC (socket) modifier
//
// IOType: required for modifier types 2 and 4, because
//         they use 2 processes (one to read and the other
//         to write). Not needed for modifier types 1 & 3
//
//         For parts 2 & 4, call the read version (2)
//         from CLion. Your code should call the write
//         (3) version for the 2nd process.
//--------------------------------------------------------
int main(int argc, char** argv) {
    // Delete the output file so we're starting fresh
    unlink(Util::outputFilename);

    if ( argc < 2) {
        cerr << "No type specified.\n" << Util::usage;
        exit(1);
    }

    ModifierType modifierType;

    // Turn argv[1] (first argument) into the proper modifier type
    try {
        modifierType = Util::toModifierType(stoi(argv[1]));
    } catch ( FileModifyException e) {
        cerr << "Unable to determine type of " << argv[1] << ": " << e.what() << "\n" << Util::usage;
        exit(1);
    } catch ( exception e) {
        cerr << "Is " << argv[1] << " an integer? Couldn't convert it to a ModifierType:\n" << Util::usage;
        exit(1);
    }

    // Get the IOType (if specified)
    IOType ioType = IOType::READ_AND_WRITE;
    if ( argc == 3) {
        try {
            ioType = Util::toIOType(stoi(argv[2]));
        } catch ( FileModifyException e) {
            cerr << "Unable to determine I/O type of " << argv[2] << ": " << e.what() << "\n" << Util::usage;
        } catch ( exception e) {
            cerr << "Is " << argv[2] << " an integer? Couldn't convert it to an IOType\n" << Util::usage;
        }
    }

    // Factory-build the modifier
    Modifier* modifier;
    try {
        modifier = FileModifierFactory::createModifier(modifierType, ioType, argc, argv);
    } catch(FileModifyException e) {
        cerr << "Error creating modifier object: " << e.what();
        exit(1);
    } catch ( exception e) {
        cerr << "Error creating modifier object: " << e.what();
        exit(1);
    }

    try {
        modifier->modifyAndCopyFile(Util::inputFilename, Util::outputFilename);
    } catch (FileModifyException e) {
        cerr << "Error modifying file: " << e.what();
        exit(1);
    } catch ( exception e) {
        cerr << "Error modifying file: " << e.what();
        exit(1);
    }

    // Exec ProjectChecker to do the checking for us
    // The #ifdef here is some trickery to launch the MacOS or Linux version
    // of the checker program based on your architecture

    int error = 0;
#ifdef __linux__
    error = execl("./ProjectCheckerLinux", "ProjectChecker", NULL);
#elif __APPLE__
    error = execl("./ProjectCheckerMac", "ProjectChecker", NULL);
#else
    cerr << "Unknown architecture!" << endl;
    exit(1);
#endif
    if ( error) {
        cerr << "Unable to start file checker!" << strerror(errno) << endl;
        exit(1);
    }
}
