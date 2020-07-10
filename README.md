# P2P_Messages_Exchange

This is a Project that lets you send messages between different nodes using zMQ c++ target.
The simulation is done in vagrant o bring 6 nodes up and running.



To compile the stuff :
  
  => Clone the repo
  
  => make sure you have a working Vagrant env
  
  => $ vagrant up 

this will create 6 hosts ready to be used
  
  => Compile the project : $ cd Code && make && make clean 
  
  => Log into the vagrant machines : $ vagrant ssh host-[1-5] 

#each in a different terminal and also the consul server : $ vagrant ssh consul-server

  => in all machines  $  /vagrant/Code/Server
  
  Write a message and see the magic.
 
 
 To check the consul service + the nodes that are connected (a health test is not available for the moment), use the url : 192.168.99.100:8500 from your main machine.
