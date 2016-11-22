#include <time.h>
#include <iostream>
#include <pthread.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Monitor.h"
#include "Sender.h"
#include "Receiver.h"

using namespace std;

struct threadData {
    int threadId;
    string ip;
    int port;
    int oPort;
};

bool survive;
clock_t timer;

void *startMonitor(void*);
void *startSender(void*);
void *startReceiver(void*);

int main(int argc, char *argv[])
{
    survive = true;

    //parsing the arguments
    int ipLength = strlen(argv[1]);
    char *tempIpA = (char*)malloc(sizeof(char) * (ipLength + 1));
    char *tempIpB = (char*)malloc(sizeof(char) * (ipLength + 1));
    char *tempIpC = (char*)malloc(sizeof(char) * (ipLength + 1));
    strcpy(tempIpA, argv[1]);
    strcpy(tempIpB, argv[1]);
    strcpy(tempIpC, argv[1]);
    tempIpA[ipLength] = '\0';
    tempIpB[ipLength] = '\0';
    tempIpC[ipLength] = '\0';
    string myIpA = (string)tempIpA;
    string myIpB = (string)tempIpB;
    string myIpC = (string)tempIpC;

    int portLength = strlen(argv[2]);
    char *tempPortA = (char*) malloc(sizeof(char) * (portLength + 1));
    char *tempPortB = (char*) malloc(sizeof(char) * (portLength + 1));
    char *tempPortC = (char*) malloc(sizeof(char) * (portLength + 1));
    strcpy(tempPortA, argv[2]);
    strcpy(tempPortB, argv[2]);
    strcpy(tempPortC, argv[3]);
    tempPortA[portLength] = '\0';
    tempPortB[portLength] = '\0';
    tempPortC[portLength] = '\0';
    int myPortA = atoi(tempPortA);
    int myPortB = atoi(tempPortB);
    int myPortC = atoi(tempPortC);


    //create 3 threads
    pthread_t threads[3];

    //set up each thread as a monitor, sender, and receiver, respectively
    struct threadData monitorThread;
    monitorThread.threadId = 0;
    monitorThread.ip = myIpA;
    monitorThread.port = myPortA;
    struct threadData senderThread;
    senderThread.threadId = 1;
    senderThread.ip = myIpB;
    senderThread.port = myPortB;
    struct threadData receiverThread;
    receiverThread.threadId = 2;
    receiverThread.ip = myIpC;
    receiverThread.port = myPortC;
    receiverThread.oPort = myPortB;

    //use the threads to start each of the processes
    int newMonitor = pthread_create(&threads[0], NULL, startMonitor, (void *)&monitorThread);
    int newSender = pthread_create(&threads[1], NULL, startSender, (void *)&senderThread);
    int newReceiver = pthread_create(&threads[2], NULL, startReceiver, (void *)&receiverThread);

    /*void* res;
    int s = pthread_join(newMonitor, &res);
    s = pthread_join(newReceiver, &res);
    s = pthread_join(newSender, &res);*/

    pthread_exit(NULL);
}

void *startMonitor(void *threadArg)
{
    //start a new connection monitor
    //declaring a pointer to a threadData struct that will parse the data
    struct threadData *myData;

    //pointing the threadData pointer to our parameter
    myData = (struct threadData*) threadArg;

    //create a new Monitor process
    Monitor myMonitor(myData->ip);
    myMonitor.Maintain();

    pthread_exit(NULL);
}

void *startSender(void *threadArg)
{
    //start a new sender process
    //declaring a pointer to a threadData struct that will parse the data
    struct threadData *myData;

    //pointing the threadData pointer to our parameter
    myData = (struct threadData*) threadArg;

    Sender mySender(myData->ip, myData->port);
    mySender.Talk();

    pthread_exit(NULL);
}

void *startReceiver(void *threadArg)
{
    //start a new receiver process
    //declaring a pointer to a threadData struct that will parse the data
    struct threadData *myData;

    //pointing the threadData pointer to our parameter
    myData = (struct threadData*) threadArg;

    Receiver myReceiver(myData->ip, myData->port, myData->oPort);
    myReceiver.Listen();

    pthread_exit(NULL);
}
