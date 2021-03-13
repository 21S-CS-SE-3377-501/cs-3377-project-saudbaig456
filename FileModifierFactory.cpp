//
// Created by erik on 2/2/21.
//

#include <string>
#include <sstream>
#include "FileModifierFactory.h"
#include "Part1SimpleFileModifier.h"
#include "FileModifyException.h"
#include "Part2MultiProcessModifier.h"
#include "Part3ThreadedModifier.h"
#include "Part4SocketModifier.h"

using namespace std;

// Create the proper modifier based on which part of the project you're doing
Modifier* FileModifierFactory::createModifier(ModifierType type, IOType ioType, int argc, char** argv) {
    Modifier* modifier = nullptr;
    switch(type) {
        case ModifierType::SIMPLE_MODIFIER:
            if ( ioType != IOType::READ_AND_WRITE) {
                throw FileModifyException("Simple file modifier must be R/W");
            }
            modifier = new Part1SimpleFileModifier();
            break;
        case ModifierType::MULTI_PROCESS_MODIFIER:
            if ( ioType == IOType::READ_AND_WRITE) {
                throw FileModifyException("Multi-process modifier must be read or write");
            }
            modifier = new Part2MultiProcessModifier();
            break;
        case ModifierType::THREADED_MODIFIER:
            if ( ioType != IOType::READ_AND_WRITE) {
                throw FileModifyException("Threaded file modifier must be R/W");
            }
            modifier = new Part3ThreadedModifier();
            break;
        case ModifierType::IPC_MODIFIER:
            if ( ioType == IOType::READ_AND_WRITE) {
                throw FileModifyException("IPC modifier must be read or write");
            }
            modifier = new Part4SocketModifier();
            break;
        default:
            throw FileModifyException("Unknown modifier " + to_string(static_cast<int>(type)) + Util::usage);
    }

    modifier->doSetup(ioType);
    return modifier;
}
