//
// Created by Erik Peterson on 2/10/21.
//

#ifndef INC_21S_CS3377_PROJECT_PART3THREADEDMODIFIER_H
#define INC_21S_CS3377_PROJECT_PART3THREADEDMODIFIER_H


#include "Modifier.h"

class Part3ThreadedModifier : public Modifier {
public:
    void doSetup(IOType ioType) override;
    void modifyAndCopyFile(const char* sourceFile,
                           const char* destFile) override;
    ~Part3ThreadedModifier() noexcept;
private:
    static void* threadEntry(void* arg) noexcept;
    int numItems;
    void outputThreadMethod();
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    EntryInfo infoBetweenThreads;
    const char* destFile;

};


#endif //INC_21S_CS3377_PROJECT_PART3THREADEDMODIFIER_H
