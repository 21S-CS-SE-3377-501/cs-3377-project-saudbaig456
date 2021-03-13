//
// Created by erik on 2/3/21.
//
#include "Util.h"
#include "FileModifyException.h"

#include <string>

using namespace std;

const char* Util::usage = "FileModifier { 1 | 2 {R|W} |3 | 4 {R|W} }\n";
const char* Util::inputFilename = "input";
const char* Util::outputFilename = "output";

ModifierType Util::toModifierType(int type) {
    switch(type) {
        case 1:
            return ModifierType::SIMPLE_MODIFIER;
        case 2:
            return ModifierType::MULTI_PROCESS_MODIFIER;
        case 3:
            return ModifierType::THREADED_MODIFIER;
        case 4:
            return ModifierType::IPC_MODIFIER;
        default:
            throw FileModifyException("Unknown modifier type (int) " + to_string(type));
    }
}

IOType Util::toIOType(int type) {
    switch(type) {
        case 1:
            return IOType::READ_AND_WRITE;
        case 2:
            return IOType::READ;
        case 3:
            return IOType::WRITE;
        default:
            throw FileModifyException("Unknown IO type (int) " + to_string(type));
    }
}
