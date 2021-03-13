//
// Created by erik on 2/2/21.
//

#ifndef INC_21S_CS3377_PROJECT_FILEMODIFIERFACTORY_H
#define INC_21S_CS3377_PROJECT_FILEMODIFIERFACTORY_H


#include "Modifier.h"
#include "Util.h"

class FileModifierFactory {
public:
    static Modifier* createModifier(ModifierType type, IOType ioType, int argc, char** argv);
};


#endif //INC_21S_CS3377_PROJECT_FILEMODIFIERFACTORY_H
