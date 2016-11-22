#ifndef SYSTEM_PING_H
#define SYSTEM_PING_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cerrno>
#include <cstring>

using namespace std;

class system_ping
{
    public:
        int test_connection (std::string, bool); //, int max_attempts, bool check_eth_port = false, int eth_port_number = 0);
    private:
        int ping_ip_address(std::string); //, int max_attempts, std::string& details);
};

#endif
