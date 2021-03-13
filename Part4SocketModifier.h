//
// Created by Erik Peterson on 2/10/21.
//

#ifndef INC_21S_CS3377_PROJECT_PART4SOCKETMODIFIER_H
#define INC_21S_CS3377_PROJECT_PART4SOCKETMODIFIER_H


#include "Modifier.h"

class Part4SocketModifier : public Modifier {
public:
    ~Part4SocketModifier();
    void doSetup(IOType ioType) override;
    void modifyAndCopyFile(const char* sourceFile,
                           const char* destFile) override;
private:
};


#endif //INC_21S_CS3377_PROJECT_PART4SOCKETMODIFIER_H
