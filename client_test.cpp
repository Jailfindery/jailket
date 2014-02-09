#include <iostream>

#include "server_connection.h"
#include "inet_port.h"

using namespace std;
using namespace jailket;

int main()
{
    inet_port p("tcp", 8080);
    server_connection s("127.0.0.1", p);

    s.send("Hello, world!");
    string reply = s.recv();
    cout << reply << endl;

    s.disconnect();
}

