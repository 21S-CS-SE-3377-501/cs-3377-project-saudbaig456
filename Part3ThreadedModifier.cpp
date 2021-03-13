//
// Created by Erik Peterson on 2/10/21.
//

#include <iostream>
#include "Part3ThreadedModifier.h"
#include "FileModifyException.h"

using namespace std;

void Part3ThreadedModifier::doSetup(IOType ioType) {
    // TODO: fill in
}

void Part3ThreadedModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
    // TODO: fill in
}

// Use this as the starting point for the thread you create
void *Part3ThreadedModifier::threadEntry(void* arg) noexcept{
    return nullptr;
}

Part3ThreadedModifier::~Part3ThreadedModifier() noexcept {
    // TODO: clean up your condition and mutex
}
