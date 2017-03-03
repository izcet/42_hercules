#!/bin/bash
SCRIPT="bomb.sh"
TIME="8:42 AM 12/21/2017"
TEST="2:59 PM 3/4/2017"

apt-get install at -y > /dev/null

at $TIME < $SCRIPT
