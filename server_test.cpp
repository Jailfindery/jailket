#include <iostream>

#include "jailket.h"

using namespace std;
using namespace jailket;

int main()
{
    try
    {
        inet_port p("tcp", 8080);
        server s(p);

        s.listen();
        client_connection c = s.accept();
        string mesg = c.recv();
        c.send("ACK");
        c.disconnect();

        cout << mesg << endl;
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

