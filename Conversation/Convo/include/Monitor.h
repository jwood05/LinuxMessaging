#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
#include <string>
#include <thread>

#include "system_ping.h"

using namespace std;

class Monitor
{
    public:
        Monitor(string);
        void Maintain();
        virtual ~Monitor();

    protected:

    private:
        string ip;
};

#endif // MONITOR_H
