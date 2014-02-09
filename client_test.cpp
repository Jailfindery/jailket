#include <iostream>

#include "inet_port.h"
#include "jailket_except.h"
#include "server_connection.h"

using namespace std;
using namespace jailket;

int main()
{
    try
    {
        inet_port p("tcp", 8080);
        server_connection s("127.0.0.1", p);

        s.send("Hello, world!");
        string reply = s.recv();
        cout << reply << endl;

        s.disconnect();
    }
    catch(jailket_invalid_argument& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch(jailket_error& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
}

