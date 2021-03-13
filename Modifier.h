//
// Created by erik on 2/2/21.
//

#ifndef INC_21S_CS3377_PROJECT_MODIFIER_H
#define INC_21S_CS3377_PROJECT_MODIFIER_H

#include "Util.h"

class Modifier {
public:
    // Method for doing setup work
    virtual void doSetup(IOType ioType) = 0;
    virtual void modifyAndCopyFile(const char* sourceFile,
                                   const char* destFile) = 0;
};


#endif //INC_21S_CS3377_PROJECT_MODIFIER_H
