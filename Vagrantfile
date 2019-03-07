Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial64"

  def create_consul_host(config, hostname, ip, initJson, zService)
    config.vm.define hostname do |host|		
		
		host.vm.hostname = hostname
		host.vm.provision "shell", path: "provision.sh"
		
		host.vm.network "private_network", ip: ip
		host.vm.provision "shell", inline: "echo '#{initJson}' > /etc/systemd/system/consul.d/init.json"
		
		host.vm.provision "shell", inline: "echo '#{zService}' > /etc/systemd/system/consul.d/zService.json"
		
		host.vm.provision "shell", inline: "service consul start"
    end
  end

  serverIp = "192.168.99.100"
  serverInit = %(
	{
		"datacenter": "test",
		"node_name": "server",
		"server": true,
		"ui": true,
		"advertise_addr": "#{serverIp}",
		"client_addr": "#{serverIp}",
		"retry_join": ["#{serverIp}"],
		"data_dir": "/tmp/consul",
		"bootstrap_expect": 1
	}
  )

  zmqService= %(
	{
	  "service": {
		"name": "zmq",
		"address": "#{serverIp}",
		"port": 5555,
		"enableTagOverride": false
	  }
	}
  )
  
  create_consul_host config, "consul-server", serverIp, serverInit, zmqService

  for host_number in 1..5
  	hostname="host-#{host_number}"
  	clientIp="192.168.99.10#{host_number}"

	clientInit = %(
		{
			"datacenter": "test",
			"node_name": "host-#{host_number}",
			"server":false,
			"advertise_addr": "#{clientIp}",
			"retry_join": ["#{serverIp}"],
			"data_dir": "/tmp/consul"
		}
	)

	zmqService= %(
		{
		  "service": {
			"name": "zmq",
			"address": "#{clientIp}",
			"port": 5555,
			"enableTagOverride": false
		  }
		}
  	)
	create_consul_host config, hostname, clientIp, clientInit, zmqService
  end

end
