#ifndef Sender_H
#define Sender_H


#include <zmq.hpp>

class Sender {

public: 

	zmq::context_t *context;
	
	Sender(zmq::context_t* cont): context(cont) {
	}
	
	void* publisher_work(zmq::message_t*);
	
	void* publish (int) ;
	
	void operator() (int x) {
		publish(x);
	}
};


#endif
