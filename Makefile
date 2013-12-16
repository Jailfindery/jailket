JAILKET_OBJECTS= obj/client_connection.o obj/client_socket.o obj/inet_port.o \
    obj/jailket_except.o obj/server_socket.o

default: jailket

# Meta builds
jailket: bin/jailket.so

# Shared objects
bin/jailket.so: $(JAILKET_OBJECTS)
	g++ $(JAILKET_OBJECTS) -o bin/libjailket.so -shared

# Objects
obj/client_connection.o: client_connection.cpp
	g++ -c client_connection.cpp -o obj/client_connection.o -fPIC
obj/client_socket.o: client_socket.cpp
	g++ -c client_socket.cpp -o obj/client_socket.o -fPIC
obj/inet_port.o: inet_port.cpp
	g++ -c inet_port.cpp -o obj/inet_port.o -fPIC -std=c++11
obj/jailket_except.o: jailket_except.cpp
	g++ -c jailket_except.cpp -o obj/jailket_except.o -fPIC
obj/server_socket.o: server_socket.cpp
	g++ -c server_socket.cpp -o obj/server_socket.o -fPIC

# Clean
clean:
	-rm -f obj/*.o
	-rm -f bin/*.so

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

