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

    pid_t pid = fork();

    //Handle child and parent processes
    if (pid < 0) {
        //fork failed
        cout << "Fork Failed" << endl;
    }
    else if(pid == 0) {
        //we are the child
        this->pipeFd = filePipe.setUpToRead();
        execl("./21S_CS3377_Project", "21S_CS3377_Project", "2", "3", nullptr);
    }
    else {
        //we are the parent
        this->pipeFd = filePipe.setUpToWrite();
    }

        //setup to write in the parent (gets back fd)
        //execl for the child

    //figure out if we are child or parent

}

void Part2MultiProcessModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    if(this->ioType == IOType::READ) {
        //parent process here
        //read from file to pipe
        FileReader reader(sourceFile);
        reader.populateEntries();
        const char* sobellName = "A Programming Guide to Linux Commands, Editors, and Shell Programming by Sobell";
        reader.makeEntry(1612195200, 4636152, sobellName, 70, 70.99);
        const char* apueName = "Advanced Programming in the UNIX Environment by Stevens and Rago";
        reader.makeEntry(1613412000, 6530927, apueName, 68, 89.99);

        //write entries to pipe
        FileWriter writer(this->pipeFd, reader.getEntries());
        writer.writeRecords();
        int temp = 0;
        wait(&temp);


    }
    else if(this->ioType == IOType::WRITE) {
        //child process here
        //read from pipe to outfile
        FileReader reader(this->pipeFd);
        reader.populateEntries();

        FileWriter writer(destFile, reader.getEntries());
        writer.writeRecords();
        exit(0);
    }
}
