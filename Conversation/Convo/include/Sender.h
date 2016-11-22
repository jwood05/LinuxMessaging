#ifndef SENDER_H
#define SENDER_H

#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <unistd.h>

using namespace std;

class Sender
{
    public:
        Sender(string, int);
        void Ack(string);
        void Talk();
        virtual ~Sender();

    protected:

    private:
        void ParseCommand(string);
        void SendMessage(string);
        string ip;
        int port, sock;
        struct sockaddr_in server;
};

#endif // SENDER_H
