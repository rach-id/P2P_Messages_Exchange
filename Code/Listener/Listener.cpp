
#include <iostream>
#include "zhelpers.hpp"
#include "protobuf/msg.pb.h"
#include "Listener.h"

using namespace std;

bool Listener::subscriber_work() { // Subscriber : for receiving updates published by other serves

	
	zmq::socket_t subscriber(*context, ZMQ_SUB);
    subscriber.connect("tcp://zmq.service.test.consul:5563");  
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);
    
    
    // cout << "Waiting to get the envelope..." << endl;
    //  Read envelope with address
    std::string address = s_recv (subscriber);
    //  Read message contents
    // cout << "Waiting to get the Contents..." << endl;
    
    std::string contents = s_recv (subscriber);
    
    cout << "Checking if its the same stuff..." << endl;
            
    if(data_verification(contents)) return false; // re-listen if we only received the same data as before
    
    
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
	
    std::cout << "[" << address << "] " << "\tname : "  << name << "\tid : "  << id << "\targ1 : "  << arg1 << "\targ2 : "  << arg2 << "\targ3 : "  << arg3 <<"\n" << std::endl;
            
            
    data->push_back(contents);
    
    return true;
}// end subscriber_work



void Listener::listen() {
	
	while(1){
		subscriber_work();
	}
	
} 


bool Listener::data_verification(string content1){
	
	for(auto it =data->begin()++; it != data->end(); it++){
		
		string content2 = *it;
		
		// Getting the byte table from the received string
		std::vector<char> byte1(content1.begin(), content1.end());
		byte1.push_back('\0');
		char *c1 = &byte1[0];
		
		std::vector<char> byte2(content2.begin(), content2.end());
		byte2.push_back('\0');
		char *c2 = &byte2[0];
	
	
		// parsing that bytes table
		zmq::message_t message1(content1.size());
		memcpy (message1.data(), content1.data(), content1.size());
		msg::msg m1;
		m1.ParseFromArray(message1.data(), message1.size());
	
		zmq::message_t message2(content2.size());
		memcpy (message2.data(), content2.data(), content2.size());
		msg::msg m2;
		m2.ParseFromArray(message2.data(), message2.size());

		// Getting the data from the parsed message	
		string name1 = m1.name();
		int id1 = m1.id();
		string arg11 = m1.arg1();
	
		string arg21 = "empty"; 
		if(m1.has_arg2()) arg21 = m1.arg2();
	
		string arg31 = "empty";
		if(m1.has_arg3()) arg31 = m1.arg3();
	
	
		string name2 = m2.name();
		int id2 = m2.id();
		string arg12 = m1.arg1();
	
		string arg22 = "empty"; 
		if(m1.has_arg2()) arg22 = m2.arg2();
	
		string arg32 = "empty";
		if(m2.has_arg3()) arg32 = m2.arg3();
	
	
		if(name1.compare(name2) == 0 && id1 == id2 && arg11.compare(arg12) == 0) return true;
	
	}
	return false;
	
}
