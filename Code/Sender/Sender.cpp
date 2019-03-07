
#include "Sender.h"
#include <iostream>
#include "zhelpers.hpp"
#include "protobuf/msg.pb.h"


using namespace std;

void* Sender::publisher_work(zmq::message_t* message) { //Publisher : For publishing the answer to all the connected nodes

	zmq::socket_t publisher(*context, ZMQ_PUB); 
	try {
		publisher.bind("tcp://*:5563");
	
	} catch (...) {
			cout << "Sending Error, retrying" << endl;
			sleep(2);
			publisher_work(message);
	}
	cout << "New stuff, proceding with the sending..." << endl;
	
    for(int i = 0; i < 10 ; i++) { // Publish till we got a confirmation from a node that it received something
    
        sleep(1);
        
		s_sendmore (publisher, "B");
		s_send (publisher, std::string(static_cast<char*>(message->data()), message->size()));
		cout << "sending : " << i << endl;
		
		// verify confirmation from any node, replaced by the for loop
		
	}
} // end publisher_work



void* Sender::publish (int id) {
	
	while(1) {
		cout << "Enter the message you want to send: " << endl;
		string msg = "";
		cin >> msg;
	
		/* Serializing a message using protobuf */
	   
	   msg::msg m ;
	   
	   m.set_name(msg);
	   m.set_id(id);
	   m.set_arg1("m");
	   
	   std::string str;
	   m.SerializeToString(&str);
	   int sz = str.length();
	   
	   zmq::message_t *message = new zmq::message_t(sz);
	   memcpy(message->data(), str.c_str(), sz);
	   
	   /* End protobuf */
	   
	   /* Sending the message to the publisher */
	   
	   publisher_work(message);
   }
   
}

