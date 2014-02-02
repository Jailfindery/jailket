#include <iostream>

#include "client_connection.h"
#include "inet_port.h"
#include "server_socket.h"

using namespace std;
using namespace jailket;

int main()
{
    inet_port p("tcp", 8080);
    server_socket s(p);

    s.listen();
    client_connection c = s.accept();
    string mesg = c.recv();
    c.send("ACK");
    c.close();

    cout << mesg << endl;
}
