JAILKET_OBJECTS= obj/client_connection.o obj/server_connection.o obj/inet_port.o \
    obj/jailket_except.o obj/server.o

default: jailket

# Meta builds
jailket: bin/jailket.so
test: bin/client_test bin/server_test

# Shared objects
bin/jailket.so: $(JAILKET_OBJECTS)
	g++ $(JAILKET_OBJECTS) -o bin/libjailket.so -shared

# Binaries
bin/client_test: $(JAILKET_OBJECTS) client_test.cpp
	g++ client_test.cpp $(JAILKET_OBJECTS) -o bin/client_test
bin/server_test: $(JAILKET_OBJECTS) server_test.cpp
	g++ server_test.cpp $(JAILKET_OBJECTS) -o bin/server_test

# Objects
obj/client_connection.o: client_connection.cpp
	g++ -c client_connection.cpp -o obj/client_connection.o -fPIC
obj/server_connection.o: server_connection.cpp
	g++ -c server_connection.cpp -o obj/server_connection.o -fPIC
obj/inet_port.o: inet_port.cpp
	g++ -c inet_port.cpp -o obj/inet_port.o -fPIC -std=c++11
obj/jailket_except.o: jailket_except.cpp
	g++ -c jailket_except.cpp -o obj/jailket_except.o -fPIC
obj/server.o: server.cpp
	g++ -c server.cpp -o obj/server.o -fPIC

# Clean
clean:
	-rm -f obj/*
	-rm -f bin/*

# Installations - requires root privledges
install: jailket
	cp bin/libjailket.so /usr/local/lib/libjailket.so
	-mkdir /usr/local/include/jailket
	cp *.h /usr/local/include/jailket/

# Uninstallations - requires root privledges
uninstall:
	-rm -f /usr/local/lib/libjailket.so
	-rm -f /usr/local/include/jailket/*.h
	-rmdir /usr/local/include/jailket

