//
// Created by Erik Peterson on 2/10/21.
//

#include <iostream>
#include "Part3ThreadedModifier.h"
#include "FileModifyException.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <pthread.h>
#include "Util.h"
#include <vector>

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
   pthread_mutex_lock(&mutex);
   //create thread with threadEntry
   //make the thread an pass start function
   pthread_t outputThreadID;

   //figure out which arg to pass
   pthread_create(&outputThreadID, nullptr, threadEntry, this);

   //main thread waits on condition: unlocks the mutex while waiting
   pthread_cond_wait(&condition, &mutex);

    //set infoBetweenThreads to next entry
    FileReader fileReader(sourceFile);
    fileReader.populateEntries();
    //add new entries
    const char* sobellName = "A Programming Guide to Linux Commands, Editors, and Shell Programming by Sobell";
    fileReader.makeEntry(1612195200, 4636152, sobellName, 70, 70.99);
    const char* apueName = "Advanced Programming in the UNIX Environment by Stevens and Rago";
    fileReader.makeEntry(1613412000, 6530927, apueName, 68, 89.99);
    vector<EntryInfo> entries = fileReader.getEntries();

    //entry ready this will be a loop
    for(int i=0; i<entries.size(); i++) {
        cout << entries.at(i).itemName << endl;
        this->infoBetweenThreads = entries.at(i);
        pthread_cond_signal(&condition);
    }



    //unlock and rejoin
    cout << "Back to main thread " << endl;
    pthread_mutex_unlock(&mutex);
    pthread_join(outputThreadID, nullptr);

   //signal that we are ready for a read

}

// Use this as the starting point for the thread you create
void *Part3ThreadedModifier::threadEntry(void* arg) noexcept {
    //converts arg to pointer
    Part3ThreadedModifier* modifier = (Part3ThreadedModifier*) arg;
    try {
       modifier->outputThreadMethod();
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
    cout << "Locking NOW" << endl;
    pthread_mutex_lock(&mutex);
    //signal the condition
    cout << "Signaling NOW" << endl;
    pthread_cond_signal(&condition);
    //now wait on entryInfo condition
    FileWriter fileWriter(this->destFile);

    for(int i=0; i<2; i++) {
        pthread_cond_wait(&condition, &mutex);
        fileWriter.writeRecord(this->infoBetweenThreads);
    }
    //save entry and unlock

    cout << "Unlocked the mutex" << endl;
    pthread_mutex_unlock(&mutex);
    //write file

}

Part3ThreadedModifier::~Part3ThreadedModifier() noexcept {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

}
