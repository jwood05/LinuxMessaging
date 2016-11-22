#ifndef RECEIVER_H
#define RECEIVER_H

//#include <iostream>
#include <sstream>
#include <string>
#include <netinet/in.h>

#include "Sender.h"

using namespace std;

class Receiver
{
    public:
        Receiver(string, int, int);
        void Listen();
        virtual ~Receiver();

    protected:

    private:
        void ParseCommand(string);
        string ip;
        int port, sock, oPort;
        struct sockaddr_in server;
};

#endif // RECEIVER_H
