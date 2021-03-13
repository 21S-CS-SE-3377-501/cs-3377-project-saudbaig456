//
// Created by Erik Peterson on 2/11/21.
//

#ifndef INC_21S_CS3377_PROJECT_PIPEMAKER_H
#define INC_21S_CS3377_PROJECT_PIPEMAKER_H


class PipeMaker {
public:
    PipeMaker();

    // Call when you're the parent process, to write to the child
    int setUpToWrite();

    // Call when you're the child process, to read from the parent
    int setUpToRead();
private:
    int pipeFDs[2];
};


#endif //INC_21S_CS3377_PROJECT_PIPEMAKER_H
