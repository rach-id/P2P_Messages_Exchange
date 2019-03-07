INCLUDEPATHS= -I "." -I "protobuf/" -I "Listener/" -I "Sender/" 

CC = g++ -std=c++11

Server: Server.o msg.pb.o Listener.o Sender.o
	$(CC) Server.o msg.pb.o Listener.o Sender.o -o Server -lzmq -pthread -lprotobuf $(INCLUDEPATHS)
	
Server.o: Server.cpp zhelpers.o
	$(CC) -c Server.cpp -lzmq -pthread $(INCLUDEPATHS)
	
Listener.o: Listener/Listener.h Listener/Listener.cpp
	$(CC) -c Listener/Listener.h Listener/Listener.cpp -lzmq \
	$(INCLUDEPATHS)
	
Sender.o: Sender/Sender.h Sender/Sender.cpp
	$(CC) -c Sender/Sender.h Sender/Sender.cpp -lzmq \
	$(INCLUDEPATHS)
	
zhelpers.o: zhelpers.hpp
	$(CC) -c zhelpers.hpp -lzmq

msg.pb.o: protobuf/msg.pb.h protobuf/msg.pb.cc
	g++ -c protobuf/msg.pb.h protobuf/msg.pb.cc -lprotobuf
	
clean:
	rm -rf *.o *.gch */*.gch */*.o

cleanall:
	rm -rf *.o *.gch */*.gch */*.o Server
