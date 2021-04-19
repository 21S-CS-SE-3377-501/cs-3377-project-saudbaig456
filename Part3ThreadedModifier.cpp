//
// Created by Erik Peterson on 2/10/21.
//

#include <iostream>
#include "Part3ThreadedModifier.h"
#include "FileModifyException.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <pthread.h>

using namespace std;

void Part3ThreadedModifier::doSetup(IOType ioType) {
    if(ioType != IOType::READ_AND_WRITE) {
        throw FileModifyException("IOType must be R+W");
    }
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condition, nullptr);
}

void Part3ThreadedModifier::modifyAndCopyFile(const char *sourceFile, const char *destFile) {
   this->destFile = destFile;

   //Read the data and pass to write thread
   cout << "Reading input" << endl;
   pthread_mutex_lock(&mutex);
   cout << "Creating thread" << endl;
   //create thread with threadEntry
   //make the thread an pass start function
   pthread_t outputThreadID;
   pthread_create(&outputThreadID, nullptr, Part3ThreadedModifier::threadEntry, nullptr);

   //main thread waits on condition: unlocks the mutex while waiting
   //pthread_cond_wait(&condition, &mutex);

   //set infoBetweenThreads to next entry

   //singal that we are ready for a read

}

// Use this as the starting point for the thread you create
void *Part3ThreadedModifier::threadEntry(void* arg) noexcept {
    //converts arg to pointer
    //Part3ThreadedModifier* modifier = (Part3ThreadedModifier*) arg;
    try{
       // modifier->outputThreadMethod();
    } catch (FileModifyException e) {
        cerr << "Receiving thread failed: " << e.what() << endl;
        exit(1);
    } catch (exception e) {
        cerr << "Receiving thread failed" << e.what() << endl;
        exit(1);
    } catch (...) {
        cerr << "Unknown error in receiving thread" << endl;
        exit(1);
    }
    return nullptr;
}

void Part3ThreadedModifier::outputThreadMethod() {
    //lock the mutex here
    //pthread_mutex_lock(&mutex);
    //signal the condition
    //pthread_cond_signal(&condition);
    //now wait on entryInfo condition
    //pthread_cond_wait(&condition, &mutex);

}

Part3ThreadedModifier::~Part3ThreadedModifier() noexcept {
    // TODO: clean up your condition and mutex
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

}
