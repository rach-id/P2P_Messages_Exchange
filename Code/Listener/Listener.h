#ifndef Listener_H
#define Listener_H

#include <zmq.hpp>
#include <string>
#include <vector>
#include <iostream>

class Listener {
	
public:
	zmq::context_t *context;
	std::vector <std::string> *data;
	
	Listener(zmq::context_t* cont, std::vector <std::string> *dt) : context(cont), data(dt) {
	}
	
	bool subscriber_work();
	
	void listen();
	
	void operator() () {
		listen();
	}
	
	bool data_verification(std::string);
	

};

#endif

