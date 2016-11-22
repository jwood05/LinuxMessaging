#include "Receiver.h"

extern bool survive;
extern clock_t timer;

Receiver::Receiver(string newIp, int newPort, int otherPort)
{
    //ctor
    ip = newIp;
    port = newPort;
    oPort = otherPort;
}

void Receiver::Listen()
{
    //open up a socket for receiving messages
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //bind to a port to listen for messages from the other party
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if(bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        cout << "Connection failed. Retry your call later." << endl;
        survive = false;
        return;
    } else {
        cout << "Listening on port " << port << "..." << endl;
    }

    //char[] reads messages in, msg displays them simply
    char buffer[256];
    string msg;

    //listen to the port we're bound to
    listen(sock, 2);

    //set up a new socket that accepts the incoming connection we listened for
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newSock = accept(sock, (struct sockaddr*)&cli_addr, &clilen);

    //loop until the conversation is over
    while(survive) {

        //read the received data into the buffer; ignore the int (result) value
        int n = read(newSock, buffer, 256);

        //see if the message is a command and parse/display appropriately
        msg = buffer;
        if(msg[0] == '/') {
            ParseCommand(msg);
        } else {
            cout << "> " << msg << endl;
        }

        //clear the buffer to eliminate extra characters in case of a multi-line message
        bzero(buffer, 256);
    }

    //close both sockets so there's not a "busy signal" afterward
    close(newSock);
    close(sock);
}

void Receiver::ParseCommand(string msg)
{
    //check what the command is and act accordingly
    if(msg.compare("/quit") == 0) {
        cout << "The other party has disconnected this call." << endl;
        survive = false;
        exit(0);
    } else if(msg.compare("/ping") == 0) {
        Sender tempSender(ip, oPort);
        tempSender.Ack("/pong");
    } else if(msg.compare("/pong") == 0) {
        cout << "Time: " << (double)(clock() - timer) << endl;
    }
}

Receiver::~Receiver()
{
    //dtor
}
