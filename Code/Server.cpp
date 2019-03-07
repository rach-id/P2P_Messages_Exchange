#include <zmq.hpp>
#include <string>
#include <iostream>
#include "zhelpers.hpp"
#include <thread>
#include <vector>
#include "protobuf/msg.pb.h"
#include "Listener/Listener.h"
#include "Sender/Sender.h"

using namespace std;

/* The server Code */
void printData(std::vector <std::string> data);

std::vector <std::string> data(1,"Genesis"); // The data

struct args {
	void* context;
	std::vector <std::string> data;
	int id;
};

int main () {
    zmq::context_t context1(1); //  For publishing the answer to all the connected nodes
	zmq::context_t context2(1); // for receiving updates published by other serves
   
   /* struct args *arguments = (struct args *)malloc(sizeof(struct args));
			
   arguments->context = (void*) context1;
   arguments->data = data;
   arguments->id = 0;
   */
   
   Listener listener(&context2, &data);
   Sender sender(&context1);
   
   	thread ls(listener);
   	thread sd(sender, 0);
   	
   	while(1){
   		printData(data);
   		sleep(20);
   	}
   	
   	
   	/*
	while(1) {
		
		sender.publish(3);
		
		sleep(1);
		/*
		
		if (subscriber_work(&context2, data)) {
			cout << "in While" << endl;
			
			
			pthread_t publisher;
			pthread_create(&publisher, NULL, Sender, (void*)arguments);
			
			// publisher_work(&context1, data);
			
			sleep(1);
		}
		
	}*/
    return 0;
}



void printData(std::vector <std::string> data)
{
	for(auto it =data.begin()++; it != data.end(); it++){
		
		string contents = *it;
		
		// Getting the byte table from the received string
		std::vector<char> bytes(contents.begin(), contents.end());
		bytes.push_back('\0');
		char *c = &bytes[0];

		// parsing that bytes table
	
		zmq::message_t message(contents.size());
		memcpy (message.data(), contents.data(), contents.size());
		
		msg::msg m;
		m.ParseFromArray(message.data(), message.size());
	
		// Getting the data from the parsed message	
		string name = m.name();
		int id = m.id();
		string arg1 = m.arg1();
	
		string arg2 = "empty"; 
		if(m.has_arg2()) arg2 = m.arg2();
	
		string arg3 = "empty";
		if(m.has_arg3()) arg3 = m.arg3();
	
		std::cout << " name : "  << name << "\tid : "  << id << "\targ1 : "  << arg1 << std::endl;
            
	}
}
