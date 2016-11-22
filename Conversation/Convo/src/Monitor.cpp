#include "Monitor.h"

extern bool survive;

Monitor::Monitor(string newIp)
{
    //ctor
    ip = newIp;
}

void Monitor::Maintain()
{
    system_ping connTest;
    while(survive) {
        if(connTest.test_connection(ip, false) != 0) {
            cout << "Connection has been lost. Application run ended." << endl;
            survive = false;
            //return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    pthread_exit(NULL);
}

Monitor::~Monitor()
{
    //dtor
}
