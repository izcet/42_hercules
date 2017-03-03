#!/bin/bash
SCRIPT="bomb.sh"
TIME=""
TEST="2:59 PM 3/3/2017"

apt-get install at -y > /dev/null

at $TEST < $SCRIPT
