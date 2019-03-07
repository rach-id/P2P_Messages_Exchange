#!/bin/bash

# update and unzip



dpkg -s unzip &>/dev/null || {
	apt-get -y update && apt-get install -y unzip
}


if [ ! -f /usr/local/bin/consul ]; then

	# install consul 
	
	cd /usr/local/bin
	version='0.8.0'
	wget https://releases.hashicorp.com/consul/${version}/consul_${version}_linux_amd64.zip -O consul.zip
	unzip consul.zip
	rm consul.zip

	chmod +x consul
	
	
	# Dnsmasq Configuration
	
	apt-get install -y dnsmasq

	echo "server=/consul/127.0.0.1#8600" >> /etc/dnsmasq.d/10-consul

	echo "nameserver 127.0.0.1" > /etc/resolv.conf
	
	systemctl start dnsmasq 
	
	export LANGUAGE=en_US.UTF-8
	export LANG=en_US.UTF-8
	export LC_ALL=en_US.UTF-8
	locale-gen en_US.UTF-8

	# apt-get install locales
	# dpkg-reconfigure locales
	
	systemctl enable dnsmasq 
	
	systemctl restart dnsmasq
	
	apt install -y build-essential
	apt-get install -y libzmqpp-dev 

	# protobuf c++ target
	apt-get install -y libprotobuf-dev 
	
fi

if [ ! -f /etc/systemd/system/consul.service ]; then
	cp /vagrant/consul.service /etc/systemd/system/consul.service
fi

if [ ! -d /etc/systemd/system/consul.d ]; then
	mkdir -p /etc/systemd/system/consul.d
fi
