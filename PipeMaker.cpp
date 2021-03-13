//
// Created by Erik Peterson on 2/11/21.
//

#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <string>
#include "PipeMaker.h"
#include "FileModifyException.h"

using namespace std;

PipeMaker::PipeMaker() {
    int rc = pipe(pipeFDs);
    if ( rc < 0) {
        string errorString = "Unable to create pipe: ";
        errorString.append(strerror(errno));
        throw FileModifyException(errorString);
    }
}

int PipeMaker::setUpToWrite() {
    // Close of fd[0] since we'll be writing, not reading
    // DO NOT dup the write file descriptor as that would mess up writing other things...
    close(pipeFDs[0]);
    return pipeFDs[1];
}

int PipeMaker::setUpToRead() {
    // Close of fd[1] since we'll be reading, not writing
    close(pipeFDs[1]);
    int usedFD = pipeFDs[0];
    int rc = dup2(usedFD, STDIN_FILENO);
    if ( rc < 0) {
        string errorString = "Unable to dup read pipe: ";
        errorString.append(strerror(errno));
        throw FileModifyException(errorString);
    }
    return usedFD;
}
