//
// Created by Erik Peterson on 2/10/21.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include "Part4SocketModifier.h"
#include "FileModifyException.h"
#include "FileWriter.h"
#include "FileReader.h"
#include <sys/wait.h>
#include "Util.h"
#include <sys/socket.h>
#include <arpa/inet.h>


Part4SocketModifier::~Part4SocketModifier() {
    // TODO: clean up anything needed
}

void Part4SocketModifier::doSetup(IOType ioType) {
    //parent is client
    //child is server
    this->ioType = ioType;
    if(ioType == IOType::WRITE) {
        //we are the child setup to listen
        //socket, bind, listen
        int server_fd, new_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);

        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            std::cout << "Socket failed" << std::endl;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(Util::portNumber);

        if (bind(server_fd, (struct sockaddr*) &address, sizeof(address))<0) {
            std::cerr << strerror(errno) << std::endl;
            std::cout << "Bind Failed" << std::endl;
        }

        if (listen(server_fd, 3) < 0) {
            std::cout << "Listen error" << std::endl;
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*) &addrlen)) <0) {
            std::cout << "Accept Error" << std::endl;
        }

        this->socketFd = new_socket;

        return;
    }


    pid_t pid = fork();

    //Handle child and parent processes
    if (pid < 0) {
        //fork failed
        std::cout << "Fork Failed" << std::endl;
    }
    else if(pid == 0) {
        //we are the child
        execl("./21S_CS3377_Project", "21S_CS3377_Project", "4", "3", nullptr);
    }
    else {
        //we are the parent
        //setup to write
        int fileDescriptor = 0;
        struct sockaddr_in serverAddress;
        if ((fileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) <0) {
            std::cout << "Socket creation error "<< std::endl;
        }
        //save this off to write to later
        this->socketFd = fileDescriptor;

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(Util::portNumber);

        if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <=0)
        {
            std::cout << "Invalid address" << std::endl;
        }

        int amountToWait = 1;
        while (connect(fileDescriptor, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) {
            if ( errno != ECONNREFUSED) {
                // Something unexpected happened
                std::cerr << strerror(errno) << std::endl;
                throw FileModifyException("Error connecting");
            }
            std::cout << "Not ready to connect yet..." << std::endl;

            // Exponential backoff
            sleep(amountToWait);
            amountToWait = amountToWait * 2;
        }
    }

}

void Part4SocketModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    if(this->ioType == IOType::READ) {
        //parent process here
        //read from file, write to socket
        FileReader reader(sourceFile);
        reader.populateEntries();
        const char* sobellName = "A Programming Guide to Linux Commands, Editors, and Shell Programming by Sobell";
        reader.makeEntry(1612195200, 4636152, sobellName, 70, 70.99);
        const char* apueName = "Advanced Programming in the UNIX Environment by Stevens and Rago";
        reader.makeEntry(1613412000, 6530927, apueName, 68, 89.99);

        //write entries to socket
        FileWriter writer(this->socketFd, reader.getEntries());
        writer.writeRecords();
        int temp = 0;
        wait(&temp);


    }
    else if(this->ioType == IOType::WRITE) {
        //child process here
        //read from socket to outfile
        FileReader reader(this->socketFd);
        reader.populateEntries();

        FileWriter writer(destFile, reader.getEntries());
        writer.writeRecords();
        exit(0);
    }
}

