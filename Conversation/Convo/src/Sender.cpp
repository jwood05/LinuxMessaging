#include "Sender.h"

extern bool survive;
extern clock_t timer;

Sender::Sender(string newIp, int newPort)
{
    //ctor
    ip = newIp;
    port = newPort;
}

void Sender::Talk()
{
    //sleep for 1 second to allow the other party's Receiver to initialize
    std::this_thread::sleep_for(std::chrono::seconds(5));

    //open up a socket for sending messages
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //parse out the other party's IP
    struct hostent *server_addr;
    struct in_addr parsedIp;
    if(!inet_aton(ip.c_str(), &parsedIp)) {
        cout << "Can't parse IP " << gethostbyaddr((const void*)&parsedIp, sizeof(parsedIp), AF_INET) << endl;
        survive = false;
        return;
    }

    //set up a hostentity for the other party's PC
    if((server_addr = gethostbyaddr((const void*)&parsedIp, sizeof(parsedIp), AF_INET)) == NULL) {
        cout << "Host Entity initialization failed." << endl;
        survive = false;
        return;
    }

    //copy the host entity's IP to be the Sender's IP
    bcopy((char*)server_addr->h_addr, (char*)&server.sin_addr.s_addr, server_addr->h_length);

    //set up the Sender information
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //connect the Sender to the Receiver's socket
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cout << "Connection failed. Retry your call later." << endl;
        survive = false;
        return;
    } else {
        cout << "Talking on port " << port << "..." << endl;
    }

    //loop to wait for messages to send
    while(survive) {
        //get input from cin
        string msg;
        std::getline(cin, msg);
        if(msg[0] == '/') {
            //this is a command
            ParseCommand(msg);
        } else {
            //this is a message
            SendMessage(msg);
        }
    }
    close(sock);
}

void Sender::ParseCommand(string msg)
{
    //check what the command is and act accordingly
    if(msg.compare("/quit") == 0) {
        cout << "You have disconnected this call." << endl;
        SendMessage(msg);
        survive = false;
    } else if(msg.compare("/ping") == 0) {
        timer = clock();
        SendMessage(msg);
    } else {
        cout << msg << " is not a valid command." << endl;
    }
}

void Sender::SendMessage(string msg)
{
    //send the message through the socket
    int n = write(sock, msg.c_str(), strlen(msg.c_str()));
}

/*this is a rehash of the Talk() void for sending one-off messages*/
void Sender::Ack(string msg)
{
    //open up a socket for sending messages
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //parse out the other party's IP
    struct hostent *server_addr;
    struct in_addr parsedIp;
    if(!inet_aton(ip.c_str(), &parsedIp)) {
        cout << "Can't parse IP" << endl;
        survive = false;
        return;
    }

    //set up a hostentity for the other party's PC
    if((server_addr = gethostbyaddr((const void*)&parsedIp, sizeof(parsedIp), AF_INET)) == NULL) {
        cout << "Host Entity initialization failed." << endl;
        survive = false;
        return;
    }

    //copy the host entity's IP to be the Sender's IP
    bcopy((char*)server_addr->h_addr, (char*)&server.sin_addr.s_addr, server_addr->h_length);

    //set up the Sender information
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //connect the Sender to the Receiver's socket
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
    }

    //send the message
    SendMessage(msg);
    close(sock);
}

Sender::~Sender()
{
    //dtor
}
