//
// Created by Erik Peterson on 2/10/21.
//

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include "Part2MultiProcessModifier.h"
#include "PipeMaker.h"
#include "FileModifyException.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Util.h"

using namespace std;

void Part2MultiProcessModifier::doSetup(IOType ioType) {
    this->ioType = ioType;
    if(ioType == IOType::WRITE) {
        //we are the child nothing to do here
        return;
    }
    //make the pipe
    PipeMaker filePipe;

    pid_t pid;
    pid = fork();

    //Handle child and parent processes
    if (pid < 0) {
        //fork failed
        cout << "Fork Failed" << endl;
    }
    else if(pid == 0) {
        //we are the child
        int fd = filePipe.setUpToRead();
        execl("./21S_CS3377_Project", "21S_CS3377_Project", "2", "3", nullptr);
    }
    else {
        //we are the parent
        int fd = filePipe.setUpToWrite();
    }

        //setup to write in the parent (gets back fd)
        //execl for the child

    //figure out if we are child or parent

}

void Part2MultiProcessModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    if(this->ioType == IOType::READ) {
        //parent process here
        //read from file to pipe
        cout << "I am the parent" << endl;
        int temp = 0;
        wait(&temp);

    }
    else if(this->ioType == IOType::WRITE) {
        //child process here
        //read from pipe to outfile
        cout << "I am the child" << endl;
        exit(0);
    }
}
