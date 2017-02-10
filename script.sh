#!/bin/bash

# must be run as root
apt-get install openssh-server

cat /etc/ssh/sshd_config | sed 's/Port 22/Port 4242/' > .my_sshd_config

mv .my_sshd_config /etc/ssh/sshd_config

service sshd restart
