#!/bin/sh
SCRIPT="bomb.sh"
TIME=""
TEST="2:17 PM 3/3/2017"

apt-get install at -y

cat -v "$SCRIPT" | at $TEST
