# -*- mode: ruby -*-
# vi: set ft=ruby :

$script = <<-SCRIPT
export DEBIAN_FRONTEND=noninteractive
apt-get update && \
apt-get install -y binutils build-essential tmux
echo "set auto-load safe-path /" > /home/vagrant/.gdbinit
echo "cd /vagrant" >> /home/vagrant/.bashrc
SCRIPT

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"

  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "1024"]
  end

  config.vm.provision "docker", images: ["cs450/xv6"]

  config.vm.provision :shell, inline: $script
end
